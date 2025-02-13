#ifndef RMLUI_BACKENDS_PLATFORM_SDL_H
#define RMLUI_BACKENDS_PLATFORM_SDL_H

#include <SDL.h>
#include "../Include/RmlUi/Core/Context.h"

namespace RmlSDL {

// Applies input on the context based on the given SDL event.
// @return True if the event is still propagating, false if it was handled by the context.
bool InputEventHandler(Rml::Context* context, SDL_Window* window, SDL_Event& ev);

}
#endif