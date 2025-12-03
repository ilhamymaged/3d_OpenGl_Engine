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

     m_scene->shadow_shader = create_shader("../shaders/shadow.v", "../shaders/shadow.f");
    if(!m_scene->shadow_shader) {
        printf("failed to create shadow shader\n");
        destroy_shader(m_scene->shader);
        destroy_renderer(m_scene->renderer);
        free(m_scene);
        return NULL;
    }

    m_scene->quad_shader = create_shader("../shaders/quad.v", "../shaders/quad.f");
    if(!m_scene->quad_shader) {
        printf("failed to create quad shader\n");
        destroy_shader(m_scene->shader);
        destroy_shader(m_scene->shadow_shader);
        destroy_renderer(m_scene->renderer);
        free(m_scene);
        return NULL;
    }

    vec3 cam_pos = {0.0f, 1.0f, 3.0f};
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

    vertex quad_vertices[] = {
        // positions         // normals // texCoords // color
        { {-1.0f,  1.0f, 0.0f}, {0,0,0}, {0.0f, 1.0f}, {1,1,1} }, // top-left
        { {-1.0f, -1.0f, 0.0f}, {0,0,0}, {0.0f, 0.0f}, {1,1,1} }, // bottom-left
        { { 1.0f, -1.0f, 0.0f}, {0,0,0}, {1.0f, 0.0f}, {1,1,1} }, // bottom-right
        { { 1.0f,  1.0f, 0.0f}, {0,0,0}, {1.0f, 1.0f}, {1,1,1} }, // top-right
    };

    uint32_t quad_indices[] = {
        0, 1, 2,
        0, 2, 3
    };


    // 36 vertices (6 faces × 2 triangles × 3 vertices)
    vertex cube_vertices[] = {
        // ---- Front face ----
        { { -0.5f, -0.5f,  0.5f }, { 0, 0, 1 }, {0, 0}, {1, 0, 0} },
        { {  0.5f, -0.5f,  0.5f }, { 0, 0, 1 }, {1, 0}, {1, 0, 0} },
        { {  0.5f,  0.5f,  0.5f }, { 0, 0, 1 }, {1, 1}, {1, 0, 0} },

        { { -0.5f, -0.5f,  0.5f }, { 0, 0, 1 }, {0, 0}, {1, 0, 0} },
        { {  0.5f,  0.5f,  0.5f }, { 0, 0, 1 }, {1, 1}, {1, 0, 0} },
        { { -0.5f,  0.5f,  0.5f }, { 0, 0, 1 }, {0, 1}, {1, 0, 0} },

        // ---- Back face ----
        { {  0.5f, -0.5f, -0.5f }, { 0, 0,-1 }, {0, 0}, {0, 1, 0} },
        { { -0.5f, -0.5f, -0.5f }, { 0, 0,-1 }, {1, 0}, {0, 1, 0} },
        { { -0.5f,  0.5f, -0.5f }, { 0, 0,-1 }, {1, 1}, {0, 1, 0} },

        { {  0.5f, -0.5f, -0.5f }, { 0, 0,-1 }, {0, 0}, {0, 1, 0} },
        { { -0.5f,  0.5f, -0.5f }, { 0, 0,-1 }, {1, 1}, {0, 1, 0} },
        { {  0.5f,  0.5f, -0.5f }, { 0, 0,-1 }, {0, 1}, {0, 1, 0} },

        // ---- Left face ----
        { { -0.5f, -0.5f, -0.5f }, {-1, 0, 0 }, {0, 0}, {0, 0, 1} },
        { { -0.5f, -0.5f,  0.5f }, {-1, 0, 0 }, {1, 0}, {0, 0, 1} },
        { { -0.5f,  0.5f,  0.5f }, {-1, 0, 0 }, {1, 1}, {0, 0, 1} },

        { { -0.5f, -0.5f, -0.5f }, {-1, 0, 0 }, {0, 0}, {0, 0, 1} },
        { { -0.5f,  0.5f,  0.5f }, {-1, 0, 0 }, {1, 1}, {0, 0, 1} },
        { { -0.5f,  0.5f, -0.5f }, {-1, 0, 0 }, {0, 1}, {0, 0, 1} },

        // ---- Right face ----
        { { 0.5f, -0.5f,  0.5f }, {1, 0, 0 }, {0, 0}, {1, 1, 0} },
        { { 0.5f, -0.5f, -0.5f }, {1, 0, 0 }, {1, 0}, {1, 1, 0} },
        { { 0.5f,  0.5f, -0.5f }, {1, 0, 0 }, {1, 1}, {1, 1, 0} },

        { { 0.5f, -0.5f,  0.5f }, {1, 0, 0 }, {0, 0}, {1, 1, 0} },
        { { 0.5f,  0.5f, -0.5f }, {1, 0, 0 }, {1, 1}, {1, 1, 0} },
        { { 0.5f,  0.5f,  0.5f }, {1, 0, 0 }, {0, 1}, {1, 1, 0} },

        // ---- Top face ----
        { { -0.5f, 0.5f,  0.5f }, {0, 1, 0 }, {0, 0}, {1, 0, 1} },
        { {  0.5f, 0.5f,  0.5f }, {0, 1, 0 }, {1, 0}, {1, 0, 1} },
        { {  0.5f, 0.5f, -0.5f }, {0, 1, 0 }, {1, 1}, {1, 0, 1} },

        { { -0.5f, 0.5f,  0.5f }, {0, 1, 0 }, {0, 0}, {1, 0, 1} },
        { {  0.5f, 0.5f, -0.5f }, {0, 1, 0 }, {1, 1}, {1, 0, 1} },
        { { -0.5f, 0.5f, -0.5f }, {0, 1, 0 }, {0, 1}, {1, 0, 1} },

        // ---- Bottom face ----
        { { -0.5f, -0.5f, -0.5f }, {0,-1, 0 }, {0, 0}, {0, 1, 1} },
        { {  0.5f, -0.5f, -0.5f }, {0,-1, 0 }, {1, 0}, {0, 1, 1} },
        { {  0.5f, -0.5f,  0.5f }, {0,-1, 0 }, {1, 1}, {0, 1, 1} },

        { { -0.5f, -0.5f, -0.5f }, {0,-1, 0 }, {0, 0}, {0, 1, 1} },
        { {  0.5f, -0.5f,  0.5f }, {0,-1, 0 }, {1, 1}, {0, 1, 1} },
        { { -0.5f, -0.5f,  0.5f }, {0,-1, 0 }, {0, 1}, {0, 1, 1} },
    };

    uint32_t cube_indices[] = {
        0,1,2, 3,4,5,
        6,7,8, 9,10,11,
        12,13,14, 15,16,17,
        18,19,20, 21,22,23,
        24,25,26, 27,28,29,
        30,31,32, 33,34,35
    };

    texture* tex = create_texture("../assets/textures/wall.jpg");
    texture* ground_tex = create_texture("../assets/textures/wall.jpg");
    if(!tex) {
        printf("failed to create tex\n");
        destroy_renderer(m_scene->renderer);
        destroy_shader(m_scene->shader);
        destroy_camera(m_scene->camera);
        destroy_input(m_scene->input);
        free(m_scene);
        return NULL;
    }

    mesh* cube_mesh = create_mesh(
                cube_vertices, 36,
                cube_indices,  36,
                tex
                );
    if(!cube_mesh) {
        printf("failed to create mesh\n");
        destroy_renderer(m_scene->renderer);
        destroy_shader(m_scene->shader);
        destroy_camera(m_scene->camera);
        destroy_texture(tex);
        free(m_scene);
        return NULL;
    }

    m_scene->quad_mesh = create_mesh(
                quad_vertices, 4,
                quad_indices,  6,
                NULL
    );
    if(!m_scene->quad_mesh) {
        printf("failed to create mesh\n");
        destroy_renderer(m_scene->renderer);
        destroy_shader(m_scene->shader);
        destroy_camera(m_scene->camera);
        destroy_texture(tex);
        free(m_scene);
        return NULL;
    }

    mesh* plane_mesh = create_plane(50.0f, 50.0f, ground_tex);
    if(!plane_mesh) {
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
    m_scene->plane_entity = create_entity(); 

    transform t = {
        .pos = {0.0f, 1.0f, 0.0f},
        .rot = {0, 0, 0},
        .scale = {1, 1, 1}
    };

    transform t2 = {
        .pos = {1.0f, 2.0f, 0.0f},
        .rot = {0, 0, 0},
        .scale = {1, 1, 1}
    };

    transform ground_trans = {
        .pos = {0.0f, 0.0f, 0.0f},
        .rot = {0, 0, 0},
        .scale = {1, 1, 1}
    };

    renderable r = {
        .mesh = cube_mesh
    };

    renderable ground_r = {
        .mesh = plane_mesh
    };

    add_component(m_scene->entity, TRANSFORM, &t);
    add_component(m_scene->entity, RENDERABLE, &r);
    
    add_component(m_scene->cube, TRANSFORM, &t2);
    add_component(m_scene->cube, RENDERABLE, &r);

    add_component(m_scene->plane_entity, TRANSFORM, &ground_trans);
    add_component(m_scene->plane_entity, RENDERABLE, &ground_r);

    m_scene->shadow_map = create_shadow_map(render_pass, 1024, 1024);
    if(!m_scene->shadow_map) {
        printf("failed to create shadow_map\n");
        destroy_renderer(m_scene->renderer);
        destroy_shader(m_scene->shader);
        destroy_camera(m_scene->camera);
        destroy_texture(tex);
        free(m_scene);
        return NULL;
    }

    return m_scene;
}

void render_pass(scene* scene) {
    use_shader(scene->shadow_shader);

    mat4 lightView;
    glm_mat4_identity(lightView);
    
    vec3 eye = {20.0f, 20.0f, 20.0f};
    vec3 center = {0.0f, 0.0f, 0.0f};
    vec3 up = {0.0f, 1.0f, 0.0f};
    glm_lookat(eye, center, up, lightView);
    set_mat4(scene->shadow_shader, "view", lightView);

    float near_plane = 0.1, far_plane = 50.0f;
    mat4 light_projection;
    glm_mat4_identity(light_projection);
    glm_ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane, light_projection);
    set_mat4(scene->shadow_shader, "projection", light_projection);

    glm_mat4_mul(light_projection, lightView, scene->shadow_map->lightSpaceMatrix);

    draw_entity(scene->entity, scene->shadow_shader);
    draw_entity(scene->cube, scene->shadow_shader);
    draw_entity(scene->plane_entity, scene->shadow_shader);
}

void update_scene(scene* scene, float delta_time) {
    update_input(scene->input);

    update_camera(scene->camera, delta_time, scene->input, 
            scene->input->mouseDeltaX, scene->input->mouseDeltaY);
}

void render_scene(scene* scene) {

    shadow_pass(scene->shadow_map, scene);

    glViewport(0, 0, 1600, 900);
    clear_buffer(COLOR_BUFFER | DEPTH_BUFFER);
    clear_color(scene->renderer);
    use_shader(scene->shader);

    mat4 view;
    glm_mat4_identity(view);
    get_view_matrix(scene->camera, view);
    set_mat4(scene->shader, "view", view);

    mat4 projection;
    glm_mat4_identity(projection);
    get_projection_matrix(scene->camera, projection);
    set_mat4(scene->shader, "projection", projection);

    set_vec3(scene->shader, "viewPos", scene->camera->position);

    vec3 lightDir = {1.0f, 1.0f, 1.0f};
    glm_vec3_normalize(lightDir);
    set_vec3(scene->shader, "lightDir", lightDir);

    set_mat4(scene->shader, "lightSpaceMatrix", scene->shadow_map->lightSpaceMatrix);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, scene->shadow_map->depthMapTex);
    set_int(scene->shader, "depthMap", 1);

    draw_entity(scene->entity, scene->shader);
    draw_entity(scene->cube, scene->shader);
    draw_entity(scene->plane_entity, scene->shader);

    // glDisable(GL_DEPTH_TEST);
    // glActiveTexture(GL_TEXTURE0);
    // use_shader(scene->quad_shader);
    // set_int(scene->quad_shader, "depthMap", 0);
    // glBindTexture(GL_TEXTURE_2D, scene->shadow_map->depthMapTex);
    // draw_mesh(scene->quad_mesh);
}

void destroy_scene(scene* scene) {
    //free it once
    renderable* r = get_component(scene->entity, RENDERABLE);
    destroy_mesh(r->mesh);
    renderable* r1 = get_component(scene->plane_entity, RENDERABLE);
    destroy_mesh(r1->mesh);

    destroy_mesh(scene->quad_mesh);

    destroy_camera(scene->camera);
    destroy_shader(scene->shader);
    destroy_shader(scene->quad_shader);
    destroy_shader(scene->shadow_shader);
    destroy_renderer(scene->renderer);
    destroy_input(scene->input);
    destroy_shadow_map(scene->shadow_map);

    free(scene);
}
