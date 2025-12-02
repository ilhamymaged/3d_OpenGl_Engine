#ifndef APP
#define APP

#include <context.h>

typedef struct application {
    context* context;
} application;

application* create_application(int width, int height, const char* title);
void destroy_application(application* app);
void run_application(application* app);

#endif
