#include <Window.h>
#include <stdio.h>
#include <stdlib.h>

Window* create_window(int width, int height, const char* title) {

    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return NULL;
    }

    Window* window = malloc(sizeof(Window));
    if(!window) return NULL;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window->frame = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window->frame) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        free(window);
        return NULL;
    }

    glfwMakeContextCurrent(window->frame);
    window->width = width;
    window->height = height;
    return window;
}

void destroy_window(Window* window) {
    if(!window) return;
    glfwDestroyWindow(window->frame);
    free(window);
}

bool should_window_close(Window* window) {
    return glfwWindowShouldClose(window->frame);
}

