#include "RmlUi_Backend.h"
#include "RmlUi_Renderer_GL3.h"
#include "../Include/RmlUi/Core/Context.h"
#include "../Include/RmlUi/Core/Core.h"
#include "RmlUi_Platform_SDL.h"

/**
    Custom render interface example for the SDL/GL3 backend.

    Overloads the OpenGL3 render interface to load textures through SDL_image's built-in texture loading functionality.
 */
class RenderInterface_GL3_SDL : public RenderInterface_GL3 {
public:
	RenderInterface_GL3_SDL() {}
};

struct BackendData {
	//SystemInterface_SDL system_interface;
	RenderInterface_GL3_SDL render_interface;

	SDL_Window* window = nullptr;
	SDL_GLContext glcontext = nullptr;

	bool running = true;
};
static Rml::UniquePtr<BackendData> data;

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
	//处理鼠标移动和左键按下和弹起事件
	int has_event = 0;
	SDL_Event ev;

	//调用SDL库函数等待事件发生
	//等待10秒没有事件发生就返回
	//有事件发生立即返回
	has_event = SDL_WaitEventTimeout(&ev, static_cast<int>(10.0 * 1000));

	//循环处理每一条事件
	while (has_event)
	{
		bool propagate_event = true;

		if (propagate_event)
		{
			//处理事件
			RmlSDL::InputEventHandler(context, data->window, ev);
		}

		//取出事件
		has_event = SDL_PollEvent(&ev);
	}

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
