#ifndef GLITTER_SHADERPROGRAM_HPP
#define GLITTER_SHADERPROGRAM_HPP

#include <string>
#include "includes.hpp"
#include "Shader.hpp"

/**
 * OpenGL shader program wrapper
 */
class ShaderProgram {
public:
    ShaderProgram() {
        program = glCreateProgram();
    }

    ~ShaderProgram() {
        glDeleteProgram(program);
    }

    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram(const ShaderProgram&&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&&) = delete;

    GLuint get() {
        return program;
    }

    void use() {
        glUseProgram(program);
    }

    ShaderProgram* attachShader(const Shader& shader);
    ShaderProgram* detachShader(const Shader& shader);
    ShaderProgram* setUniform(const std::string &name, bool value);
    ShaderProgram* setUniform(const std::string &name, int value);
    ShaderProgram* setUniform(const std::string &name, float value);
    ShaderProgram* setUniform(const std::string &name, const glm::mat4 &transformMatrix);
    ShaderProgram* link();

private:
    inline GLint getUniformLocation(std::string const &name) {
        return glGetUniformLocation(program, name.c_str());
    }

    GLuint program;
};


#endif //GLITTER_SHADERPROGRAM_HPP
