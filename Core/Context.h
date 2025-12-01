#include <Window.h>

typedef struct Context {
    Window* window;
} Context;

Context* create_context(int width, int height, const char* title);
void destroy_context(Context* context);
