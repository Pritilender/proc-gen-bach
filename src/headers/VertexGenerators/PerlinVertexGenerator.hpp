#ifndef GLAMOUR_PERLINVERTEXGENERATOR_HPP
#define GLAMOUR_PERLINVERTEXGENERATOR_HPP


#include "VertexGenerator.hpp"

class PerlinVertexGenerator: public VertexGenerator {
public:
    explicit PerlinVertexGenerator(const FastNoise& noise): VertexGenerator(noise) {};
    glm::vec3 generateVertex(const float x, const float z) override {
        float y = noise.GetNoise(x, z) + 0.1f;
        y = y < 0 ? -0.1f : 10.0f * y;
        return glm::vec3(x, y, z);
    }
};


#endif //GLAMOUR_PERLINVERTEXGENERATOR_HPP
