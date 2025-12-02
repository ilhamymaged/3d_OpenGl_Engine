#include <mesh.h>
#include <stdlib.h>
#include <glad/glad.h>

mesh* create_mesh(vertex* vertices, size_t vertices_count, uint32_t* indices, size_t indices_count,
        texture* texture){
    mesh* m = malloc(sizeof(mesh));
    if(!m) return NULL;

    m->vertices = vertices;
    m->indices = indices;
    m->vertecies_count = vertices_count;
    m->indecies_count = indices_count;
    m->texture = texture;

    glGenVertexArrays(1, &m->VAO);
    glGenBuffers(1, &m->VBO);
    glGenBuffers(1, &m->EBO);
    glBindVertexArray(m->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m->VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_count * sizeof(vertex), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_count * sizeof(uint32_t), indices, GL_STATIC_DRAW);

    int stride = sizeof(vertex);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(vertex, pos));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(vertex, normals));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(vertex, tex_coords));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    return m;
}


void destroy_mesh(mesh* mesh) {

    destroy_texture(mesh->texture);

    glDeleteVertexArrays(1, &mesh->VAO);
    glDeleteBuffers(1, &mesh->VBO);
    glDeleteBuffers(1, &mesh->EBO);

    free(mesh);
}

