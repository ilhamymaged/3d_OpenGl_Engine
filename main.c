#include <application.h>

int main() {
    application* app = create_application(1600, 900, "Test");
    if(!app) return EXIT_FAILURE;
    run_application(app);
    destroy_application(app);
    return EXIT_SUCCESS;
}
