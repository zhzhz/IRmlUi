#shell的文件中需要选中并链接一个后端
add_library(rmlui_shell STATIC
	#src/PlatformExtensions.cpp
	#src/RendererExtensions.cpp
	src/Shell.cpp
	#src/ShellFileInterface.cpp

	#include/PlatformExtensions.h
	#include/RendererExtensions.h
	include/Shell.h
	#include/ShellFileInterface.h
)

#目前只有rmlui_backend_SDL_GL3一个后端
target_link_libraries(rmlui_shell PRIVATE rmlui_backend_SDL_GL3)

#每个用户程序都使用shell模块，所以让shell去链接内核rmlui_core模块
target_link_libraries(rmlui_shell PUBLIC rmlui_core)

target_include_directories(rmlui_shell INTERFACE  "${PROJECT_SOURCE_DIR}/Samples/shell/include")