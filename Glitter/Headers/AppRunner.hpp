#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "ShaderProgram.hpp"

#ifndef GLITTER_APPRUNNER_HPP
#define GLITTER_APPRUNNER_HPP

/**
 * Application and window wrapper for GLFW
 */
class AppRunner {
public:
    /**
     * Create app runner providing just the window title with default window dimensions of 1280x800.
     * @param title - Window title
     */
    explicit AppRunner(const std::string &title): AppRunner(title, 800, 1280) {};
    /**
    * Create app runner with a given window title and window dimensions.
    * @param title - Window title
    * @param height - Window height
    * @param width - Window width
    */
    AppRunner(const std::string &title, int height, int width);
    ~AppRunner();

    // Delete defaults
    AppRunner() = delete;
    AppRunner(const AppRunner&) = delete;
    AppRunner& operator=(const AppRunner&) = delete;
    AppRunner(AppRunner&&) = delete;
    AppRunner& operator=(AppRunner&&) = delete;

    /**
     * Creates a new window with a title
     * @param tite - Window title
     * @throws runtime_error - If no window is created
     */
    void createWindow();
    /**
     * Main application method used for OpenGL scene setup and scene drawing
     */
    void run();
    /**
     * GLFW input processing callback
     * @param window
     * @param key
     * @param scancode
     * @param action
     * @param mods
     */
    static void processInput(GLFWwindow *window, int key, int scancode, int action, int mods);
    /**
     * GLFW framebuffer callback
     * @param window
     * @param width
     * @param height
     */
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

private:
    /**
     * Scene setup
     */
    void setup();
    /**
    * Scene drawing logic
    */
    void draw();

    std::string title; //!< Window title
    int height; //!< Window height
    int width; //!< Window width
    GLFWwindow *pWindow; //!< Pointer to GLFW window

    bool isWireframe = false; //!< Is current drawn object shown as wireframe

    ShaderProgram *shaderProgram;
};


#endif //GLITTER_APPRUNNER_HPP
