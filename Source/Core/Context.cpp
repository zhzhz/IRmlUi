#include "../../Include/RmlUi/Core/Context.h"
#include "../../Include/RmlUi/Core/ElementDocument.h"
#include "../../Include/RmlUi/Core/ID.h"

namespace Rml {

ElementDocument* Context::LoadDocument(const String& document_path)
{
    return NULL;
}

bool Context::Update()
{
    return true;
}

bool Context::Render()
{
    return true;
}

Context::~Context()
{
}

Context::Context(const String& name, RenderManager* render_manager)
{
	mouse_active = false;
}

bool Context::ProcessMouseMove(int x, int y)
{
	Vector2i old_mouse_position = mouse_position;
	mouse_position = {x, y};
	const bool mouse_moved = (mouse_position != old_mouse_position || !mouse_active);
	mouse_active = true;

	UpdateHoverChain(old_mouse_position);

	return true;
}

void Context::UpdateHoverChain(Vector2i old_mouse_position)
{
	//得到鼠标的当前位置
	const Vector2f position(mouse_position);

	//得到当前鼠标位置下的元素
	hover = mouse_active ? GetElementAtPoint(position) : nullptr;

	//将鼠标位置下的元素及其所有父元素加入到hover链
	ElementSet new_hover_chain;
	Element* element = hover;
	while (element != nullptr)
	{
		new_hover_chain.insert(element);
		element = element->GetParentNode();
	}

	//发送鼠标进入和鼠标退出消息
	//向只出现在hover_chain的元素发送Mouseout事件
	//向只出现在new_hover_chain的元素发送Mouseover事件
	SendEvents(hover_chain, new_hover_chain, EventId::Mouseout);
	SendEvents(new_hover_chain, hover_chain, EventId::Mouseover);

	//更新hover链
	hover_chain.swap(new_hover_chain);
}

//根据位置找到当前位置下的元素
Element* Context::GetElementAtPoint(Vector2f point, const Element* ignore_element, Element* element) const
{
	return (Element*)NULL;
}

using ElementObserverList = Vector<ObserverPtr<Element>>;

class ElementObserverListBackInserter {
public:
	using iterator_category = std::output_iterator_tag;
	using value_type = void;
	using difference_type = void;
	using pointer = void;
	using reference = void;
	using container_type = ElementObserverList;

	ElementObserverListBackInserter(ElementObserverList& elements) : elements(&elements) {}
	ElementObserverListBackInserter& operator=(Element* element)
	{
		elements->push_back(element->GetObserverPtr());
		return *this;
	}
	ElementObserverListBackInserter& operator*() { return *this; }
	ElementObserverListBackInserter& operator++() { return *this; }
	ElementObserverListBackInserter& operator++(int) { return *this; }

private:
	ElementObserverList* elements;
};

//发送特定事件到只在old_items中出现的元素
void Context::SendEvents(const ElementSet& old_items, const ElementSet& new_items, 
EventId id)
{
	// We put our elements in observer pointers in case some of them are deleted during dispatch.
	ElementObserverList elements;
	
	std::set_difference(old_items.begin(), old_items.end(), 
	new_items.begin(), new_items.end(), ElementObserverListBackInserter(elements));

	for (auto& element : elements)
	{
		//如果element在DispatchEvent的处理中被删除，则element为NULL，不被调用
		if (element)
			element->DispatchEvent(id);//向元素发送特定事件
	}
}

}