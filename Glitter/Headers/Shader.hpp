#ifndef GLITTER_SHADER_HPP
#define GLITTER_SHADER_HPP

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader {
public:
    explicit Shader(const std::string& filename);
    ~Shader() {
        glDeleteShader(shader);
    }

    inline const GLuint get() const {
        return shader;
    }

    static const std::string shaderFolder; //!< Shader folder default location

private:
    GLuint shader;
};


#endif //GLITTER_SHADER_HPP
