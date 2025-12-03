#pragma once

#include <renderer.h>
#include <camera.h>
#include <shader.h>
#include <inputs.h>
#include <shadow_map.h>

typedef struct scene {
    renderer* renderer;
    shader* shader;
    shader* shadow_shader;
    shader* quad_shader;
    camera* camera;
    input* input;
    entity_id entity;
    entity_id cube;
    entity_id plane_entity;
    shadow_map* shadow_map;

    mesh* quad_mesh;
} scene;

scene* create_scene();
void update_scene(scene* scene, float delta_time);
void render_scene(scene* scene);
void add_mesh(scene* s, mesh* mesh);
void destroy_scene(scene* scene);
void render_pass(scene* scene);