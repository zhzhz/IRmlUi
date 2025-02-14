#include "../../Include/RmlUi/Core/Factory.h"
#include "../../Include/RmlUi/Core/EventInstancer.h"
#include "../../Include/RmlUi/Core/Event.h"

#include "ControlledLifetimeResource.h"
#include "EventInstancerDefault.h"

namespace Rml {

static EventInstancer* event_instancer = nullptr;

struct DefaultInstancers {
	UniquePtr<EventInstancer> event_default;

};

struct FactoryData {
	DefaultInstancers default_instancers;
	// UnorderedMap<String, ElementInstancer*> element_instancers;
	// UnorderedMap<String, DecoratorInstancer*> decorator_instancers;
	// UnorderedMap<String, FilterInstancer*> filter_instancers;
	// UnorderedMap<String, FontEffectInstancer*> font_effect_instancers;
	// UnorderedMap<String, DataViewInstancer*> data_view_instancers;
	// UnorderedMap<String, DataControllerInstancer*> data_controller_instancers;
	// SmallUnorderedMap<String, DataViewInstancer*> structural_data_view_instancers;
	// StringList structural_data_view_attribute_names;
};

static ControlledLifetimeResource<FactoryData> factory_data;

EventPtr Factory::InstanceEvent(Element* target, EventId id)
{
	EventPtr event = event_instancer->InstanceEvent(target, id);

	if (event)
		event->instancer = event_instancer;

	return event;
}

void Factory::RegisterEventInstancer(EventInstancer* instancer)
{
	event_instancer = instancer;
}

void Factory::Initialise()
{
	factory_data.Initialize();

	DefaultInstancers& default_instancers = factory_data->default_instancers;

	//初始化事件实例化
	if (!event_instancer)
	{
		default_instancers.event_default = MakeUnique<EventInstancerDefault>();
		event_instancer = default_instancers.event_default.get();
	}
}


}