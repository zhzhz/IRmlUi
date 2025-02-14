#ifndef RMLUI_CORE_FACTORY_H
#define RMLUI_CORE_FACTORY_H

#include "Header.h"
#include <stack>
#include "Types.h"

namespace Rml {
class Element;
class EventInstancer;
enum class EventId : uint16_t;

class RMLUICORE_API Factory {
public:
	static EventPtr InstanceEvent(Element* target, EventId id);
	static void RegisterEventInstancer(EventInstancer* instancer);

	static void Initialise();
};

}

#endif