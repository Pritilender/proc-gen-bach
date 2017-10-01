#ifndef GLITTER_SCENE_HPP
#define GLITTER_SCENE_HPP

#include <vector>
#include <memory>
#include <random>
#include "includes.hpp"
#include "Drawable.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "TextureArray.hpp"

class Scene {
public:
    Scene(int w, int h);

    void render();

    void setFreq(float freq);
    void setLacunarity(float lacunarity);
    void setPersistence(float persistence);
    void setOctaves(int octaves);
    void setXMax(float xMax);
    void generateSeed();

    Camera camera;

protected:
    void setupProgram();
    void setupTextures();

private:
    void setupLandscape();
    const FastNoise createFastNoise();
    void printInfo();
    int width;
    int height;

    float freq = 0.04f;
    float lacunarity = 1.7f;
    float persistence = 0.5f; // gain
    int octaves = 5;
    int seed = 1337;

    std::random_device rd;
    std::mt19937 gen;

//    std::vector<std::unique_ptr<Drawable>> drawables;
//    std::vector<std::unique_ptr<Texture>> textures;

    std::unique_ptr<NoisySquare> landscape;
    std::unique_ptr<ShaderProgram> program;
    TextureArray textures;
    float xMax = 100.0f;
    float resolution = 500;
};


#endif //GLITTER_SCENE_HPP
