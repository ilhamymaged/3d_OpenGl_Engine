#include <renderer.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

void draw_mesh(mesh* mesh) {
    bind_texture(mesh->texture);
    glBindVertexArray(mesh->VAO);
    glDrawElements(GL_TRIANGLES, mesh->indecies_count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

renderer* create_renderer(vec4* background_color) {
    renderer* m_renderer = malloc(sizeof(renderer));

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("FAILED TO LOAD GLAD\n");
        destroy_renderer(m_renderer);
        return NULL;
    }

    m_renderer->background_color = background_color;
    return m_renderer;
}

void clear_screen(renderer* renderer) {
    vec4* color = renderer->background_color;
    glClearColor((*color)[0], (*color)[1], (*color)[2], (*color)[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}

void destroy_renderer(renderer* renderer) {
    free(renderer->background_color);
    free(renderer);
}
