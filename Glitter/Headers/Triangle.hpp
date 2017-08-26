#ifndef GLITTER_TRIANGLE_HPP
#define GLITTER_TRIANGLE_HPP

#include "glitter.hpp"
#include "ShaderProgram.hpp"
#include "Drawable.hpp"

class Triangle : public Drawable {
public:
    Triangle();
    ~Triangle();
    void draw() override;

private:
    float vertices[9] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f, // right
        0.0f, 0.5f, 0.0f  // top
    };
    GLuint VBO;
    GLuint VAO;
};


#endif //GLITTER_TRIANGLE_HPP
