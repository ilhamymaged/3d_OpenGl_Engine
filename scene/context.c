#include <context.h>
#include <stdlib.h>
#include <cglm/cglm.h>

context* create_context(int width, int height, const char* title) {
    context* cont = malloc(sizeof(context));
    if(!cont) return NULL;

    cont->window = create_window(width, height, title);
    if(!cont->window) {
        printf("failed to create a window\n");
        free(cont);
        return NULL;
    }

    cont->scene = create_scene();
    if(!cont->window) {
        printf("failed to create a scene\n");
        destroy_window(cont->window);
        free(cont);
        return NULL;
    }
    return cont;
}

void destroy_context(context* context) {
    destroy_window(context->window);
    destroy_scene(context->scene);
    free(context);
}
