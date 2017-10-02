#include "NoisySquare.hpp"
#include "FragmentShader.hpp"
#include "VertexShader.hpp"
#include "NoisyScene.hpp"
#include <glm/gtc/matrix_inverse.hpp>
#include <VertexGenerators/PerlinVertexGenerator.hpp>

using namespace std;
using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;
using glm::radians;

NoisyScene::NoisyScene(int w, int h) : Scene(w, h),
                             program(new ShaderProgram()),
                             textures({"deep-water.jpg",
                                       "coastal-water.jpg",
                                       "beach.jpg",
                                       "lowlands.jpg",
                                       "hills.jpg",
                                       "mountains.jpg",
                                       "mid-snow.jpg",
                                       "snow.jpg"}) {
    setupProgram();
    setupTexture();
    // scene specific
    FastNoise n = createFastNoise();
    auto gen = make_shared<PerlinVertexGenerator>(PerlinVertexGenerator(n));
    landscape.reset(new NoisySquare(gen, resolution, xMax));
}

void NoisyScene::setupProgram() {
    VertexShader vertex("adsPerPixel.vert");
    FragmentShader fragment("adsPerPixel.frag");

    program->attachShader(vertex)
        ->attachShader(fragment);

    program->link();

    // setup projection matrix
    mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 2000.0f);
    program->use();
    program->setUniform("ProjectionMatrix", projection);
}

void NoisyScene::setupTexture() {
    program->use();
    textures.prepare();
    program->setUniform("textures", 0);
    // setup for texture coordinates generation
    program->setUniform("xMax", xMax);
    program->setUniform("resolution", resolution);
}

void NoisyScene::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearBufferfi(GL_DEPTH_STENCIL, 0, 1.0f, 0);
    program->use();
    textures.bindToActive(GL_TEXTURE0);

    mat4 view = camera.getViewMatrix();
    program->setUniform("ViewMatrix", view);

    mat4 model = mat4(1.0f);
    model = glm::translate(model, vec3(-xMax / 2, 0.0f, -xMax / 2));
    mat4 mv = view * model;
    mat3 normalMatrix = glm::inverseTranspose(mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
    program->setUniform("ModelMatrix", model);
    program->setUniform("NormalMatrix", normalMatrix);
    landscape->draw();
}

void NoisyScene::redraw() {
    auto gen = make_shared<PerlinVertexGenerator>(PerlinVertexGenerator(createFastNoise()));
    landscape->setVertexGenerator(gen);
    printInfo();
}

const FastNoise NoisyScene::createFastNoise() {
    FastNoise noise(seed);
    noise.SetNoiseType(FastNoise::PerlinFractal);
//    noise.SetNoiseType(FastNoise::SimplexFractal);
    noise.SetFrequency(freq);
    noise.SetFractalLacunarity(lacunarity);
    noise.SetFractalGain(persistence);
    noise.SetFractalOctaves(octaves);
    return noise;
}
