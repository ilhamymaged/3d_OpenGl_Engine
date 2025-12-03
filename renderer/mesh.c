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
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(vertex, color));
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    return m;
}

mesh* create_plane(float size, int resolution, texture* tex) {
    int verts_per_side = resolution + 1;
    int vertex_count   = verts_per_side * verts_per_side;
    int index_count    = resolution * resolution * 6;

    vertex* vertices = malloc(sizeof(vertex) * vertex_count);
    uint32_t* indices = malloc(sizeof(uint32_t) * index_count);

    if (!vertices || !indices) {
        free(vertices);
        free(indices);
        return NULL;
    }

    float half = size * 0.5f;
    float step = size / resolution;

    // ---- Generate vertices ----
    int v = 0;
    for (int z = 0; z <= resolution; z++) {
        for (int x = 0; x <= resolution; x++) {

            float worldX = -half + x * step;
            float worldZ = -half + z * step;

            vertices[v].pos[0] = worldX;
            vertices[v].pos[1] = 0.0f;    // flat plane
            vertices[v].pos[2] = worldZ;

            vertices[v].normals[0] = 0;
            vertices[v].normals[1] = 1;
            vertices[v].normals[2] = 0;

            // Tile UVs to avoid stretching
            vertices[v].tex_coords[0] = (float)x / resolution * 20.0f;
            vertices[v].tex_coords[1] = (float)z / resolution * 20.0f;

            vertices[v].color[0] = 1;
            vertices[v].color[1] = 1;
            vertices[v].color[2] = 1;

            v++;
        }
    }

    // ---- Generate indices (2 triangles per quad) ----
    int idx = 0;
    for (int z = 0; z < resolution; z++) {
        for (int x = 0; x < resolution; x++) {
            uint32_t i0 =  z      * verts_per_side + x;
            uint32_t i1 =  z      * verts_per_side + (x + 1);
            uint32_t i2 = (z + 1) * verts_per_side + x;
            uint32_t i3 = (z + 1) * verts_per_side + (x + 1);

            // Triangle 1
            indices[idx++] = i0;
            indices[idx++] = i1;
            indices[idx++] = i2;

            // Triangle 2
            indices[idx++] = i1;
            indices[idx++] = i3;
            indices[idx++] = i2;
        }
    }

    // ---- Create GPU mesh ----
    mesh* plane_mesh = create_mesh(vertices, vertex_count, indices, index_count, tex);

    free(vertices);
    free(indices);

    return plane_mesh;
}


void destroy_mesh(mesh* mesh) {

    destroy_texture(mesh->texture);

    glDeleteVertexArrays(1, &mesh->VAO);
    glDeleteBuffers(1, &mesh->VBO);
    glDeleteBuffers(1, &mesh->EBO);

    free(mesh);
}

