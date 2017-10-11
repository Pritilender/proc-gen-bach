#ifndef GLITTER_DRAWABLE_HPP
#define GLITTER_DRAWABLE_HPP

#include "includes.hpp"
#include "TextureArray.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"

/**
 * Abstract class for all drawable elements of the scene.
 */
class Drawable {
public:
    Drawable(const std::vector<std::shared_ptr<Shader>> &shaders, const std::vector<std::string> &textureFiles) :
        textures(textureFiles) {
        setupProgram(shaders);

        program.use();
        textures.prepare();
        program.setUniform("textures", 0);
    }

    Drawable() = delete;

    /**
     * Figure should release all buffers that it holds in its destructor.
     */
    virtual ~Drawable() {};

    /**
     * Bind all buffers and draw elements.
     */
    virtual void draw() = 0;

    virtual void setupProgram(const std::vector<std::shared_ptr<Shader>>& shaders) {
        for (auto s: shaders) {
            program.attachShader(*s);
        }
        program.link();
    }

    ShaderProgram program;
protected:
    TextureArray textures;
};


#endif //GLITTER_DRAWABLE_HPP
