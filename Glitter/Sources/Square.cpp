#include "Square.hpp"

Square::Square() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    Shader vertex("vertexShaderSquare.vert"), fragment("fragmentShaderSquare.frag");
    shaderProgram = new ShaderProgram();
    shaderProgram->
        attachShader(vertex)->
        attachShader(fragment)->
        link();

    texture2 = new Texture("awesomeface.png");
    texture1 = new Texture("container.jpg");
    // prepare uniforms, should be somewhere else
    shaderProgram->use();
    shaderProgram->setUniform("texture1", 0);
    shaderProgram->setUniform("texture2", 1);
}

Square::~Square() {
    delete texture1;
    delete texture2;
    delete shaderProgram;

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VAO);
}

void Square::render() {
//    texture1->bindToActive(GL_TEXTURE0);
    texture2->bindToActive(GL_TEXTURE1);
    shaderProgram->use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
