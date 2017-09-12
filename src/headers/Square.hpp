#ifndef GLITTER_SQUARE_HPP
#define GLITTER_SQUARE_HPP

#include <vector>
#include "includes.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Drawable.hpp"

class Square: public Drawable {
public:
    Square(int resolution, float xMax);
    explicit Square(int resolution): Square(resolution, 1.0f) {}
    Square(): Square(2, 1.0f) {}
    ~Square();
    void draw() override;

private:
    void prepareVerticesAndIndices();

    int resolution;
    float xMax;
    float step;

    std::vector<glm::vec3> vertices;
    std::vector<glm::uvec3> indices;
    std::vector<glm::vec3> normals;
    GLuint VBO;
    GLuint NBO;
    GLuint VAO;
    GLuint EBO;
};


#endif //GLITTER_SQUARE_HPP
