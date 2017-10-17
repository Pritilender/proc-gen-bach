#include <VertexShader.hpp>
#include <NoiseSquare.hpp>
#include <FragmentShader.hpp>
#include <CpuTimer.hpp>
#include "CpuSquare.hpp"

using glm::vec3;
using glm::uvec3;
using namespace std;

CpuSquare::CpuSquare(const int res, const float xM) :
        NoiseSquare({std::make_shared<VertexShader>("adsPerPixel.vert"),
                     std::make_shared<FragmentShader>("adsPerPixel.frag")},
                    {"deep-water.jpg",
                     "coastal-water.jpg",
                     "beach.jpg",
                     "lowlands.jpg",
                     "hills.jpg",
                     "mountains.jpg",
                     "mid-snow.jpg",
                     "snow.jpg"},
                    res,
                    xM),
        step(xMax / (resolution - 1)) {

    noise.SetFrequency(freq);
    noise.SetFractalLacunarity(lacunarity);
    noise.SetFractalGain(persistence);
    noise.SetFractalOctaves(octaves);
    noise.SetNoiseType(FastNoise::PerlinFractal);

    prepareVerticesAndIndices(0.0f, 0.0f);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // vertices
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    glEnableVertexAttribArray(0);

    // normals
    glGenBuffers(1, &NBO);
    glBindBuffer(GL_ARRAY_BUFFER, NBO);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec3), &normals[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    glEnableVertexAttribArray(1);

    // indices
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(vec3), &indices[0], GL_STATIC_DRAW);
}

CpuSquare::~CpuSquare() {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &NBO);
    glDeleteBuffers(1, &VAO);
}

void CpuSquare::draw() {
    program.use();
    textures.bindToActive(GL_TEXTURE0);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 3 * indices.size(), GL_UNSIGNED_INT, 0);
}

void CpuSquare::prepareVerticesAndIndices(float xOffset, float zOffset) {
    vector<vec3> v, n;
    vector<uvec3> ind;

    auto normalsFromIndices = [&](glm::uvec3 indices) {
        vec3 p1 = v[indices.x];
        vec3 p2 = v[indices.y];
        vec3 p3 = v[indices.z];
        vec3 normal = glm::normalize(glm::cross(p3 - p1, p2 - p1));

        n[indices.x] += normal;
        n[indices.y] += normal;
        n[indices.z] += normal;
    };
    auto forwards = [&](int i, int o) {
        glm::uvec3 vertexIndices = glm::uvec3(o + i, o + i + 1, o + i + resolution);
        ind.push_back(vertexIndices);
        normalsFromIndices(vertexIndices);
    };
    auto backwards = [&](int i, int o) {
        glm::uvec3 vertexIndices = glm::uvec3(o + i, o + i + resolution, o + i + resolution - 1);
        ind.push_back(vertexIndices);
        normalsFromIndices(vertexIndices);
    };

    float z = 0.0f;
    for (int j = 0; j < resolution; j++) {
        float x = 0.0f;
//        #pragma omp for schedule(dynamic, 20)
        for (int i = 0; i < resolution; i++) {
            vec3 vertex(x, noise.GetNoise(x + xOffset, z + zOffset), z);

            vertex.y *= vertex.y > 0 ? 20.0f : 5.0f; // altitude correction
            v.push_back(vertex);
            n.emplace_back(vec3(0.0f, 0.0f, 0.0f)); // generate empty normal also
            x += step;
        }
        z += step;
    }

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

    vertices = v;
    normals = n;
    indices = ind;
}

void CpuSquare::uploadNewData() {
    prepareVerticesAndIndices(xOffset, zOffset);
    // vertices
    glNamedBufferSubData(VBO, 0, vertices.size() * sizeof(vec3), &vertices[0]);
    // normals
    glNamedBufferSubData(NBO, 0, normals.size() * sizeof(vec3), &normals[0]);
}
