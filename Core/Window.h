#include <stdbool.h>
#include <GLFW/glfw3.h>

typedef struct Window {
    int width;
    int height;
    const char* title;
    GLFWwindow* frame;
} Window;


Window* create_window(int width, int height, const char* title);
bool should_window_close(Window* window);
void destroy_window(Window* window);
