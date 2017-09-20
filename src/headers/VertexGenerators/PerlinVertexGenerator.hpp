#ifndef GLAMOUR_PERLINVERTEXGENERATOR_HPP
#define GLAMOUR_PERLINVERTEXGENERATOR_HPP

#include "includes.hpp"
#include "VertexGenerator.hpp"

class PerlinVertexGenerator: public VertexGenerator {
public:
    explicit PerlinVertexGenerator(const FastNoise& noise): VertexGenerator(noise) {};
    glm::vec3 generateVertex(const float x, const float z) override {
        float y = noise.GetNoise(x, z);
//        y = powf(y, 1.2f) * 10;
        // water cut-off
        if (y < 0) {
            y = 0;
        } else {
            // this can be tweaked so we can force a certain type of a terrain
            y *= 10.0f;
            y = powf(y, 1.8f);
        }
        return glm::vec3(x, y, z);
    }
};


#endif //GLAMOUR_PERLINVERTEXGENERATOR_HPP
