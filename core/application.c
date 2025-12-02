#include <application.h>
#include <stdlib.h>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <time.h>


void run_application(application* app) {
    while(!should_window_close(app->context->window)) {
        Time_Update();

        if(glfwGetKey(app->context->window->frame, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            close_window(app->context->window);

        render_scene(app->context->scene, GetDeltaTime());
        update_window(app->context->window);
    }
}

application* create_application(int width, int height, const char* title) {

    application* app = malloc(sizeof(application));
    if(!app) return NULL;

    app->context = create_context(width, height, title); 
    if (!app->context) {
        printf("Failed to create context\n");
        free(app);
        return NULL;
    }

    return app;
}

void destroy_application(application* app) {
    destroy_context(app->context);
    free(app);
    glfwTerminate();
}
