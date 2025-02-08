project (Dev)

set(TARGET_NAME "dev")

add_executable(${TARGET_NAME} WIN32
	src/main.cpp
)

target_link_libraries(${TARGET_NAME} PRIVATE rmlui_shell)