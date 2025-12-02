#include <renderer.h>
#include <shader.h>

typedef struct scene {
    renderer* renderer;
    mesh** meshes;
    size_t mesh_count;
    shader* shader;
} scene;

scene* create_scene();
void render_scene(scene* scene);
void add_mesh(scene* s, mesh* mesh);
void destroy_scene(scene* scene);
