#ifndef MESH
#define MESH

#include <cglm/cglm.h>
#include <texture.h>

typedef struct vertex {
    vec3 pos;
    vec3 normals;
    vec2 tex_coords;
    vec3 color;
} vertex;

typedef struct mesh {
    vertex* vertices;
    uint32_t* indices;
    size_t vertecies_count;
    size_t indecies_count;
    texture* texture;

    uint32_t VAO,VBO,EBO;
} mesh;

mesh* create_mesh(vertex* vertices, size_t vertices_count, 
        uint32_t* indices, size_t indices_count,
        texture* texture);
void destroy_mesh(mesh* mesh);
mesh* create_plane(float size, int resolution, texture* tex);

#endif
