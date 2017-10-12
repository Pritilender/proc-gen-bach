#include <ShaderScene.hpp>
#include <Timer.hpp>
#include <chrono>
#include <NoiseSceneEventHandler.hpp>
#include "AppRunner.hpp"

AppRunner::AppRunner(const std::string &title, int height, int width) :
        title(title), height(height), width(width) {
    glfwInit();
    createWindow();
}

AppRunner::~AppRunner() {
    glfwTerminate();
}

void AppRunner::createWindow() {
    // Window hints setup
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // Window creation
    pWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (pWindow == nullptr) {
        // throw if there is no window
        throw std::runtime_error("Failed to create OpenGL context");
    }

    // Context setting
    glfwMakeContextCurrent(pWindow);

    // Callback registration
    glfwSetWindowUserPointer(pWindow, this); // Set point to this object because it's the main input handler
    glfwSetKeyCallback(pWindow, processInput);
    glfwSetFramebufferSizeCallback(pWindow, framebuffer_size_callback);

    // GLAD
    gladLoadGL();
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "OpenGL SL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    auto begin = std::chrono::high_resolution_clock::now();
    scene = std::make_shared<CpuScene>(width, height);
//    scene = std::make_unique<ShaderScene>(width, height);
    auto end = std::chrono::high_resolution_clock::now();
    const auto s = std::static_pointer_cast<NoiseScene>(scene);
    handler.reset(new NoiseSceneEventHandler(s));
    std::cout << "Scene creation time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
              << "ms" << std::endl;
}

void AppRunner::run() {
//    double lastTime = glfwGetTime();
//    int nbFrames = 0;
    Timer timer("run timer");
    while (glfwWindowShouldClose(pWindow) == false) {
//        double currentTime = glfwGetTime();
//        nbFrames++;
//        if (currentTime - lastTime >= 1.0) {
//            std::cout << 1000.0 / double(nbFrames) << " ms/frame" << std::endl;
//            nbFrames = 0;
//            lastTime += 1.0;
//        }
        timer.begin();
        scene->render();
        timer.end();

        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }
}

void AppRunner::processInput(GLFWwindow *window, int key, int scancode, int action, int mods) {
    auto appRunner = static_cast<AppRunner *>(glfwGetWindowUserPointer(window)); // retrieve pointer to the handler

    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_ESCAPE: {
                glfwSetWindowShouldClose(window, true);
                break;
            }
            case GLFW_KEY_TAB: {
                appRunner->isWireframe = !appRunner->isWireframe;
                GLenum lineOrFill = appRunner->isWireframe ? GL_LINE : GL_FILL;
                glPolygonMode(GL_FRONT_AND_BACK, lineOrFill);
                break;
            }
            default:
                appRunner->handler->handleKey(key, scancode, action, mods);
        }
    }

}

void AppRunner::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
