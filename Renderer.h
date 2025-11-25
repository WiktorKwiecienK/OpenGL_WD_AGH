// Renderer.h
#pragma once
#include <glm.hpp>
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"

class Renderer {
public:
    glm::mat4 projection;
    Renderer(int width, int height);
    void render(const Shader& shader, const Mesh& mesh, const Camera& camera, float time);
};
