#include <glad/glad.h>
#include <window.h>
#include <stdio.h>
#include <stdlib.h>

void update_window(window* window) {
    glfwPollEvents();
    glfwSwapBuffers(window->frame);
}

window* create_window(int width, int height, const char* title) {

    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return NULL;
    }

    window* m_window = malloc(sizeof(window));
    if(!m_window) return NULL;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window->frame = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!m_window->frame) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        free(m_window);
        return NULL;
    }

    glfwMakeContextCurrent(m_window->frame);
    glfwSetFramebufferSizeCallback(m_window->frame, framebuffer_size_callback);
    glfwSetInputMode(m_window->frame, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    m_window->width = width;
    m_window->height = height;
    return m_window;
}

void destroy_window(window* window) {
    if(!window) return;
    glfwDestroyWindow(window->frame);
    free(window);
}

void close_window(window* window) {
    glfwSetWindowShouldClose(window->frame, true);
}

bool should_window_close(window* window) {
    return glfwWindowShouldClose(window->frame);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
