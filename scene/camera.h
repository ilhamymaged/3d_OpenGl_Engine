#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/cglm.h>
#include <stdbool.h>
#include <inputs.h>

typedef struct {
    vec3 position;
    vec3 front;
    vec3 up;
    vec3 right;
    vec3 worldUp;
    float yaw;
    float pitch;
    float speed;
    float sensitivity;
    float zoom;
    bool active;
} camera;

camera* create_camera(vec3 position, vec3 up, float yaw, float pitch);
void update_camera(camera* cam, float deltaTime, input* input, float mouseDeltaX, float mouseDeltaY);
void get_view_matrix(camera* cam, mat4 view);
void get_projection_matrix(camera* cam, mat4 proj);
void destroy_camera(camera* cam);

#endif

