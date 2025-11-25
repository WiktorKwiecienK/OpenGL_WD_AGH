// Mesh.h
#pragma once
#include <GL/glew.h>
#include <vector>

class Mesh {
protected:
    GLuint VAO, VBO;
    int vertexCount;

public:
    Mesh(const std::vector<float>& vertices);
    virtual ~Mesh();
    virtual void draw() const;
};
