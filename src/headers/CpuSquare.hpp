#ifndef GLITTER_SQUARE_HPP
#define GLITTER_SQUARE_HPP

#include <vector>
#include <FastNoise.h>
#include <functional>
#include <memory>
#include <random>
#include "includes.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "NoiseSquare.hpp"

class CpuSquare : public NoiseSquare {
public:
    CpuSquare(int xMax, float res);
    CpuSquare() = delete;
    ~CpuSquare() override;

    void draw() override;
    void uploadNewData() override;

    void setFreq(float f) override {
        NoiseSquare::setFreq(f);
        noise.SetFrequency(freq);
    }

    void setLacunarity(float l) override {
        NoiseSquare::setLacunarity(l);
        noise.SetFractalLacunarity(lacunarity);
    }

    void setPersistence(float p) override {
        NoiseSquare::setPersistence(p);
        noise.SetFractalGain(persistence);
    }

    void setOctaves(int o) override {
        NoiseSquare::setOctaves(o);
        noise.SetFractalOctaves(octaves);
    }

    void generateSeed() override {
        NoiseSquare::generateSeed();
        noise.SetSeed(seed);
    }

private:
    void prepareVerticesAndIndices(float, float);

    float step;

    std::vector<glm::vec3> vertices;
    std::vector<glm::uvec3> indices;
    std::vector<glm::vec3> normals;

    FastNoise noise;

    GLuint VBO;
    GLuint NBO;
    GLuint VAO;
    GLuint EBO;
};


#endif //GLITTER_SQUARE_HPP
