#include <renderer.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

Renderer* create_renderer(vec4* background_color) {
    Renderer* renderer = malloc(sizeof(Renderer));

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("FAILED TO LOAD GLAD\n");
        destroy_renderer(renderer);
        return NULL;
    }

    renderer->background_color = background_color;
    return renderer;
}

void clear_screen(Renderer* renderer) {
    vec4* color = renderer->background_color;
    glClearColor((*color)[0], (*color)[1], (*color)[2], (*color)[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}

void destroy_renderer(Renderer* renderer) {
    free(renderer->background_color);
    free(renderer);
}
