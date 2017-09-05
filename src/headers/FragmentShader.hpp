#ifndef GLITTER_FRAGMENTSHADER_HPP
#define GLITTER_FRAGMENTSHADER_HPP

#include "Shader.hpp"

class FragmentShader : public Shader {
public:
    FragmentShader(const std::string filename) : Shader(filename, GL_FRAGMENT_SHADER) {};
};


#endif //GLITTER_FRAGMENTSHADER_HPP
