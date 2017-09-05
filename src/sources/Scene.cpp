#include "Square.hpp"
#include "Triangle.hpp"
#include "FragmentShader.hpp"
#include "VertexShader.hpp"
#include "Scene.hpp"
#include <Cube.hpp>

using namespace std;

Scene::Scene(int w, int h) : width(w), height(h) {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.5f, 0.9f, 1.0f);

    setupProgram();
    setupTextures();

    for(int i = 0; i < 24; i++) {
        drawables.push_back(unique_ptr<Drawable>(new Cube));
    }
//    drawables.push_back(unique_ptr<Drawable>(new Square));
//    drawables.push_back(unique_ptr<Drawable>(new Triangle));
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 100.0f);
    program->use();
    program->setUniform("projection", projection);
}

void Scene::setupProgram() {
    VertexShader vertex("vertexShaderSquare.vert");
    FragmentShader fragment("fragmentShaderSquare.frag");

    program.reset(new ShaderProgram());
    program->attachShader(vertex)
        ->attachShader(fragment);

    program->link();
}

void Scene::setupTextures() {
    textures.push_back(unique_ptr<Texture>(new Texture("awesomeface.png")));
    textures.push_back(unique_ptr<Texture>(new Texture("container.jpg")));

    program->use();
    program->setUniform("texture1", 0)
        ->setUniform("texture2", 1);
}

void Scene::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearBufferfi(GL_DEPTH_STENCIL, 0, 1.0f, 0);
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 100.0f);
    program->use();
    program->setUniform("projection", projection);

    for (auto &d : drawables) {
        auto currentTime = (float) glfwGetTime() * 0.01f;
        float f = currentTime * (float) M_PI * 0.1f;
        // model view matrix for spinning cube
        glm::mat4 mvMatrix, translation1, translation2, rotation1, rotation2;
        translation1 = glm::translate(glm::mat4(), glm::vec3(0.0f + 10 * currentTime, 0.0f, -20.0f + currentTime));
        translation2 = glm::translate(glm::mat4(),
                                      glm::vec3(sinf(2.1f * f) * 2.0f,
                                                cosf(1.7f * f) * 2.0f,
                                                sinf(1.3f * f) * cosf(1.5f * f) * 2.0f));
        rotation1 = glm::rotate(glm::mat4(), currentTime * 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        rotation2 = glm::rotate(glm::mat4(), currentTime * 21.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        mvMatrix = translation1 * rotation1 * rotation2 * translation2;

        program->setUniform("modelView", mvMatrix);

//    for (int i = 0; i < textures.size(); ++i) {
//        textures[i]->bindToActive(static_cast<GLenum>(GL_TEXTURE0 + i));
//    }

        d->draw();
    }
}

void Scene::moveCameraX(bool isPositive) {
    int modifier = isPositive ? 1 : -1;
    cameraPos += modifier * cameraSpeed * cameraFront;
}

void Scene::moveCameraY(bool isPositive) {
    int modifier = isPositive ? 1 : -1;
    cameraPos += modifier * cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
}

void Scene::rotateY(bool isPositive) {
    int modifier = isPositive ? 5 : -5;
    angY += modifier * 1;
}

void Scene::rotateX(bool isPositive) {
    int modifier = isPositive ? 5 : -5;
    angX += modifier * 1;
}

void Scene::rotateZ(bool isPositive) {
    int modifier = isPositive ? 5 : -5;
    angZ += modifier * 1;
}
