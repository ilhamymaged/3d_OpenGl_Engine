#include <context.h>
#include <stdlib.h>
#include <cglm/cglm.h>

Context* create_context(int width, int height, const char* title) {
    Context* context = malloc(sizeof(Context));
    if(!context) return NULL;

    context->window = create_window(width, height, title);

    vec4* color = malloc(sizeof(vec4));
    (*color)[0] = 0.1f;
    (*color)[1] = 0.2f;
    (*color)[2] = 0.3f;
    (*color)[3] = 1.0f;

    context->renderer = create_renderer(color);
    return context;
}

void destroy_context(Context* context) {
    destroy_window(context->window);
    destroy_renderer(context->renderer);
    free(context);
}
