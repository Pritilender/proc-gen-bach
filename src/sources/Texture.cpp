#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include "Texture.hpp"
#include "includes.hpp"

using namespace std;

const std::string Texture::assetFolder = PROJECT_SOURCE_DIR "/src/resources/";

Texture::Texture(const string &imageName) {
    string path = assetFolder + imageName;
    bool isPng = path.substr(path.rfind('.') + 1) == "png";
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // Setup wrapping and filtering for current texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, isPng ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        // TODO some error handling...
        cerr << "Unable to load texture image from " << path << endl;
    }
    stbi_image_free(data);
}
