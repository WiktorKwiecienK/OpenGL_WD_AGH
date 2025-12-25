<<<<<<< HEAD
ï»¿#include "Texture.h"
=======
#include "Texture.h"
>>>>>>> f548684fc4b9fc87d9e22157b8360ae2e11358c9
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

Texture::Texture(const char* texturePath) {
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

<<<<<<< HEAD
        std::cout << "Tekstura zaÅ‚adowana: " << texturePath << " (" << width << "x" << height << ", " << nrChannels << " kanaÅ‚Ã³w)" << std::endl;
    }
    else {
        std::cerr << "BÅ‚Ä…d Å‚adowania tekstury: " << texturePath << std::endl;
=======
        std::cout << "Tekstura za³adowana: " << texturePath << " (" << width << "x" << height << ", " << nrChannels << " kana³ów)" << std::endl;
    }
    else {
        std::cerr << "B³¹d ³adowania tekstury: " << texturePath << std::endl;
>>>>>>> f548684fc4b9fc87d9e22157b8360ae2e11358c9
    }

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
    glDeleteTextures(1, &ID);
}

void Texture::bind(GLuint textureUnit) const {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}