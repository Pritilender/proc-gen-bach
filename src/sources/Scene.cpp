#include "Square.hpp"
#include "FragmentShader.hpp"
#include "VertexShader.hpp"
#include "Scene.hpp"

using namespace std;

Scene::Scene(int w, int h) : width(w), height(h) {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.5f, 0.9f, 1.0f);

    setupProgram();
    setupTextures();

    drawables.push_back(unique_ptr<Drawable>(new Square));

    // setup projection matrix
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
//    textures.push_back(unique_ptr<Texture>(new Texture("awesomeface.png")));
//    textures.push_back(unique_ptr<Texture>(new Texture("container.jpg")));
//
//    program->use();
//    program->setUniform("texture1", 0)
//        ->setUniform("texture2", 1);
}

void Scene::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearBufferfi(GL_DEPTH_STENCIL, 0, 1.0f, 0);

    for (auto &d : drawables) {
        glm::mat4 mvMatrix, translate, rotateX, rotateY, rotateZ;
        translate = glm::translate(translate, cameraPos);
        rotateX = glm::rotate(rotateX, glm::radians(angX), glm::vec3(1, 0, 0));
        rotateY = glm::rotate(rotateY, glm::radians(angY), glm::vec3(0, 1, 0));
        rotateZ = glm::rotate(rotateZ, glm::radians(angZ), glm::vec3(0, 0, 1));
        mvMatrix = rotateX * rotateZ * rotateY * translate;

        program->setUniform("modelView", mvMatrix);

        d->draw();
    }
}

void Scene::moveCameraX(bool isPositive) {
    int modifier = isPositive ? 1 : -1;
    cameraPos.x += modifier * cameraSpeed;
}

void Scene::moveCameraY(bool isPositive) {
    int modifier = isPositive ? 1 : -1;
    cameraPos.y += modifier * cameraSpeed;
}

void Scene::moveCameraZ(bool isPositive) {
    int modifier = isPositive ? 1 : -1;
    cameraPos.z += modifier * cameraSpeed;
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

void Scene::restart() {
    angY = 0;
    angX = 0;
    angZ = 0;
    cameraPos = glm::vec3(0.0f, 0.0f, -3.0f);
}
