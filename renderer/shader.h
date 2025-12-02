#include <glad/glad.h>

typedef struct shader {
    uint32_t id;
} shader;

shader* create_shader(char* vertex_shader_path, char* fragment_shader_path);
void destroy_shader(shader* shader);
void use_shader(shader* shader);

