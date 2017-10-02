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
#include "../Scene.hpp"

class NoisyScene: public Scene {
public:
    NoisyScene(int w, int h);

    void render() override;

protected:
    void setupProgram() override;
    void setupTexture() override;

private:
    void redraw();
    const FastNoise createFastNoise();

    std::unique_ptr<NoisySquare> landscape;
    std::unique_ptr<ShaderProgram> program;
    TextureArray textures;
    float xMax = 100.0f;
    float resolution = 500;
};


#endif //GLITTER_SCENE_HPP
