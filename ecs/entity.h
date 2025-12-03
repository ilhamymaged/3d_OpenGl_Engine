#include <component.h>
#include <stdint.h>

typedef uint32_t entity_id;

entity_id create_entity();
void add_component(entity_id e, component_type type, void* data);
void remove_component(entity_id e, component_type type);
void* get_component(entity_id e, component_type type);
bool has_component(entity_id e, component_type type);
