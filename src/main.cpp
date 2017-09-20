#include "AppRunner.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

    try {
        auto app = new AppRunner("OpenGL test", 900, 1600);
        app->run();
    } catch (std::runtime_error &error) {
        cerr << error.what() << endl;
        return EXIT_FAILURE;
    } catch (...) {
        cerr << "Unknown error" << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
