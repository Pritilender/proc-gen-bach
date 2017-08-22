#include "glitter.hpp"
#include "ShaderProgram.hpp"

#ifndef GLITTER_TRIANGLE_HPP
#define GLITTER_TRIANGLE_HPP

class Triangle {
public:
    Triangle();
    ~Triangle();
    void render();

private:
    float vertices[9] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f, // right
        0.0f, 0.5f, 0.0f  // top
    };
    GLuint VBO;
    GLuint VAO;
    ShaderProgram *shaderProgram;
};


#endif //GLITTER_TRIANGLE_HPP
