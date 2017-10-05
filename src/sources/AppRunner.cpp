#include <ShaderScene.hpp>
#include <Timer.hpp>
#include <chrono>
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

    auto begin = std::chrono::high_resolution_clock::now();
    scene = std::make_unique<NoisyScene>(width, height);
//    scene = std::make_unique<ShaderScene>(width, height);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Scene creation time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << std::endl;
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
            case GLFW_KEY_R: {
                --appRunner->scene->camera.positionY;
                break;
            }
            case GLFW_KEY_F: {
                ++appRunner->scene->camera.positionY;
                break;
            }
            case GLFW_KEY_W: {
                ++appRunner->scene->camera.positionZ;
                break;
            }
            case GLFW_KEY_S: {
                --appRunner->scene->camera.positionZ;
                break;
            }
            case GLFW_KEY_A: {
                ++appRunner->scene->camera.positionX;
                break;
            }
            case GLFW_KEY_D: {
                --appRunner->scene->camera.positionX;
                break;
            }
            case GLFW_KEY_Q: {
                ++appRunner->scene->camera.angleZ;
                break;
            }
            case GLFW_KEY_E: {
                --appRunner->scene->camera.angleZ;
                break;
            }
            case GLFW_KEY_UP: {
                ++appRunner->scene->camera.angleX;
                break;
            }
            case GLFW_KEY_DOWN: {
                --appRunner->scene->camera.angleX;
                break;
            }
            case GLFW_KEY_LEFT: {
                ++appRunner->scene->camera.angleY;
                break;
            }
            case GLFW_KEY_RIGHT: {
                --appRunner->scene->camera.angleY;
                break;
            }
            case GLFW_KEY_T: {
                appRunner->scene->setFreq(0.002f);
                break;
            }
            case GLFW_KEY_G: {
                appRunner->scene->setFreq(-0.002f);
                break;
            }
            case GLFW_KEY_Y: {
                appRunner->scene->setLacunarity(0.05f);
                break;
            }
            case GLFW_KEY_H: {
                appRunner->scene->setLacunarity(-0.05f);
                break;
            }
            case GLFW_KEY_U: {
                appRunner->scene->setPersistence(0.02f);
                break;
            }
            case GLFW_KEY_J: {
                appRunner->scene->setPersistence(-0.02f);
                break;
            }
            case GLFW_KEY_I: {
                appRunner->scene->setOctaves(1);
                break;
            }
            case GLFW_KEY_K: {
                appRunner->scene->setOctaves(-1);
                break;
            }
            case GLFW_KEY_SPACE: {
                appRunner->scene->generateSeed();
            }
        }
    }
}

void AppRunner::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
