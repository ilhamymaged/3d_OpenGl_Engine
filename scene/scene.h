#ifndef SCENE
#define SCENE

#include <renderer.h>
#include <camera.h>
#include <shader.h>
#include <inputs.h>

typedef struct scene {
    renderer* renderer;
    shader* shader;
    camera* camera;
    input* input;
    entity_id entity;
} scene;

scene* create_scene();
void update_scene(scene* scene, float delta_time);
void render_scene(scene* scene);
void add_mesh(scene* s, mesh* mesh);
void destroy_scene(scene* scene);

#endif
