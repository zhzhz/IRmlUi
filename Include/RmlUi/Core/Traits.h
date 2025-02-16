﻿
#ifndef RMLUI_CORE_TRAITS_H
#define RMLUI_CORE_TRAITS_H

#include "Header.h"

namespace Rml {

class RMLUICORE_API NonCopyMoveable {
public:
	NonCopyMoveable() {}
	~NonCopyMoveable() {}
	NonCopyMoveable(const NonCopyMoveable&) = delete;
	NonCopyMoveable& operator=(const NonCopyMoveable&) = delete;
	NonCopyMoveable(NonCopyMoveable&&) = delete;
	NonCopyMoveable& operator=(NonCopyMoveable&&) = delete;
};

class ReleaserBase;

class RMLUICORE_API Releasable : public NonCopyMoveable {
protected:
	virtual ~Releasable() = default;
	virtual void Release() = 0;
	friend class Rml::ReleaserBase;
};

class RMLUICORE_API ReleaserBase {
protected:
	void Release(Releasable* target) const { target->Release(); }
};

template <typename T>
class RMLUICORE_API Releaser : public ReleaserBase {
public:
	void operator()(T* target) const
	{
		static_assert(std::is_base_of<Releasable, T>::value, "Rml::Releaser can only operate with classes derived from ::Rml::Releasable.");
		Release(static_cast<Releasable*>(target));
	}
};


}

#define RMLUI_RTTI_Define(_NAME_)
#define RMLUI_RTTI_DefineWithParent(_NAME_, _PARENT_)

#endif // RMLUI_CORE_TRAITS_H