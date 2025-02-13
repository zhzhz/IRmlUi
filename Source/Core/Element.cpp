#include "../../Include/RmlUi/Core/Element.h"
#include "../../Include/RmlUi/Core/ID.h"
#include "EventSpecification.h"
#include "EventDispatcher.h"

namespace Rml {

Element::Element(const String& tag)
{

}

Element::~Element()
{
    
}

Element* Element::GetParentNode() const
{
	return parent;
}

//向元素发送特定事件
bool Element::DispatchEvent(EventId id)
{
	//根据时间id得到事件具体信息
	const EventSpecification& specification = EventSpecificationInterface::Get(id);
	
	//调用事件转发器转发事件
	return EventDispatcher::DispatchEvent(this, specification.id, specification.type, specification.interruptible, specification.bubbles,
		specification.default_action_phase);
	
	//return true;
}

}