#ifndef GLAMOUR_TEXTUREARRAY_HPP
#define GLAMOUR_TEXTUREARRAY_HPP


#include "includes.hpp"

class TextureArray {
public:
    explicit TextureArray(const std::vector<std::string> &images): images(images) {
        glGenTextures(1, &texture);
    }

    void prepare() {
        glBindTexture(GL_TEXTURE_2D_ARRAY, texture);

//        glTexStorage3D(GL_TEXTURE_2D_ARRAY, 11, GL_RGBA8, 1024, 1024, images.size()); // todo something about this hardcoding
        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, 2048, 2048, images.size(), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        const std::string assetFolder = PROJECT_SOURCE_DIR "/src/resources/";
        for (unsigned int i = 0; i < images.size(); i++) {
            std::string path = assetFolder + images[i];
            bool isPng = path.substr(path.rfind('.') + 1) == "png";
            int width, height, noChannels;
            stbi_set_flip_vertically_on_load(true);
            unsigned char *data = stbi_load(path.c_str(), &width, &height, &noChannels, 0);
            if (data) {
                glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, isPng ? GL_RGBA : GL_RGB,
                                GL_UNSIGNED_BYTE, data);
            } else {
                std::cerr << "Unable to load texture from " << path << std::endl;
            }
            stbi_image_free(data);
        }
        glGenerateTextureMipmap(texture);
    }

    ~TextureArray() {
        glDeleteTextures(1, &texture);
    }

    inline void bind() {
        glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
    }

    inline void bindToActive(GLenum unit) {
        glActiveTexture(unit);
        glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
    }

private:
    std::vector<std::string> images;
    GLuint texture;
};


#endif //GLAMOUR_TEXTUREARRAY_HPP
