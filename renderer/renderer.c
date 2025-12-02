#include <renderer.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

void draw_entity(entity_id e, shader* shader) {
    transform* t = get_component(e, TRANSFORM);
    renderable* r = get_component(e, RENDERABLE);

    mat4 model;
    glm_mat4_identity(model);

    glm_translate(model, t->pos);

    glm_rotate(model, t->rot[0], (vec3){1.0f, 0.0f, 0.0f});
    glm_rotate(model, t->rot[1], (vec3){0.0f, 1.0f, 0.0f});
    glm_rotate(model, t->rot[2], (vec3){0.0f, 0.0f, 1.0f});

    glm_scale(model, t->scale);

    set_mat4(shader, "model", model);
    draw_mesh(r->mesh);
}

void draw_mesh(mesh* mesh) {
    if(mesh->texture) bind_texture(mesh->texture);
    if(!mesh) return;
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

    glEnable(GL_DEPTH_TEST);

    m_renderer->background_color = background_color;
    return m_renderer;
}

void clear_screen(renderer* renderer) {
    vec4* color = renderer->background_color;
    glClearColor((*color)[0], (*color)[1], (*color)[2], (*color)[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void destroy_renderer(renderer* renderer) {
    free(renderer->background_color);
    free(renderer);
}
