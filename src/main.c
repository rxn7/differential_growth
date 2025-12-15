#include "app.h"

int main() {
    struct App app;

    app_init(&app);
    app_run(&app);
    app_free(&app);
}
