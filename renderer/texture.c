#include <glad/glad.h>
#include <texture.h>
#include <stb_image.h>
#include <stdio.h>

texture* create_texture(const char* path) {
    texture* tex = malloc(sizeof(texture));
    if(!tex) return NULL;

    glGenTextures(1, &tex->id);
    glBindTexture(GL_TEXTURE_2D, tex->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
        printf("Failed to load texture\n");
    stbi_image_free(data);

    return tex;
}

void bind_texture(texture* texture) {
    glBindTexture(GL_TEXTURE_2D, texture->id);
}

void destroy_texture(texture* texture) {
    glDeleteTextures(1, &texture->id);
    free(texture);
}
