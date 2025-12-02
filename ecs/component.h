#include <cglm/cglm.h>
#include <mesh.h>

#define MAX_ENTITIES 1024

typedef struct {
    vec3 pos;
    vec3 rot;
    vec3 scale;
} transform;

typedef struct {
    mesh* mesh;
} renderable;

typedef enum {
    TRANSFORM,
    RENDERABLE
} component_type;
