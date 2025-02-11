project(IRmlUi)

add_subdirectory("Source")#编译UI内核

set(RMLUI_SAMPLES ON)#编译samples，包括shell和自己的dev

if(RMLUI_SAMPLES)
	set(RMLUI_SHELL ON)#编译shell
endif()

if(RMLUI_SHELL)
	include("CMake/DependenciesForBackends.cmake")#包含SDL2库
	add_subdirectory("Backends")#如果编译shell，则需要编译后端
endif()

add_subdirectory("Samples")#编译shell和dev应用




