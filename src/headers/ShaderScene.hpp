#ifndef GLAMOUR_SHADERSCENE_HPP
#define GLAMOUR_SHADERSCENE_HPP

#include "includes.hpp"
#include "ShaderProgram.hpp"
#include "TextureArray.hpp"
#include "NoiseScene.hpp"

class ShaderScene: public NoiseScene {
public:
    ShaderScene(int w, int h);

    void render() override;

    void redraw() override;
};


#endif //GLAMOUR_SHADERSCENE_HPP
