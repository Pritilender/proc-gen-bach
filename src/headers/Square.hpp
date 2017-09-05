#ifndef GLITTER_SQUARE_HPP
#define GLITTER_SQUARE_HPP

#include "includes.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Drawable.hpp"

class Square: public Drawable {
public:
    Square();
    ~Square();
    void draw() override;

private:
    float vertices[32] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };
    unsigned int indices[6] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    GLuint VBO;
    GLuint VAO;
    GLuint EBO;
};


#endif //GLITTER_SQUARE_HPP
