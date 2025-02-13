#include "RmlUi_Platform_SDL.h"
#include "../Include/RmlUi/Core/Context.h"

bool RmlSDL::InputEventHandler(Rml::Context* context, SDL_Window* window, SDL_Event& ev)
{
	(void)window;

	bool result = true;

	constexpr auto event_mouse_motion = SDL_MOUSEMOTION;
	constexpr auto event_mouse_down = SDL_MOUSEBUTTONDOWN;
	constexpr auto event_mouse_up = SDL_MOUSEBUTTONUP;

	switch (ev.type)
	{
	case event_mouse_motion:
	{
		result = context->ProcessMouseMove(int(ev.motion.x), int(ev.motion.y));
	}
	break;
	case event_mouse_down:
	{
		//result = context->ProcessMouseButtonDown(ConvertMouseButton(ev.button.button), GetKeyModifierState());
		//SDL_CaptureMouse(rmlsdl_true);
	}
	break;
	case event_mouse_up:
	{
		//SDL_CaptureMouse(rmlsdl_false);
		//result = context->ProcessMouseButtonUp(ConvertMouseButton(ev.button.button), GetKeyModifierState());
	}
	break;

	default: break;
	}

	return result;
}