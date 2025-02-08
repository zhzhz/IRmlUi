#include "RmlUi_Backend.h"
#include "RmlUi_Renderer_GL3.h"
#include "../Include/RmlUi/Core/Context.h"
#include "../Include/RmlUi/Core/Core.h"

#if defined RMLUI_PLATFORM_EMSCRIPTEN
	#include <emscripten.h>
#elif SDL_MAJOR_VERSION == 2 && !(SDL_VIDEO_RENDER_OGL)
	#error "Only the OpenGL SDL backend is supported."
#endif

/**
    Custom render interface example for the SDL/GL3 backend.

    Overloads the OpenGL3 render interface to load textures through SDL_image's built-in texture loading functionality.
 */
class RenderInterface_GL3_SDL : public RenderInterface_GL3 {
public:
	RenderInterface_GL3_SDL() {}
};

bool Backend::Initialize(const char* window_name, int width, int height, bool allow_resize)
{
	return true;
}

void Backend::Shutdown()
{

}

Rml::SystemInterface* Backend::GetSystemInterface()
{
	return NULL;
}

Rml::RenderInterface* Backend::GetRenderInterface()
{
	return NULL;
}

bool Backend::ProcessEvents(Rml::Context* context, bool power_save)
{
	return false;//让程序可以自己退出
}


void Backend::RequestExit()
{

}

void Backend::BeginFrame()
{

}

void Backend::PresentFrame()
{

}
