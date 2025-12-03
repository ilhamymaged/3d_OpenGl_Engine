#include <shadow_map.h>
#include <stdlib.h>
#include <glad/glad.h>

shadow_map* create_shadow_map(void(*render_func)(scene* scene), uint32_t width, uint32_t height) {
    shadow_map* map = malloc(sizeof(shadow_map));
    if(!map) return NULL;

    map->width = width;
    map->height = height;
    map->render_scene = render_func;
    glm_mat4_identity(map->lightSpaceMatrix);

    glGenFramebuffers(1, &map->depthMapFBO);

    glGenTextures(1, &map->depthMapTex);
    glBindTexture(GL_TEXTURE_2D, map->depthMapTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
                map->width, map->height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  

    glBindFramebuffer(GL_FRAMEBUFFER, map->depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, map->depthMapTex, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        printf("Shadow framebuffer not complete!\n");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);  

    return map;
}

void shadow_pass(shadow_map* map, scene* scene) {
    glViewport(0, 0, map->width, map->height);
    glBindFramebuffer(GL_FRAMEBUFFER, map->depthMapFBO);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    map->render_scene(scene);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void destroy_shadow_map(shadow_map* shadow) {
    glDeleteTextures(1, &shadow->depthMapTex);
    glDeleteFramebuffers(1, &shadow->depthMapFBO);
    free(shadow);
}