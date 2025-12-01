#ifndef CONTEXT
#define CONTEXT

#include <renderer.h>
#include <window.h>

typedef struct Context {
    Window* window;
    Renderer* renderer;
} Context;

Context* create_context(int width, int height, const char* title);
void destroy_context(Context* context);


#endif
