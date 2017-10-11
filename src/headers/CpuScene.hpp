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
#include "Scene.hpp"
#include "NoiseScene.hpp"

class CpuScene: public NoiseScene {
public:
    CpuScene(int w, int h);

    void render() override;

    void redraw() override;
};


#endif //GLITTER_SCENE_HPP
