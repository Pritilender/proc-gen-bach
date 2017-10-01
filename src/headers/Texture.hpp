#ifndef GLITTER_TEXTURE_HPP
#define GLITTER_TEXTURE_HPP

#include <string>
#include "includes.hpp"

class Texture {
public:
    explicit Texture(const std::string& imageName);
    ~Texture() {
        glDeleteTextures(1, &texture);
    }

    inline void bind() {
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    inline void bindToActive(GLenum unit) {
        glActiveTexture(unit);
        glBindTexture(GL_TEXTURE_2D, texture);
    }
private:
    GLuint texture;
};


#endif //GLITTER_TEXTURE_HPP
