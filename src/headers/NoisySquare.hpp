#ifndef GLITTER_SQUARE_HPP
#define GLITTER_SQUARE_HPP

#include <vector>
#include <FastNoise.h>
#include <functional>
#include "includes.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Drawable.hpp"

class NoisySquare : public Drawable {
public:
    NoisySquare(const FastNoise &noiseGenerator, int resolution, float xMax);

    NoisySquare(const FastNoise &noiseGenerator, int resolution) :
        NoisySquare(noiseGenerator, resolution, 1.0f) {}

    explicit NoisySquare(const FastNoise &noiseGenerator) :
        NoisySquare(noiseGenerator, 2, 1.0f) {}

    NoisySquare() = delete; // no default

    ~NoisySquare() override;

    void draw() override;

    void setNoiseGenerator(const FastNoise &noiseGenerator);

private:
    void prepareVerticesAndIndices();

    int resolution;
    float xMax;
    float step;

    FastNoise noiseGenerator;
    std::vector<glm::vec3> vertices;
    std::vector<glm::uvec3> indices;
    std::vector<glm::vec3> normals;
    GLuint VBO;
    GLuint NBO;
    GLuint VAO;
    GLuint EBO;
};


#endif //GLITTER_SQUARE_HPP
