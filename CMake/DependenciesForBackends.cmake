
#设置系统中SDL2库的位置
#list(APPEND CMAKE_PREFIX_PATH "D:/prj/vcpkg/buildtrees")

#查找系统中的SDL库
#find_package(SDL2 REQUIRED)

#创建SDL2的接口
#
#if(NOT TARGET SDL2::SDL2)
#	add_library(SDL2::SDL2 INTERFACE IMPORTED)
#	set_target_properties(SDL2::SDL2 PROPERTIES
#		#导入SDL库的链接位置到系统变量SDL2_LIBRARIES
#		INTERFACE_LINK_LIBRARIES "${SDL2_LIBRARIES}"
#
#		#导入SDL库的头文件位置到系统变量SDL2_INCLUDE_DIRS
#		INTERFACE_INCLUDE_DIRECTORIES "${SDL2_INCLUDE_DIRS}"
#	)
#endif()


#找到sdl库，感觉很丑，应该让cmake自己去找，而不是写死
#####################
#set(SDL2_INCLUDE_DIRS "D:/prj/vcpkg/packages/sdl2_x64-windows/include/SDL2")

# Support both 32 and 64 bit builds
#set(SDL2_LIBRARIES "D:/prj/vcpkg/packages/sdl2_x64-windows/lib/SDL2.lib;D:/prj/vcpkg/packages/sdl2_x64-windows/lib/manual-link/SDL2main.lib")

#string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
#####################
#自动寻找SDL2库
#list(APPEND CMAKE_PREFIX_PATH "D:/prj/vcpkg/packages/sdl2_x64-windows")
find_package("SDL2")
#####################

if(NOT TARGET SDL2::SDL2)
	add_library(SDL2::SDL2 INTERFACE IMPORTED)
	set_target_properties(SDL2::SDL2 PROPERTIES
		#导入SDL库的链接位置到系统变量SDL2_LIBRARIES
		INTERFACE_LINK_LIBRARIES "${SDL2_LIBRARIES}"

		#导入SDL库的头文件位置到系统变量SDL2_INCLUDE_DIRS
		INTERFACE_INCLUDE_DIRECTORIES "${SDL2_INCLUDE_DIRS}"
	)
endif()

#创建SDL的接口，并导出编译时会用到的RMLUI_SDL_VERSION_MAJOR来表明当前使用的是SDL2版本
add_library(SDL::SDL INTERFACE IMPORTED)
target_link_libraries(SDL::SDL INTERFACE SDL2::SDL2)
target_compile_definitions(SDL::SDL INTERFACE RMLUI_SDL_VERSION_MAJOR=2)

