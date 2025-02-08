#include "RmlUi_Backend.h"
#include "RmlUi_Renderer_GL3.h"
#include "../Include/RmlUi/Core/Context.h"
#include "../Include/RmlUi/Core/Core.h"

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
	return false;
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
