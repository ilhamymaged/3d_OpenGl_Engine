cmake_minimum_required (VERSION 3.10)
project ("gameEngine")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(Vendor/glfw)

file(GLOB_RECURSE SRC_FILES Core/*.c Renderer/*.c Editor/*.c Scene/*.c)
list(APPEND SRC_FILES main.c Vendor/glad/src/glad.c 
Vendor/stb/stb_image.c Vendor/tiny_obj_loader/tiny_obj_loader.cpp)

add_executable (CMakeTarget ${SRC_FILES})

target_include_directories(CMakeTarget PRIVATE 
    Core 
    Editor
    Renderer
    Scene
    Vendor/entt
    Vendor/glm  
    Vendor/glad/include
    Vendor/KHR
    Vendor/stb
    Vendor/tiny_obj_loader
)

target_link_libraries(CMakeTarget PRIVATE glfw)

if (WIN32)
    target_link_libraries(CMakeTarget PRIVATE opengl32)
endif()
