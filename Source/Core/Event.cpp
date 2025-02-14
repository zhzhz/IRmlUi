#include "../../Include/RmlUi/Core/Event.h"
#include "../../Include/RmlUi/Core/Element.h"
//#include "../../Include/RmlUi/Core/EventInstancer.h"
#include "../../Include/RmlUi/Core/EventInstancer.h"

namespace Rml {

Event::Event(Element* _target_element, EventId id) :
	id(id)
{

}

Event::~Event() {}


EventId Event::GetId() const
{
	return id;
}

void Event::Release()
{
	if (instancer)
		instancer->ReleaseEvent(this);
	//else
		//Log::Message(Log::LT_WARNING, "Leak detected: Event %s not instanced via RmlUi Factory. Unable to release.", type.c_str());
}

}

