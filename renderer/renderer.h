#ifndef RENDERER
#define RENDERER

#include <glad/glad.h>
#include <cglm/cglm.h>
#include <entity.h>
#include <shader.h>
#include <mesh.h>

#define DEPTH_BUFFER GL_DEPTH_BUFFER_BIT
#define COLOR_BUFFER GL_COLOR_BUFFER_BIT

typedef struct renderer {
    vec4* background_color;
} renderer;

renderer* create_renderer(vec4* background_color);
void destroy_renderer(renderer* renderer);
void clear_color(renderer* renderer);
void clear_buffer(int buffer);

void draw_mesh(mesh* mesh);
void draw_entity(entity_id e, shader* shader);

#endif
