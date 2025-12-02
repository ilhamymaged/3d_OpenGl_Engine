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

    m_scene->entity = create_entity();
    transform t = {
        .pos = {0.0f, 0.0f, 0.0f},
        .rot = {0, 0, 0},
        .scale = {1, 1, 1}
    };

    renderable r = {
        .mesh = triangle_mesh
    };

    add_component(m_scene->entity, TRANSFORM, &t);
    add_component(m_scene->entity, RENDERABLE, &r);
    return m_scene;
}

void update_scene(scene* scene, float delta_time) {
    update_input(scene->input);

    update_camera(scene->camera, delta_time, scene->input->keys, 
            scene->input->mouseDeltaX, scene->input->mouseDeltaY);

    //transform* t = get_component(scene->entity, TRANSFORM);
    //if(is_key_pressed(scene->input, RIGHT_KEY)) {
     //   vec3 v = {1.0f, 0.0f, 0.0f};
      //  glm_vec3_add(v, t->pos, t->pos);
    //}
}

void render_scene(scene* scene) {
    clear_screen(scene->renderer);
    use_shader(scene->shader);

    mat4 view;
    glm_mat4_identity(view);
    get_view_matrix(scene->camera, view);

    mat4 projection;
    glm_mat4_identity(projection);
    get_projection_matrix(scene->camera, projection);

    draw_entity(scene->entity, scene->shader);
}

void destroy_scene(scene* scene) {
    renderable* r = get_component(scene->entity, RENDERABLE);
    destroy_mesh(r->mesh);
    destroy_camera(scene->camera);
    destroy_shader(scene->shader);
    destroy_renderer(scene->renderer);
    destroy_input(scene->input);

    free(scene);
}
