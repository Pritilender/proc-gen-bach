#include "AppRunner.hpp"
#include "glitter.hpp"
#include <iostream>

AppRunner::AppRunner(const std::string &title, int height, int width) : title(title), height(height), width(width) {
    glfwInit();
    createWindow();
}

AppRunner::~AppRunner() {
    if (shaderProgram != nullptr) {
        delete shaderProgram;
    }

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
    setup();
    while (glfwWindowShouldClose(pWindow) == false) {
        draw();

        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }
}

void AppRunner::setup() {
    glClearColor(0.1f, 0.5f, 0.9f, 1.0f);
    shaderProgram = new ShaderProgram();
    shaderProgram->attachShader("vertexShader.vert");
    shaderProgram->attachShader("fragmentShader.frag");
    shaderProgram->link();
}

void AppRunner::draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f, // right
        0.0f, 0.5f, 0.0f  // top
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    shaderProgram->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
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
