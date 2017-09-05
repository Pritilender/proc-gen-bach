#ifndef GLITTER_VERTEXSHADER_HPP
#define GLITTER_VERTEXSHADER_HPP

#include "Shader.hpp"

class VertexShader : public Shader {
public:
    VertexShader(const std::string filename) : Shader(filename, GL_VERTEX_SHADER) {};
};


#endif //GLITTER_VERTEXSHADER_HPP
