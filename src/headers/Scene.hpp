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
    void restart();

    Camera camera;

private:
    void setupProgram();
    void setupTextures();

    int width;
    int height;

    float freq = 1.0f;
    float lacunarity = 2.0f;
    float persistence = 0.5f; // gain

    std::vector<std::unique_ptr<Drawable>> drawables;
    std::vector<std::unique_ptr<Texture>> textures;

    std::unique_ptr<ShaderProgram> program;
    float cameraSpeed = 0.5f;
};


#endif //GLITTER_SCENE_HPP
