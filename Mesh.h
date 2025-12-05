#pragma once
#include <GL/glew.h>
#include <vector>

class Mesh {
protected:
    GLuint VAO, VBO;
    int vertexCount;
    int stride; 

public:
    Mesh(const std::vector<float>& vertices, int stride = 6);
    virtual ~Mesh();
    virtual void draw() const;
};