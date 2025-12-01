#ifndef APP
#define APP

#include <context.h>

typedef struct Application {
    Context* context;
} Application;

Application* create_application(int width, int height, const char* title);
void destroy_application(Application* app);
void run_application(Application* app);


#endif
