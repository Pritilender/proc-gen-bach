#include "AppRunner.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
    AppRunner *app;

    try {
        app = new AppRunner("OpenGL test", 800, 1280);
    } catch (std::runtime_error &error) {
        std::cerr << error.what() << std::endl;
        return EXIT_FAILURE;
    }

    app->run();
    delete app;

    return EXIT_SUCCESS;
}
