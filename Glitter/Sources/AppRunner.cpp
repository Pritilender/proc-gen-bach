#include "AppRunner.hpp"
#include "glitter.hpp"
#include <iostream>
#include <Scene.hpp>

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
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

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

    s.reset(new Scene(width, height));
}

void AppRunner::run() {
    double lastTime = glfwGetTime();
    int nbFrames = 0;

    while (glfwWindowShouldClose(pWindow) == false) {
        double currentTime = glfwGetTime();
        nbFrames++;
        if ( currentTime - lastTime >= 1.0 ){
            std::cout << 1000.0/double(nbFrames) << " ms/frame" << std::endl;
            nbFrames = 0;
            lastTime += 1.0;
        }
        s->render();

        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }
}

void AppRunner::processInput(GLFWwindow *window, int key, int scancode, int action, int mods) {
    auto appRunner = static_cast<AppRunner *>(glfwGetWindowUserPointer(window)); // retrieve pointer to the handler

    if (action == GLFW_PRESS) {
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
            case GLFW_KEY_W: {
                appRunner->s->moveCameraX(true);
                break;
            }
            case GLFW_KEY_S: {
                appRunner->s->moveCameraX(false);
                break;
            }
            case GLFW_KEY_A: {
                appRunner->s->moveCameraY(false);
                break;
            }
            case GLFW_KEY_D: {
                appRunner->s->moveCameraY(true);
                break;
            }
            case GLFW_KEY_Q: {
                appRunner->s->rotateY(true);
                break;
            }
            case GLFW_KEY_E: {
                appRunner->s->rotateY(false);
                break;
            }
            case GLFW_KEY_LEFT: {
                appRunner->s->rotateX(true);
                break;
            }
            case GLFW_KEY_RIGHT: {
                appRunner->s->rotateX(false);
                break;
            }
            case GLFW_KEY_UP: {
                appRunner->s->rotateZ(true);
                break;
            }
            case GLFW_KEY_DOWN: {
                appRunner->s->rotateZ(false);
                break;
            }
        }
    }
}

void AppRunner::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
