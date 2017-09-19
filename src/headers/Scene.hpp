#ifndef GLITTER_SCENE_HPP
#define GLITTER_SCENE_HPP

#include <vector>
#include <memory>
#include "includes.hpp"
#include "Drawable.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

class Scene {
public:
    Scene(int w, int h);
    void render();

    Camera camera;

private:
    void setupProgram();
    void setupTextures();

    int width;
    int height;

    float freq = 0.05f;
    float lacunarity = 2.0f;
    float persistence = 0.3f; // gain
    int octaves = 5;

    std::vector<std::unique_ptr<Drawable>> drawables;
    std::vector<std::unique_ptr<Texture>> textures;

    std::unique_ptr<ShaderProgram> program;
    float xMax = 100.0f;
};


#endif //GLITTER_SCENE_HPP
