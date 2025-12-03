#pragma once
#include <stdint.h>
#include <cglm/cglm.h>

typedef struct scene scene;

typedef struct shadow_map{
    uint32_t width;
    uint32_t height;
    uint32_t depthMapTex;
    uint32_t depthMapFBO;
    mat4 lightSpaceMatrix;

    void (*render_scene)(scene* scene);

} shadow_map;

shadow_map* create_shadow_map(void(*render_func)(scene* scene), uint32_t width, uint32_t height);
void shadow_pass(shadow_map* map, scene* scene);
void destroy_shadow_map(shadow_map* shadow);