// Shader.h
#pragma once
#include <string>
#include <GL/glew.h>
#include <glm.hpp>

class Shader {
public:
    GLuint ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    void use() const;

    void setMat4(const std::string& name, const float* value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;

    void setInt(const std::string& name, int value) const;

    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setBool(const std::string& name, bool value) const;
private:
    void checkCompileErrors(GLuint shader, std::string type);
};