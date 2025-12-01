#ifndef RENDERER
#define RENDERER

#include <glad/glad.h>
#include <cglm/cglm.h>

typedef struct Renderer {
    vec4* background_color;
} Renderer;

Renderer* create_renderer(vec4* background_color);
void destroy_renderer(Renderer* renderer);
void clear_screen(Renderer* renderer);


#endif
