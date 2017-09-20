#include "NoisySquare.hpp"
#include "FragmentShader.hpp"
#include "VertexShader.hpp"
#include "Scene.hpp"
#include <glm/gtc/matrix_inverse.hpp>
#include <VertexGenerators/PerlinVertexGenerator.hpp>

using namespace std;
using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;
using glm::radians;

Scene::Scene(int w, int h) : camera(), width(w), height(h), program(new ShaderProgram()), rd(), gen(rd()) {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    setupProgram();
    setupTextures();
    // scene specific
    FastNoise n = createFastNoise();
    auto gen = make_shared<PerlinVertexGenerator>(PerlinVertexGenerator(n));
    landscape.reset(new NoisySquare(gen, 500, xMax));
//    drawables.push_back(unique_ptr<Drawable>(new NoisySquare(noise, 1000, xMax)));
}

void Scene::setupProgram() {
    VertexShader vertex("ads.vert");
    FragmentShader fragment("ads.frag");

    program->attachShader(vertex)
        ->attachShader(fragment);

    program->link();

    // setup projection matrix
    mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 2000.0f);
    program->use();
    program->setUniform("ProjectionMatrix", projection);
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

    mat4 model = mat4(1.0f);
    model = glm::translate(model, vec3(-xMax / 2, 0.0f, -xMax / 2));
    mat4 mv = view * model;
    mat3 normalMatrix = glm::inverseTranspose(mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
    program->setUniform("ModelMatrix", model);
    program->setUniform("NormalMatrix", normalMatrix);
    landscape->draw();
}

void Scene::setupLandscape() {
    auto gen = make_shared<PerlinVertexGenerator>(PerlinVertexGenerator(createFastNoise()));
    landscape->setVertexGenerator(gen);
    printInfo();
}

const FastNoise Scene::createFastNoise() {
    FastNoise noise(seed);
    noise.SetNoiseType(FastNoise::PerlinFractal);
    noise.SetFrequency(freq);
    noise.SetFractalLacunarity(lacunarity);
    noise.SetFractalGain(persistence);
    noise.SetFractalOctaves(octaves);
    return noise;
}

void Scene::setFreq(float x) {
    freq += x;
    setupLandscape();
}

void Scene::setLacunarity(float x) {
    lacunarity += x;
    setupLandscape();
}

void Scene::setPersistence(float x) {
    persistence += x;
    setupLandscape();
}

void Scene::setOctaves(int x) {
    octaves += x;
    octaves = octaves == 0 ? 1 : octaves;
    setupLandscape();
}

void Scene::setXMax(float x) {
    xMax += x;
    setupLandscape();
}

void Scene::generateSeed() {
    std::uniform_int_distribution<> dis;
    seed = dis(gen);
    setupLandscape();
}

void Scene::printInfo() {
    cout << "==========" << endl;
    cout << "Seed: " << seed << endl;
    cout << "Noise frequency: " << freq << endl;
    cout << "Noise lacunarity: " << lacunarity << endl;
    cout << "Noise persistence: " << persistence << endl;
    cout << "Number of octaves: " << octaves << endl;
    cout << "==========" << endl;
}
