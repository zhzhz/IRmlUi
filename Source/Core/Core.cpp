﻿#include "../../Include/RmlUi/Core/SystemInterface.h"
#include "../../Include/RmlUi/Core/RenderInterface.h"
#include "../../Include/RmlUi/Core/Context.h"
#include "../../Include/RmlUi/Core/Factory.h"


namespace Rml {

void SetSystemInterface(SystemInterface* _system_interface)
{
}

void SetRenderInterface(RenderInterface* _render_interface)
{
}

//初始化工厂
bool Initialise()
{
	Factory::Initialise();
	return true;
}

Context* CreateContext(const String& name, const Vector2i dimensions, RenderInterface* render_interface_for_context)
{
	return (Context*)(1);
}

void Shutdown()
{
}

}