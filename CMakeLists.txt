cmake_minimum_required(VERSION 3.28)
project(TheCommunicator)

set(CMAKE_CXX_STANDARD 26)

set(CPM_SOURCE_CACHE external)
include(cmake/get_cpm.cmake)
CPMAddPackage("gh:libsdl-org/SDL#release-3.2.8")
CPMAddPackage("gh:ocornut/imgui#v1.91.8")

add_library(ImGUI STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)
target_include_directories(ImGUI PUBLIC ${imgui_SOURCE_DIR})
target_link_libraries(ImGUI SDL3::SDL3-shared)

# Add the src directory to the include path
include_directories(src)

add_executable(TheCommunicator
        src/main.cpp
        src/gui/gui.cpp
        src/backend/messaging.cpp
        src/backend/video.cpp
        src/network/client.cpp
        src/utils/logger.cpp
)
target_link_libraries(TheCommunicator ImGUI SDL3::SDL3-shared)