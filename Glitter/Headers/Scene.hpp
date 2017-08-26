#ifndef GLITTER_SCENE_HPP
#define GLITTER_SCENE_HPP

#include <vector>
#include <memory>
#include "Drawable.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

class Scene {
public:
    Scene();
    void render();

private:
    void setupProgram();
    void setupTextures();

    std::vector<std::unique_ptr<Drawable>> drawables;
    std::vector<std::unique_ptr<Texture>> textures;
    std::unique_ptr<ShaderProgram> program;
};


#endif //GLITTER_SCENE_HPP
