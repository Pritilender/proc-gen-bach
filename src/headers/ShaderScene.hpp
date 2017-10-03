#ifndef GLAMOUR_SHADERSCENE_HPP
#define GLAMOUR_SHADERSCENE_HPP

#include "includes.hpp"
#include "../Scene.hpp"
#include "ShaderProgram.hpp"
#include "TextureArray.hpp"

class ShaderScene: public Scene {
public:
    ShaderScene(int w, int h);

    ~ShaderScene() {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &ebo);
    }

    void render() override;

protected:
    void redraw() override;

    void setupProgram() override;

    void setupTexture() override;

    std::unique_ptr<ShaderProgram> program;
    TextureArray textures;
    GLuint vao;
    GLuint ebo;
    std::vector<glm::uvec3> indices;

private:
    void prepareIndices();
};


#endif //GLAMOUR_SHADERSCENE_HPP
