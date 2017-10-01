#ifndef GLAMOUR_PERLINVERTEXGENERATOR_HPP
#define GLAMOUR_PERLINVERTEXGENERATOR_HPP

#include "includes.hpp"
#include "VertexGenerator.hpp"

class PerlinVertexGenerator: public VertexGenerator {
public:
    explicit PerlinVertexGenerator(const FastNoise& noise): VertexGenerator(noise) {};
    glm::vec3 generateVertex(const float x, const float z) override {
        float y = noise.GetNoise(x, z);
        if (y > 0) {
            y *= 20.0f;
        } else {
            y *= 5.0f;
        }
//        float peakFactor = 1.8f;
//        float terracingFactor = 10;
//        y = powf(y, 1.2f) * 10;
        // water cut-off
//        if (y < 0) {
//            y = -0.001f;
//        } else {
            // this can be tweaked so we can force a certain type of a terrain
//            y = powf(y, peakFactor);
//            y = roundf(y * terracingFactor) / terracingFactor;
//        }
        return glm::vec3(x, y, z);
    }
};


#endif //GLAMOUR_PERLINVERTEXGENERATOR_HPP
