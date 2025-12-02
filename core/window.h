#ifndef WINDOW
#define WINDOW

#include <stdbool.h>
#include <GLFW/glfw3.h>

typedef struct window {
    int width;
    int height;
    const char* title;
    GLFWwindow* frame;
} window;


window* create_window(int width, int height, const char* title);
bool should_window_close(window* window);
void destroy_window(window* window);
void close_window(window* window);

#endif
