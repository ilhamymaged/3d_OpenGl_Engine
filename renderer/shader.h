#ifndef SHADER
#define SHADER

#include <glad/glad.h>
#include <cglm/cglm.h>

typedef struct shader {
    uint32_t id;
} shader;

shader* create_shader(char* vertex_shader_path, char* fragment_shader_path);
void destroy_shader(shader* shader);
void use_shader(shader* shader);

void set_mat4(shader* shader, const char* name, mat4 value);
void set_vec3(shader* shader, const char* name, vec3 value);
void set_int(shader* shader, const char* name, int value);

#endif

