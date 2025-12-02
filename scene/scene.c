#include <scene.h>
#include <stdlib.h>

scene* create_scene() {
    scene* m_scene = malloc(sizeof(scene));
    if(!m_scene) return NULL;

    vec4* color = malloc(sizeof(vec4));
    (*color)[0] = 0.1f;
    (*color)[1] = 0.2f;
    (*color)[2] = 0.3f;
    (*color)[3] = 1.0f;

    m_scene->renderer = create_renderer(color);

    m_scene->shader = create_shader("../shaders/triangle.v", "../shaders/triangle.f");

    vec3 cam_pos = {0.0f, 0.0f, 3.0f};
    vec3 cam_up  = {0.0f, 1.0f, 0.0f};
    m_scene->camera = create_camera(cam_pos, cam_up, -90.0f, 0.0f);

    m_scene->input = create_input();

    m_scene->meshes = NULL;
    m_scene->mesh_count = 0;

    vertex triangle_vertices[] = {
        { { 0.0f,  0.5f, 0.0f },  { 0.0f, 0.0f, 1.0f }, { 0.5f, 1.0f } },
        { {-0.5f, -0.5f, 0.0f },  { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
        { { 0.5f, -0.5f, 0.0f },  { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f } },
    };

    uint32_t triangle_indices[] = { 0, 1, 2 };

    texture* tex = create_texture("../assets/textures/wall.jpg");

    mesh* triangle_mesh = create_mesh(
            triangle_vertices, 3,
            triangle_indices,  3,
            tex
            );

    add_mesh(m_scene, triangle_mesh);
    return m_scene;
}

void add_mesh(scene* s, mesh* m) {
    s->meshes = realloc(s->meshes, sizeof(mesh*) * (s->mesh_count + 1));
    s->meshes[s->mesh_count++] = m;
}

void render_scene(scene* scene, float delta_time) {
    update_input(scene->input);

    update_camera(scene->camera, delta_time, scene->input->keys, scene->input->mouseDeltaX, scene->input->mouseDeltaY);

    clear_screen(scene->renderer);
    use_shader(scene->shader);

    mat4 view;
    glm_mat4_identity(view);
    get_view_matrix(scene->camera, view);

    mat4 projection;
    glm_mat4_identity(projection);
    get_projection_matrix(scene->camera, projection);

    mat4 model;
    glm_mat4_identity(model);

    set_mat4(scene->shader, "view", view);
    set_mat4(scene->shader, "projection", projection);
    set_mat4(scene->shader, "model", model);

    for(size_t i = 0; i < scene->mesh_count; i++) {
        draw_mesh(scene->meshes[i]);
    }
}

void destroy_scene(scene* scene) {
    for (size_t i = 0; i < scene->mesh_count; i++) {
        destroy_mesh(scene->meshes[i]);
    }

    free(scene->meshes);
    destroy_camera(scene->camera);
    destroy_shader(scene->shader);
    destroy_renderer(scene->renderer);
    destroy_input(scene->input);
    free(scene);
}
