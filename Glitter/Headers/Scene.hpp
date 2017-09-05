#ifndef GLITTER_SCENE_HPP
#define GLITTER_SCENE_HPP

#include <vector>
#include <memory>
#include "Drawable.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

class Scene {
public:
    Scene(int w, int h);
    void render();
    void moveCameraX(bool isPositive);
    void moveCameraY(bool isPositive);
    void rotateY(bool isPositive);
    void rotateX(bool isPositive);
    void rotateZ(bool isPositive);

private:
    void setupProgram();
    void setupTextures();

    int width;
    int height;

    float angY = 0;
    float angX = 0;
    float angZ = 0;

    std::vector<std::unique_ptr<Drawable>> drawables;
    std::vector<std::unique_ptr<Texture>> textures;
    std::unique_ptr<ShaderProgram> program;

    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    float cameraSpeed = 0.5f;
};


#endif //GLITTER_SCENE_HPP
