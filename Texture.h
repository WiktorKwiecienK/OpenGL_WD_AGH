// Texture.h
#pragma once
#include <GL/glew.h>
#include <string>

class Texture {
private:
    GLuint ID;
    int width, height, nrChannels;

public:
    Texture(const char* texturePath);
    ~Texture();

    void bind(GLuint textureUnit = 0) const;
    void unbind() const;
    GLuint getID() const { return ID; }
};