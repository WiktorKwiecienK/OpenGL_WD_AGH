// Shader.h
#pragma once
#include <string>
#include <GL/glew.h>

class Shader {
public:
    GLuint ID;
    Shader(const char* vertexPath, const char* fragmentPath);
    void use() const;
    void setMat4(const std::string& name, const float* value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void checkCompileErrors(GLuint shader, std::string type);
};
