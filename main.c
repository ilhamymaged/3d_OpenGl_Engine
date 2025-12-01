#include <application.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1

int main() {
    Application* app = create_application(1280, 720, "Test");
    if(!app) return EXIT_FAILURE;
    run_application(app);
    destroy_application(app);
    return EXIT_SUCCESS;
}
