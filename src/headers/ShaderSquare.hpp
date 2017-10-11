#ifndef GLITTERING_GLAMOUR_SHADERSQUARE_HPP
#define GLITTERING_GLAMOUR_SHADERSQUARE_HPP

#include "includes.hpp"
#include "NoiseSquare.hpp"
#include "VertexShader.hpp"
#include "FragmentShader.hpp"

class ShaderSquare : public NoiseSquare {
public:
    ShaderSquare(int xMax, float res) : NoiseSquare(
        {std::make_shared<VertexShader>("noiseShader.vert"), std::make_shared<FragmentShader>("adsPerPixel.frag")},
        {"deep-water.jpg",
         "coastal-water.jpg",
         "beach.jpg",
         "lowlands.jpg",
         "hills.jpg",
         "mountains.jpg",
         "mid-snow.jpg",
         "snow.jpg"},
        res,
        xMax) {
        prepareIndices();
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(glm::vec3), &indices[0], GL_STATIC_DRAW);

        program.use();
        program.setUniform("Seed", seed);
        program.setUniform("Octaves", octaves);
        program.setUniform("Frequency", freq);
        program.setUniform("Lacunarity", lacunarity);
        program.setUniform("Persistence", persistence);
        program.setUniform("Resolution", resolution);
        program.setUniform("XMax", this->xMax);
        program.setUniform("xOffset", xOffset);
        program.setUniform("zOffset", zOffset);
    };

    ShaderSquare() = delete;

    ~ShaderSquare() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &EBO);
    }

    void draw() override {
        program.use();
        textures.bindToActive(GL_TEXTURE0);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3 * indices.size(), GL_UNSIGNED_INT, 0);
    }

    void uploadNewData() override {
        program.use();
        program.setUniform("Seed", seed);
        program.setUniform("Octaves", octaves);
        program.setUniform("Frequency", freq);
        program.setUniform("Lacunarity", lacunarity);
        program.setUniform("Persistence", persistence);
        program.setUniform("xOffset", xOffset);
        program.setUniform("zOffset", zOffset);
    }

private:
    void prepareIndices() {
        std::vector<glm::uvec3> ind;
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

    std::vector<glm::uvec3> indices;
    GLuint VAO;
    GLuint EBO;
};

#endif //GLITTERING_GLAMOUR_SHADERSQUARE_HPP
