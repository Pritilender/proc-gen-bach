#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glitter.hpp"

#ifndef GLITTER_SHADERPROGRAM_HPP
#define GLITTER_SHADERPROGRAM_HPP

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

    GLuint get() {
        return program;
    }

    void use() {
        glUseProgram(program);
    }

    ShaderProgram &attachShader(std::string const &filename);
    ShaderProgram &setUniform(const std::string &name, bool value);
    ShaderProgram &setUniform(const std::string &name, int value);
    ShaderProgram &setUniform(const std::string &name, float value);
    ShaderProgram &setUniform(const std::string &name, const glm::mat4 &transformMatrix);
    bool link();

private:
    GLuint create(std::string const &filename);
    inline GLint getUniformLocation(std::string const &name) {
        return glGetUniformLocation(program, name.c_str());
    }

    GLuint program;
};


#endif //GLITTER_SHADERPROGRAM_HPP
