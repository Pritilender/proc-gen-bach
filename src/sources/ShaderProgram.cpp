#include "ShaderProgram.hpp"
#include <iostream>
#include <fstream>

ShaderProgram* ShaderProgram::attachShader(const Shader& shader) {
    glAttachShader(program, shader.id);
    return this;
}

ShaderProgram* ShaderProgram::detachShader(const Shader& shader) {
    glDetachShader(program, shader.id);
    return this;
}

ShaderProgram* ShaderProgram::setUniform(const std::string &name, bool value) {
    GLint location = getUniformLocation(name);
    glUniform1i(location, (int)value);
    return this;
}

ShaderProgram* ShaderProgram::setUniform(const std::string &name, int value) {
    GLint location = getUniformLocation(name);
    glUniform1i(location, value);
    return this;
}

ShaderProgram* ShaderProgram::setUniform(const std::string &name, float value) {
    GLint location = getUniformLocation(name);
    glUniform1f(location, value);
    return this;
}

ShaderProgram* ShaderProgram::setUniform(const std::string &name, const glm::mat3 &transformMatrix) {
    GLint location = getUniformLocation(name);
    glUniformMatrix3fv(location, 1, GL_FALSE, &transformMatrix[0][0]);
    return this;
}

ShaderProgram* ShaderProgram::setUniform(const std::string &name, const glm::mat4 &transformMatrix) {
    GLint location = getUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, &transformMatrix[0][0]);
    return this;
}

ShaderProgram* ShaderProgram::setUniform(const std::string &name, const glm::vec3 &vector) {
    GLint location = getUniformLocation(name);
    glUniform3f(location, vector.x, vector.y, vector.z);
    return this;
}

ShaderProgram* ShaderProgram::setUniform(const std::string &name, const glm::vec4 &vector) {
    GLint location = getUniformLocation(name);
    glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
    return this;
}

ShaderProgram* ShaderProgram::link() {
    GLint status = 0;
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (status == GL_FALSE) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "Error linking the program.\n"
                  << infoLog
                  << std::endl;
    }
    return this;
}
