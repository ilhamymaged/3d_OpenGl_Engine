#include <Context.h>
#include <stdlib.h>

Context* create_context(int width, int height, const char* title) {
    Context* context = malloc(sizeof(Context));
    if(!context) return NULL;

    context->window = create_window(width, height, title);

    return context;
}

void destroy_context(Context* context) {
    destroy_window(context->window);
    free(context);
}
