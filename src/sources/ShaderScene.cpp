#include <FragmentShader.hpp>
#include <VertexShader.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "ShaderScene.hpp"

using namespace std;
using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;
using glm::radians;

ShaderScene::ShaderScene(int w, int h) : Scene(w, h),
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

    prepareIndices();
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(vec3), &indices[0], GL_STATIC_DRAW);
}

void ShaderScene::prepareIndices() {
    vector<glm::uvec3> ind;
    auto forwards = [&](int i, int o) {
        glm::uvec3 vertexIndices = glm::uvec3(o + i, o + i + 1, o + i + resolution);
        ind.push_back(vertexIndices);
    };
    auto backwards = [&](int i, int o) {
        glm::uvec3 vertexIndices = glm::uvec3(o + i, o + i + resolution, o + i + resolution - 1);
        ind.push_back(vertexIndices);
    };

    for (int i = 0; i < resolution - 1; i++) {
        auto offset = i * resolution;
        for (int j = 0; j < resolution; j++) {
            if (j == 0) {
                forwards(j, offset);
            } else if (j == resolution - 1) {
                backwards(j, offset);
            } else {
                backwards(j, offset);
                forwards(j, offset);
            }
        }
    }
    indices = ind;
}

void ShaderScene::render() {
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

    // render
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 3 * indices.size(), GL_UNSIGNED_INT, 0);
}


void ShaderScene::redraw() {
    program->use();
    program->setUniform("Seed", seed);
    program->setUniform("Octaves", octaves);
    program->setUniform("Frequency", freq);
    program->setUniform("Lacunarity", lacunarity);
    program->setUniform("Persistence", persistence);
    program->setUniform("Resolution", resolution);
    program->setUniform("XMax", xMax);
    printInfo();
}

void ShaderScene::setupProgram() {
    VertexShader vertex("noiseShader.vert");
    FragmentShader fragment("adsPerPixel.frag");

    program->attachShader(vertex)->attachShader(fragment);
    program->link();

    // setup projection matrix
    mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 2000.0f);
    program->use();
    program->setUniform("ProjectionMatrix", projection);
    program->setUniform("Seed", seed);
    program->setUniform("Octaves", octaves);
    program->setUniform("Frequency", freq);
    program->setUniform("Lacunarity", lacunarity);
    program->setUniform("Persistence", persistence);
}

void ShaderScene::setupTexture() {
    program->use();
    textures.prepare();
    program->setUniform("textures", 0);
    // setup for texture coordinates generation
    program->setUniform("Resolution", resolution);
    program->setUniform("XMax", xMax);
}
