#include <scene.h>
#include <stdlib.h>

scene* create_scene() {
    scene* m_scene = malloc(sizeof(scene));
    if(!m_scene) return NULL;

    vec4* color = malloc(sizeof(vec4));
    if (!color) { free(m_scene); return NULL; } 
    (*color)[0] = 0.1f;
    (*color)[1] = 0.2f;
    (*color)[2] = 0.3f;
    (*color)[3] = 1.0f;

    m_scene->renderer = create_renderer(color);
    if(!m_scene->renderer) {
        printf("failed to create renderer\n");
        free(color);
        free(m_scene);
        return NULL;
    }

    m_scene->shader = create_shader("../shaders/triangle.v", "../shaders/triangle.f");
    if(!m_scene->shader) {
        printf("failed to create shader\n");
        destroy_renderer(m_scene->renderer);
        free(m_scene);
        return NULL;
    }

    vec3 cam_pos = {0.0f, 0.0f, 3.0f};
    vec3 cam_up  = {0.0f, 1.0f, 0.0f};
    m_scene->camera = create_camera(cam_pos, cam_up, -90.0f, 0.0f);
    if(!m_scene->camera) {
        printf("failed to create camera\n");
        destroy_renderer(m_scene->renderer);
        destroy_shader(m_scene->shader);
        free(m_scene);
        return NULL;
    }

    m_scene->input = create_input();
    if(!m_scene->input) {
        printf("failed to create input\n");
        destroy_renderer(m_scene->renderer);
        destroy_shader(m_scene->shader);
        destroy_camera(m_scene->camera);
        free(m_scene);
        return NULL;
    }


    vertex triangle_vertices[] = {
        { { 0.0f,  0.5f, 0.0f },  { 0.0f, 0.0f, 1.0f }, { 0.5f, 1.0f } },
        { {-0.5f, -0.5f, 0.0f },  { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
        { { 0.5f, -0.5f, 0.0f },  { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f } },
    };

    uint32_t triangle_indices[] = { 0, 1, 2 };

    texture* tex = create_texture("../assets/textures/wall.jpg");
    if(!tex) {
        printf("failed to create tex\n");
        destroy_renderer(m_scene->renderer);
        destroy_shader(m_scene->shader);
        destroy_camera(m_scene->camera);
        destroy_input(m_scene->input);
        free(m_scene);
        return NULL;
    }

    mesh* triangle_mesh = create_mesh(
            triangle_vertices, 3,
            triangle_indices,  3,
            tex
            );
    if(!triangle_mesh) {
        printf("failed to create mesh\n");
        destroy_renderer(m_scene->renderer);
        destroy_shader(m_scene->shader);
        destroy_camera(m_scene->camera);
        destroy_texture(tex);
        free(m_scene);
        return NULL;
    }

    m_scene->entity = create_entity();
    m_scene->cube = create_entity();

    transform t = {
        .pos = {0.0f, 0.0f, 0.0f},
        .rot = {0, 0, 0},
        .scale = {1, 1, 1}
    };

    transform t2 = {
        .pos = {1.0f, 2.0f, 0.0f},
        .rot = {0, 0, 0},
        .scale = {1, 1, 1}
    };

    renderable r = {
        .mesh = triangle_mesh
    };

    add_component(m_scene->entity, TRANSFORM, &t);
    add_component(m_scene->entity, RENDERABLE, &r);
    
    add_component(m_scene->cube, TRANSFORM, &t2);
    add_component(m_scene->cube, RENDERABLE, &r);
    return m_scene;
}

void update_scene(scene* scene, float delta_time) {
    update_input(scene->input);

    update_camera(scene->camera, delta_time, scene->input, 
            scene->input->mouseDeltaX, scene->input->mouseDeltaY);
}

void render_scene(scene* scene) {
    clear_screen(scene->renderer);
    use_shader(scene->shader);

    mat4 view;
    glm_mat4_identity(view);
    get_view_matrix(scene->camera, view);
    set_mat4(scene->shader, "view", view);

    mat4 projection;
    glm_mat4_identity(projection);
    get_projection_matrix(scene->camera, projection);
    set_mat4(scene->shader, "projection", projection);

    draw_entity(scene->entity, scene->shader);
    draw_entity(scene->cube, scene->shader);
}

void destroy_scene(scene* scene) {
    //free it once
    renderable* r = get_component(scene->entity, RENDERABLE);
    destroy_mesh(r->mesh);

    destroy_camera(scene->camera);
    destroy_shader(scene->shader);
    destroy_renderer(scene->renderer);
    destroy_input(scene->input);

    free(scene);
}
