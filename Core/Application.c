#include <Application.h>
#include <stdlib.h>
#include <stdio.h>
#include <GLFW/glfw3.h>

void run_application(Application* app) {
    while(!should_window_close(app->context->window)) {
        glfwPollEvents();
        glfwSwapBuffers(app->context->window->frame);
    }
}

Application* create_application(int width, int height, const char* title) {

    Application* app = malloc(sizeof(Application));
    if(!app) return NULL;

    app->context = create_context(width, height, title); 
    if (!app->context) {
        printf("Failed to create context\n");
        free(app);
        return NULL;
    }

    return app;
}

void destroy_application(Application* app) {
    destroy_context(app->context);
    free(app);
}
