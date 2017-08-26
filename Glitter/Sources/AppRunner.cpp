#include "AppRunner.hpp"
#include "glitter.hpp"
#include <iostream>
#include <Scene.hpp>

AppRunner::AppRunner(const std::string &title, int height, int width) : title(title), height(height), width(width) {
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
}

void AppRunner::run() {
    Scene s;
    while (glfwWindowShouldClose(pWindow) == false) {
        s.render();

        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }
}

void AppRunner::processInput(GLFWwindow *window, int key, int scancode, int action, int mods) {
    auto appRunner = static_cast<AppRunner *>(glfwGetWindowUserPointer(window)); // retrieve pointer to the handler

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
        appRunner->isWireframe = !appRunner->isWireframe;
        GLenum lineOrFill = appRunner->isWireframe ? GL_LINE : GL_FILL;
        glPolygonMode(GL_FRONT_AND_BACK, lineOrFill);
    }
}

void AppRunner::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
