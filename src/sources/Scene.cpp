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

Scene::Scene(int w, int h) : width(w), height(h), camera() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    setupProgram();
    setupTextures();
    float xMax = 10.0f;
    FastNoise noise;
    noise.SetNoiseType(FastNoise::PerlinFractal);
    noise.SetFrequency(freq);
    noise.SetFractalLacunarity(lacunarity);
    noise.SetFractalGain(persistence);
    drawables.push_back(unique_ptr<Drawable>(new NoisySquare(noise, 200, xMax)));
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

    mat4 view = camera.getViewMatrix();
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
        model = glm::translate(model, vec3(-5.0f, 0.0f, -5.0f));
        mat4 mv = view * model;
        mat3 normalMatrix = glm::inverseTranspose(mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
        program->setUniform("ModelMatrix", model);
        program->setUniform("NormalMatrix", normalMatrix);
        d->draw();
    }
}
