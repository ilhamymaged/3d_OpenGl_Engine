#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <GLFW/glfw3.h>

#define RIGHT_KEY GLFW_KEY_RIGHT
#define LEFT_KEY GLFW_KEY_LEFT
#define UP_KEY GLFW_KEY_UP
#define DOWN_KEY GLFW_KEY_DOWN

typedef struct {
    bool keys[1024];   
    double mouseX;
    double mouseY;
    double mouseDeltaX;
    double mouseDeltaY;
    bool firstMouse;
} input;

input* create_input();
void update_input(input* input);
bool is_key_pressed(input* input, int key);
void destroy_input(input* input);

#endif
