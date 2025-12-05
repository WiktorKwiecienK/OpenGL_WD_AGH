// Renderer.h
#pragma once
#include <glm.hpp>
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "Scene.h"

class Renderer {
public:
    glm::mat4 projection;

    Renderer(int width, int height);
    void render(const Shader& shader, const Scene& scene, const Camera& camera, float time);
    void renderObject(const Shader& shader, const SceneObject& object, const Camera& camera, float time);
};