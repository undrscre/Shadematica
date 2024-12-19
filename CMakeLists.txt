cmake_minimum_required(VERSION 3.10)
project(Shadematica VERSION 0.1.0 LANGUAGES C CXX)

add_executable(Shadematica src/main.cpp src/logger.cpp)

add_subdirectory(libs/glfw)
target_link_libraries(Shadematica PRIVATE glfw)

add_library(glad STATIC libs/glad/src/glad.c)
target_include_directories(glad PUBLIC libs/glad/include)
target_link_libraries(Shadematica PRIVATE glad)

add_library(imgui STATIC
    libs/imgui/imgui.cpp
    libs/imgui/imgui_draw.cpp
    libs/imgui/imgui_widgets.cpp
)
target_include_directories(imgui PUBLIC libs/imgui)

target_link_libraries(Shadematica PRIVATE imgui)


target_include_directories(Shadematica PUBLIC libs/glm)
