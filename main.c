#include <Window.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1

int main() {
    Window* window = create_window(1280, 720, "Test");
    if(!window) return EXIT_FAILURE;
    destroy_window(window);
    return EXIT_SUCCESS;
}
