#include <renderer.h>
#include <camera.h>
#include <shader.h>
#include <inputs.h>

typedef struct scene {
    renderer* renderer;
    mesh** meshes;
    size_t mesh_count;
    shader* shader;
    camera* camera;
    input* input;
} scene;

scene* create_scene();
void render_scene(scene* scene, float delta_time);
void add_mesh(scene* s, mesh* mesh);
void destroy_scene(scene* scene);
