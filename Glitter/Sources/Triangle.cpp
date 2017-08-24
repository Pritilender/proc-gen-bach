#include "Triangle.hpp"

Triangle::Triangle() {
    // generate vertex array
    glGenVertexArrays(1, &VAO);
    // generate new buffers
    glGenBuffers(1, &VBO);

    // setup buffers for binded vertex array
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    Shader vertex("vertexShader.vert"), fragment("fragmentShader.frag");
    this->shaderProgram = new ShaderProgram();
    this->shaderProgram->
        attachShader(vertex)->
        attachShader(fragment)->
        link();

    // unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Triangle::~Triangle() {
    // delete buffers
    glDeleteBuffers(1, &VBO);
    // delete vertex array
    glDeleteVertexArrays(1, &VAO);
    delete shaderProgram;
}

void Triangle::render() {
    shaderProgram->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}
