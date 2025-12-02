#include "time.h"
#include <GLFW/glfw3.h>

static double lastTime = 0.0;
static float deltaTime = 0.0f;

void Time_Update() {
    double currentTime = glfwGetTime();
    deltaTime = (float)(currentTime - lastTime);
    lastTime = currentTime;
}

float GetDeltaTime() {
    return deltaTime;
}

