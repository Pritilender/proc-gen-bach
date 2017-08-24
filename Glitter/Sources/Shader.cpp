#include "Shader.hpp"
#include <iostream>
#include <fstream>

const std::string Shader::shaderFolder = PROJECT_SOURCE_DIR "/Glitter/Shaders/";

/**
 * Find the shader type based on the extension
 * @param filename - Shader's filename
 * @return GLenum describing the shader type or 0 if no match
 */
const GLenum getShaderType(std::string const &filename) {
    auto index = filename.rfind('.');
    std::string extension = filename.substr(index + 1);
    GLenum shaderType = 0;

    if (extension == "comp") {
        shaderType = GL_COMPUTE_SHADER;
    } else if (extension == "frag") {
        shaderType = GL_FRAGMENT_SHADER;
    } else if (extension == "geom") {
        shaderType = GL_GEOMETRY_SHADER;
    } else if (extension == "vert") {
        shaderType = GL_VERTEX_SHADER;
    }

    return shaderType;
}

Shader::Shader(const std::string &filename) {
    GLint status = 0;
    std::string path = shaderFolder + filename;
    std::ifstream fileStream(path);
    std::string src((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
    const char *source = src.c_str();
    const GLenum shaderType = getShaderType(filename);

    shader = glCreateShader(shaderType);
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
}
