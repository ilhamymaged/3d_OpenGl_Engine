cmake_minimum_required (VERSION 3.10)
project ("gameEngine")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS core/*.c renderer/*.c editor/*.c scene/*.c utility/*.c)
list(APPEND SRC_FILES main.c vendor/glad/src/glad.c
vendor/stb/stb_image.c vendor/tiny_obj_loader/tiny_obj_loader.cpp)

add_executable (CMakeTarget ${SRC_FILES})

target_include_directories(CMakeTarget PRIVATE 
    core
    editor
    renderer
    scene
    utility
    vendor/entt
    vendor/glm
    vendor/glad/include
    vendor/KHR
    vendor/stb
    vendor/tiny_obj_loader
    vendor/glfw/include
    vendor/cglm/include
)
add_library(glfw3 STATIC IMPORTED)
set_target_properties(glfw3 PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/vendor/glfw/build/src/libglfw3.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/vendor/glfw/include"
)

target_link_libraries(CMakeTarget PRIVATE glfw3)

if (WIN32)
    target_link_libraries(CMakeTarget PRIVATE opengl32)
endif()
