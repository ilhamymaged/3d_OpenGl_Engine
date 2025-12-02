#ifndef TEXTURE
#define TEXTURE


#include <stdint.h>

typedef struct texture {
    uint32_t id;
} texture;

texture* create_texture(const char* path);
void destroy_texture(texture* texture);
void bind_texture(texture* texture);

#endif
