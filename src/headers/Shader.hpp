#ifndef GLITTER_SHADER_HPP
#define GLITTER_SHADER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include "includes.hpp"


class Shader {
public:
    Shader(const std::string& filename, const GLenum type) {
        GLint status = 0;
        std::string path = shaderFolder + filename;
        std::ifstream fileStream(path);
        std::string src((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
        const char *source = src.c_str();
        const GLenum shaderType = type;

        id = glCreateShader(shaderType);
        glShaderSource(id, 1, &source, nullptr);
        glCompileShader(id);

        glGetShaderiv(id, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE) {
            char infoLog[512];
            glGetShaderInfoLog(id, 512, nullptr, infoLog);
            std::cerr << "Error attaching shader: compilation failed for file "
                      << filename
                      << "\n"
                      << infoLog
                      << std::endl;
        }
    };

    virtual ~Shader() {
        glDeleteShader(id);
    }

    Shader(Shader&) = delete;
    Shader& operator=(Shader&) = delete;

    GLuint id;
protected:
    const std::string shaderFolder = PROJECT_SOURCE_DIR "/src/shaders/";
};


#endif //GLITTER_SHADER_HPP
