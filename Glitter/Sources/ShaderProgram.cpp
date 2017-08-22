#include "ShaderProgram.hpp"
#include <iostream>
#include <fstream>

ShaderProgram &ShaderProgram::attachShader(std::string const &filename) {
    std::string baseShaderFolder = PROJECT_SOURCE_DIR "/Glitter/Shaders/";
    std::ifstream fileStream(baseShaderFolder + filename);
    std::string src((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());

    const char *source = src.c_str();
    GLint status = 0;
    GLuint shader = create(filename);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Error attaching shader: compilation failed for file "
                  << filename
                  << "\n"
                  << infoLog
                  << std::endl;
    }

    glAttachShader(program, shader);
    glDeleteShader(shader);

    return *this;
}

ShaderProgram &ShaderProgram::setUniform(const std::string &name, bool value) {
    GLint location = getUniformLocation(name);
    glUniform1i(location, (int)value);
    return *this;
}

ShaderProgram &ShaderProgram::setUniform(const std::string &name, int value) {
    GLint location = getUniformLocation(name);
    glUniform1i(location, value);
    return *this;
}

ShaderProgram &ShaderProgram::setUniform(const std::string &name, float value) {
    GLint location = getUniformLocation(name);
    glUniform1f(location, value);
    return *this;
}

ShaderProgram &ShaderProgram::setUniform(const std::string &name, const glm::mat4 &transformMatrix) {
    GLint location = getUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(transformMatrix));
    return *this;
}

bool ShaderProgram::link() {
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
    return (bool)status;
}

GLuint ShaderProgram::create(std::string const &filename) {
    auto index = filename.rfind('.');
    std::string extension = filename.substr(index + 1);
    GLenum shaderType;

    if (extension == "comp") {
        shaderType = GL_COMPUTE_SHADER;
    } else if (extension == "frag") {
        shaderType = GL_FRAGMENT_SHADER;
    } else if (extension == "geom") {
        shaderType = GL_GEOMETRY_SHADER;
    } else if (extension == "vert") {
        shaderType = GL_VERTEX_SHADER;
    } else {
        // TODO better handling
        std::cerr << "Error creating shader: unkown shader type " << extension << std::endl;
        shaderType = false;
    }
    return glCreateShader(shaderType);
}
