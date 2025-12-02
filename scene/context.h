#ifndef CONTEXT
#define CONTEXT

#include <scene.h>
#include <window.h>

typedef struct context {
    window* window;
    scene* scene;
} context;

context* create_context(int width, int height, const char* title);
void destroy_context(context* context);


#endif

