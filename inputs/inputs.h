#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

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
