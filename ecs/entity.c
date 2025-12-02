#include <entity.h>
#include <stdbool.h>

static transform transforms[MAX_ENTITIES];
static renderable renderables[MAX_ENTITIES];
static bool has_transform[MAX_ENTITIES];
static bool has_renderer[MAX_ENTITIES];

static entity_id id = 0;

entity_id create_entity() {
    return id++;
}

void add_component(entity_id e, component_type type, void* data) {
    switch(type) {
        case TRANSFORM:
            transforms[e] = *(transform*)data;
            has_transform[e] = true;
            break;
        case RENDERABLE:
            renderables[e] = *(renderable*)data;
            has_renderer[e] = true;
            break;
    }
}

void remove_component(entity_id e, component_type type) {
    switch(type) {
        case TRANSFORM:
            has_transform[e] = false;
            break;
        case RENDERABLE:
            has_renderer[e] = false;
            break;
    }

}

void* get_component(entity_id e, component_type type) {
    switch(type) {
        case TRANSFORM:
            return has_transform[e] ? &transforms[e] : NULL;
        case RENDERABLE:
            return has_renderer[e] ? &renderables[e] : NULL;
    }

    return NULL;
}
