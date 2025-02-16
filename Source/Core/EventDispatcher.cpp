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

#include "EventDispatcher.h"
#include "../../Include/RmlUi/Core/Element.h"
#include "../../Include/RmlUi/Core/Event.h"
//#include "../../Include/RmlUi/Core/EventListener.h"
//#include "../../Include/RmlUi/Core/Factory.h"
#include "EventSpecification.h"
#include <algorithm>
#include <limits>
#include "../../Include/RmlUi/Core/Factory.h"

namespace Rml {

bool operator==(EventListenerEntry a, EventListenerEntry b)
{
	return a.id == b.id && a.in_capture_phase == b.in_capture_phase && a.listener == b.listener;
}
bool operator!=(EventListenerEntry a, EventListenerEntry b)
{
	return !(a == b);
}

struct CompareId {
	bool operator()(EventListenerEntry a, EventListenerEntry b) const { return a.id < b.id; }
};
struct CompareIdPhase {
	bool operator()(EventListenerEntry a, EventListenerEntry b) const
	{
		return std::tie(a.id, a.in_capture_phase) < std::tie(b.id, b.in_capture_phase);
	}
};

//EventDispatcher::EventDispatcher(Element* _element) : element(_element) {}



//事件发生后会调用这个函数，分发事件
bool EventDispatcher::DispatchEvent(Element* target_element, const EventId id, const String& type,
	const bool interruptible, const bool bubbles, const DefaultActionPhase default_action_phase)
{

	//创建事件对象
	EventPtr event = Factory::InstanceEvent(target_element, id);

	//调用元素的默认处理函数
	target_element->ProcessDefaultAction(*event);

	return true;
}



} // namespace Rml
