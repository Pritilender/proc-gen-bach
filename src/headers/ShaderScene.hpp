#ifndef GLAMOUR_SHADERSCENE_HPP
#define GLAMOUR_SHADERSCENE_HPP

#include "includes.hpp"
#include "ShaderProgram.hpp"
#include "TextureArray.hpp"
#include "NoiseScene.hpp"

class ShaderScene: public NoiseScene {
public:
    ShaderScene(int w, int h);

    void render() {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearBufferfi(GL_DEPTH_STENCIL, 0, 1.0f, 0);

        auto& program = landscape->program;
        program.use();

        glm::mat4 projection;
        glm::mat4 view = camera.getViewMatrix();

        projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 500.0f);
        program.setUniform("ProjectionMatrix", projection);
        program.setUniform("ViewMatrix", view);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-XMAX / 2, 0.0f, -XMAX / 2));
        glm::mat4 mv = view * model;
        glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2])));
        program.setUniform("ModelMatrix", model);
        program.setUniform("NormalMatrix", normalMatrix);
        landscape->draw();
    }

    void redraw() override;
};


#endif //GLAMOUR_SHADERSCENE_HPP
