﻿/*
 * This source file is part of RmlUi, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://github.com/mikke89/RmlUi
 *
 * Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 * Copyright (c) 2019-2023 The RmlUi Team, and contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */



namespace Rml {

template < typename PoolType >
Pool< PoolType >::Pool(int _chunk_size, bool _grow)
{
	chunk_size = 0;
	grow = _grow;

	num_allocated_objects = 0;

	pool = nullptr;
	first_allocated_node = nullptr;
	first_free_node = nullptr;

	if (_chunk_size > 0)
		Initialise(_chunk_size, _grow);
}

template < typename PoolType >
Pool< PoolType >::~Pool()
{
	RMLUI_ASSERT(num_allocated_objects == 0);

	PoolChunk* chunk = pool;
	while (chunk)
	{
		PoolChunk* next_chunk = chunk->next;

		delete[] chunk->chunk;
		delete chunk;

		chunk = next_chunk;
	}
}

// Initialises the pool to a given size.
template < typename PoolType >
void Pool< PoolType >::Initialise(int _chunk_size, bool _grow)
{
	// Should resize the pool here ... ?
	if (chunk_size > 0)
		return;

	if (_chunk_size <= 0)
		return;

	grow = _grow;
	chunk_size = _chunk_size;
	pool = nullptr;

	// Create the initial chunk.
	CreateChunk();
}

// Returns the head of the linked list of allocated objects.
template < typename PoolType >
typename Pool< PoolType >::Iterator Pool< PoolType >::Begin()
{
	return typename Pool< PoolType >::Iterator(first_allocated_node);
}

// Attempts to allocate a deallocated object in the memory pool.
template<typename PoolType>
template<typename ...Args>
inline PoolType* Pool<PoolType>::AllocateAndConstruct(Args&&... args)
{
	// We can't allocate a new object if the deallocated list is empty.
	if (first_free_node == nullptr)
	{
		// Attempt to grow the pool first.
		if (grow)
		{
			CreateChunk();
			if (first_free_node == nullptr)
				return nullptr;
		}
		else
			return nullptr;
	}

	// We're about to allocate an object.
	++num_allocated_objects;

#ifdef RMLUI_DEBUG
	if (num_allocated_objects > max_num_allocated_objects)
		max_num_allocated_objects = num_allocated_objects;
#endif

	// This one!
	PoolNode* allocated_object = first_free_node;

	// Remove the newly allocated object from the list of deallocated objects.
	first_free_node = first_free_node->next;
	if (first_free_node != nullptr)
		first_free_node->previous = nullptr;

	// Add the newly allocated object to the head of the list of allocated objects.
	if (first_allocated_node != nullptr)
	{
		allocated_object->previous = nullptr;
		allocated_object->next = first_allocated_node;
		first_allocated_node->previous = allocated_object;
	}
	else
	{
		// This object is the only allocated object.
		allocated_object->previous = nullptr;
		allocated_object->next = nullptr;
	}

	first_allocated_node = allocated_object;

	return new (allocated_object->object) PoolType(std::forward<Args>(args)...);
}

// Deallocates the object pointed to by the given iterator.
template < typename PoolType >
void Pool< PoolType >::DestroyAndDeallocate(Iterator& iterator)
{
	// We're about to deallocate an object.
	--num_allocated_objects;

	PoolNode* object = iterator.node;
	reinterpret_cast<PoolType*>(object->object)->~PoolType();

	// Get the previous and next pointers now, because they will be overwritten
	// before we're finished.
	PoolNode* previous_object = object->previous;
	PoolNode* next_object = object->next;

	if (previous_object != nullptr)
		previous_object->next = next_object;
	else
	{
		RMLUI_ASSERT(first_allocated_node == object);
		first_allocated_node = next_object;
	}

	if (next_object != nullptr)
		next_object->previous = previous_object;

	// Insert the freed node at the beginning of the free object list.
	if (first_free_node == nullptr)
	{
		object->previous = nullptr;
		object->next = nullptr;
	}
	else
	{
		object->previous = nullptr;
		object->next = first_free_node;
	}

	first_free_node = object;

	// Increment the iterator, so it points to the next active object.
	iterator.node = next_object;
}

// Deallocates the given object.
template < typename PoolType >
void Pool< PoolType >::DestroyAndDeallocate(PoolType* object)
{
	// This assumes the object has the same address as the node, which will be
	// true as long as the struct definition does not change.
	Iterator iterator((PoolNode*) object);
	DestroyAndDeallocate(iterator);
}

// Returns the number of objects in the pool.
template < typename PoolType >
int Pool< PoolType >::GetSize() const
{
	return chunk_size * GetNumChunks();
}

/// Returns the number of object chunks in the pool.
template < typename PoolType >
int Pool< PoolType >::GetNumChunks() const
{
	int num_chunks = 0;

	PoolChunk* chunk = pool;
	while (chunk != nullptr)
	{
		++num_chunks;
		chunk = chunk->next;
	}

	return num_chunks;
}

// Returns the number of allocated objects in the pool.
template < typename PoolType >
int Pool< PoolType >::GetNumAllocatedObjects() const
{
	return num_allocated_objects;
}

// Creates a new pool chunk and appends its nodes to the beginning of the free list.
template < typename PoolType >
void Pool< PoolType >::CreateChunk()
{
	if (chunk_size <= 0)
		return;

	// Create the new chunk and mark it as the first chunk.
	PoolChunk* new_chunk = new PoolChunk();
	new_chunk->next = pool;
	pool = new_chunk;

	// Create chunk's pool nodes.
	new_chunk->chunk = new PoolNode[chunk_size];

	// Initialise the linked list.
	for (int i = 0; i < chunk_size; i++)
	{
		if (i == 0)
			new_chunk->chunk[i].previous = nullptr ;
		else
			new_chunk->chunk[i].previous = &new_chunk->chunk[i - 1];

		if (i == chunk_size - 1)
			new_chunk->chunk[i].next = first_free_node;
		else
			new_chunk->chunk[i].next = &new_chunk->chunk[i + 1];
	}

	first_free_node = new_chunk->chunk;
}

} // namespace Rml
