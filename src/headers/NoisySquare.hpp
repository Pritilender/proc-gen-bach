#ifndef GLITTER_SQUARE_HPP
#define GLITTER_SQUARE_HPP

#include <vector>
#include <FastNoise.h>
#include <functional>
#include <VertexGenerators/VertexGenerator.hpp>
#include <memory>
#include "includes.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Drawable.hpp"

class NoisySquare : public Drawable {
public:
    NoisySquare(const std::shared_ptr<VertexGenerator>& vg, int resolution, float xMax);

    NoisySquare(const std::shared_ptr<VertexGenerator>& vg, const int resolution) :
        NoisySquare(vg, resolution, 1.0f) {}

    explicit NoisySquare(const std::shared_ptr<VertexGenerator>& vg) :
        NoisySquare(vg, 2, 1.0f) {}

    NoisySquare() = delete; // no default

    ~NoisySquare() override;

    void draw() override;

    void setVertexGenerator(const std::shared_ptr<VertexGenerator>& vg, float, float);

private:
    void prepareVerticesAndIndices(float, float);

    int resolution;
    float xMax;
    float step;
    std::shared_ptr<VertexGenerator> generator;

    std::vector<glm::vec3> vertices;
    std::vector<glm::uvec3> indices;
    std::vector<glm::vec3> normals;

    GLuint VBO;
    GLuint NBO;
    GLuint VAO;
    GLuint EBO;
};


#endif //GLITTER_SQUARE_HPP
