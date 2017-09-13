#include "NoisySquare.hpp"
#include "FragmentShader.hpp"
#include "VertexShader.hpp"
#include "Scene.hpp"
#include <glm/gtc/matrix_inverse.hpp>

using namespace std;
using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;
using glm::radians;

Scene::Scene(int w, int h) : width(w), height(h) {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    setupProgram();
    setupTextures();
    float xMax = 1000.0f;
    FastNoise noise(21431232);
    noise.SetNoiseType(FastNoise::Perlin);
    noise.SetFrequency(0.1);
    drawables.push_back(unique_ptr<Drawable>(new NoisySquare(noise, 2000, xMax)));
}

void Scene::setupProgram() {
    VertexShader vertex("ads.vert");
    FragmentShader fragment("ads.frag");

    program.reset(new ShaderProgram());
    program->attachShader(vertex)
        ->attachShader(fragment);

    program->link();

    // setup projection matrix
    mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 2000.0f);
    program->use();
    program->setUniform("ProjectionMatrix", projection);
//    program->setUniform("normalizer", xMax);
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
    program->use();

    mat4 view(1.0f);
    view = glm::translate(view, cameraPos);
    view = glm::rotate(view, radians(angX), vec3(1, 0, 0));
    view = glm::rotate(view, radians(angY), vec3(0, 1, 0));
    view = glm::rotate(view, radians(angZ), vec3(0, 0, 1));
    program->setUniform("ViewMatrix", view);
    program->setUniform("Light.Ld", vec3(1.0f, 1.0f, 1.0f));
    program->setUniform("Light.Position", view * vec4(100.0f, 100.0f, 100.0f, 1.0f));
    program->setUniform("Light.La", vec3(0.2f, 0.2f, 0.2f));
    program->setUniform("Light.Ls", vec3(0.2f, 0.2f, 0.2f));
    program->setUniform("Shininess", 100.0f);

    for (auto &d : drawables) {
        mat4 model = mat4(1.0f);
//        model = glm::translate(model, vec3(-1, 0, -1));
//        model = glm::scale(model, vec3(0.2, 0.2, 0.2));
        model = glm::translate(model, vec3(-25.0f, 0.0f, -25.0f));
        mat4 mv = view * model;
        mat3 normalMatrix = glm::inverseTranspose(mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
        program->setUniform("ModelMatrix", model);
        program->setUniform("NormalMatrix", normalMatrix);
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
    cameraPos = glm::vec3(0.0f, -0.5f, -2.0f);
}
