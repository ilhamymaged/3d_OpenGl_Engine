#include <inputs.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

input* create_input() {
    input* m_input = malloc(sizeof(input));
    if(!m_input) return NULL;

    for (int i = 0; i < 1024; i++) m_input->keys[i] = false;
    m_input->mouseX = 0;
    m_input->mouseY = 0;
    m_input->mouseDeltaX = 0;
    m_input->mouseDeltaY = 0;
    m_input->firstMouse = true;

    return m_input;
}

void update_input(input* input) {
    for (int i = 0; i < 1024; i++) {
        input->keys[i] = glfwGetKey(glfwGetCurrentContext(), i) == GLFW_PRESS;
    }

    double xpos, ypos;
    glfwGetCursorPos(glfwGetCurrentContext(), &xpos, &ypos);

    if (input->firstMouse) {
        input->mouseX = xpos;
        input->mouseY = ypos;
        input->firstMouse = false;
    }

    input->mouseDeltaX = xpos - input->mouseX;
    input->mouseDeltaY = ypos - input->mouseY;

    input->mouseX = xpos;
    input->mouseY = ypos;
}

void destroy_input(input* input) {
    free(input);
}

bool is_key_pressed(input* input, int key) {
    return input->keys[key];
}

