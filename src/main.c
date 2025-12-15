#include "app.h"

int main(void) {
    struct App app;

    if(!app_init(&app)) {
        return 1;
    }

    app_run(&app);
    app_free(&app);
}
