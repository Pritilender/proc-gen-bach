#include "Square.hpp"
#include <glm/gtx/normal.hpp>

using glm::vec3;

Square::Square(int res, float xM) : resolution(res), xMax(xM), step(xMax / (resolution - 1)) {
    prepareVerticesAndIndices();
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

Square::~Square() {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &NBO);
    glDeleteBuffers(1, &VAO);
}

void Square::draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 3 * indices.size(), GL_UNSIGNED_INT, 0);
}

void Square::prepareVerticesAndIndices() {
    auto normalsFromIndices = [&](glm::uvec3 indices) {
        vec3 p1 = vertices[indices.x];
        vec3 p2 = vertices[indices.y];
        vec3 p3 = vertices[indices.z];
        vec3 normal = glm::normalize(glm::cross(p3 - p1, p2 - p1));

        normals[indices.x] += normal;
        normals[indices.y] += normal;
        normals[indices.z] += normal;
    };
    auto forwards = [&](int i, int o) {
        glm::uvec3 vertexIndices = glm::uvec3(o + i, o + i + 1, o + i + resolution);
        indices.push_back(vertexIndices);
        normalsFromIndices(vertexIndices);
    };
    auto backwards = [&](int i, int o) {
        glm::uvec3 vertexIndices = glm::uvec3(o + i, o + i + resolution, o + i + resolution - 1);
        indices.push_back(vertexIndices);
        normalsFromIndices(vertexIndices);
    };

    float z = 0.0f;
    for (int i = 0; i < resolution; i++) {
        float x = 0.0f;
        for (int j = 0; j < resolution; j++) {
            vec3 vertex = vec3(x, sinf(x* z), z);
            vertices.push_back(vertex);
            normals.push_back(vec3(0.0f, 0.0f, 0.0f)); // generate empty normal also
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

    for (auto &n: normals) {
        n = glm::normalize(n);
//        std::cout << n.x << " " << n.y << " " << n.z << std::endl;
    }
}
