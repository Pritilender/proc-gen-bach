#ifndef GLITTERING_GLAMOUR_NOISESQUARE_HPP
#define GLITTERING_GLAMOUR_NOISESQUARE_HPP

#include <random>
#include "Drawable.hpp"
#include "Shader.hpp"

class NoiseSquare : public Drawable {

public:
    NoiseSquare(const std::vector<std::shared_ptr<Shader>> &shaders,
                const std::vector<std::string> &textureFiles,
                int resolution,
                float xMax) : Drawable(shaders, textureFiles),
                              resolution(resolution),
                              xMax(xMax),
                              gen(rd()) {
        std::cout << "In Noise Square " << resolution << " " << xMax << std::endl;
        program.use();
        program.setUniform("xMax", xMax);
        program.setUniform("resolution", resolution);
    }

    void printInfo() {
        std::cout << "==========" << std::endl;
        std::cout << "Seed: " << seed << std::endl;
        std::cout << "Noise frequency: " << freq << std::endl;
        std::cout << "Noise lacunarity: " << lacunarity << std::endl;
        std::cout << "Noise persistence: " << persistence << std::endl;
        std::cout << "Number of octaves: " << octaves << std::endl;
        std::cout << "==========" << std::endl;
    }

    int resolution;
    float xMax;
    std::random_device rd;
    std::mt19937 gen;
    float xOffset = 0.0;
    float zOffset = 0.0;

    virtual void setFreq(float freq) {
        NoiseSquare::freq += freq;
    }

    virtual void setLacunarity(float lacunarity) {
        NoiseSquare::lacunarity += lacunarity;
    }

    virtual void setPersistence(float persistence) {
        NoiseSquare::persistence += persistence;
    }

    virtual void setOctaves(int octaves) {
        NoiseSquare::octaves += octaves;
    }

    virtual void generateSeed() {
        std::uniform_int_distribution<> dis(0, 10000);
        NoiseSquare::seed = dis(gen);
    }

    virtual void uploadNewData() = 0;

protected:
    float freq = 0.01f;
    float lacunarity = 1.7f;
    float persistence = 0.5f; // gain
    int octaves = 5;
    int seed = 1337;
};

#endif //GLITTERING_GLAMOUR_NOISESQUARE_HPP
