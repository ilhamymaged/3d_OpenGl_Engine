#include "camera.h"
#include <stdlib.h>
#include <cglm/cglm.h>

camera* create_camera(vec3 position, vec3 up, float yaw, float pitch) {
    camera* cam = malloc(sizeof(camera));
    if (!cam) return NULL;

    glm_vec3_copy(position, cam->position);
    glm_vec3_copy(up, cam->worldUp);

    glm_vec3_zero(cam->front);
    cam->front[2] = -1.0f; // initial front pointing -Z

    cam->yaw = yaw;
    cam->pitch = pitch;
    cam->speed = 5.0f;
    cam->sensitivity = 0.1f;
    cam->zoom = 45.0f;
    cam->active = true;

    // Initial right and up
    glm_vec3_cross(cam->front, cam->worldUp, cam->right);
    glm_vec3_normalize(cam->right);
    glm_vec3_cross(cam->right, cam->front, cam->up);
    glm_vec3_normalize(cam->up);

    return cam;
}

void update_camera(camera* cam, float deltaTime, const bool* keys, float mouseDeltaX, float mouseDeltaY) {
    if (!cam || !cam->active) return;

    // Mouse movement
    cam->yaw += mouseDeltaX * cam->sensitivity;
    cam->pitch -= mouseDeltaY * cam->sensitivity;

    if (cam->pitch > 89.0f) cam->pitch = 89.0f;
    if (cam->pitch < -89.0f) cam->pitch = -89.0f;

    // Update front vector
    cam->front[0] = cosf(glm_rad(cam->yaw)) * cosf(glm_rad(cam->pitch));
    cam->front[1] = sinf(glm_rad(cam->pitch));
    cam->front[2] = sinf(glm_rad(cam->yaw)) * cosf(glm_rad(cam->pitch));
    glm_vec3_normalize(cam->front);

    // Update right and up
    glm_vec3_cross(cam->front, cam->worldUp, cam->right);
    glm_vec3_normalize(cam->right);
    glm_vec3_cross(cam->right, cam->front, cam->up);
    glm_vec3_normalize(cam->up);

    // Keyboard movement
    float velocity = cam->speed * deltaTime;
    if (keys[87]) { // W
        vec3 temp;
        glm_vec3_scale(cam->front, velocity, temp);
        glm_vec3_add(cam->position, temp, cam->position);
    }
    if (keys[83]) { // S
        vec3 temp;
        glm_vec3_scale(cam->front, velocity, temp);
        glm_vec3_sub(cam->position, temp, cam->position);
    }
    if (keys[65]) { // A
        vec3 temp;
        glm_vec3_scale(cam->right, velocity, temp);
        glm_vec3_sub(cam->position, temp, cam->position);
    }
    if (keys[68]) { // D
        vec3 temp;
        glm_vec3_scale(cam->right, velocity, temp);
        glm_vec3_add(cam->position, temp, cam->position);
    }
}

void get_view_matrix(camera* cam, mat4 view) {
    glm_lookat(cam->position, (vec3){cam->position[0] + cam->front[0], cam->position[1] + cam->front[1], cam->position[2] + cam->front[2]}, cam->up, view);
}

void get_projection_matrix(camera* cam, mat4 proj) {
    glm_perspective(glm_rad(45.0f), (float)1280/720, 0.1f, 100.0f, proj);
}

void destroy_camera(camera* cam) {
    if (cam) free(cam);
}

