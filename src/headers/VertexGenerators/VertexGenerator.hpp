#ifndef GLAMOUR_VERTEXGENERATOR_HPP
#define GLAMOUR_VERTEXGENERATOR_HPP


#include <glm/vec3.hpp>
#include "FastNoise.h"

class VertexGenerator {
public:
    explicit VertexGenerator(const FastNoise& noise): noise(noise) {};
    virtual ~VertexGenerator() = default;
    virtual glm::vec3 generateVertex(float x, float z) = 0;

protected:
    const FastNoise noise;
};


#endif //GLAMOUR_VERTEXGENERATOR_HPP
