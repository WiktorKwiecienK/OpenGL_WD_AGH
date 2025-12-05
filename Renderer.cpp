#include "Renderer.h"
#include <gtc/type_ptr.hpp>

Renderer::Renderer(int width, int height) {
    projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void Renderer::render(const Shader& shader, const Scene& scene, const Camera& camera, float time) {
    shader.use();

    glm::mat4 view = camera.getViewMatrix();
    shader.setMat4("view", glm::value_ptr(view));
    shader.setMat4("proj", glm::value_ptr(projection));

    for (const auto& object : scene.getObjects()) {
        renderObject(shader, *object, camera, time);
    }
}

void Renderer::renderObject(const Shader& shader, const SceneObject& object, const Camera& camera, float time) {
    glm::mat4 model = object.getModelMatrix();

    shader.setMat4("model", glm::value_ptr(model));

    if (object.getTexture() != nullptr) {
        object.getTexture()->bind(0);
        shader.setInt("useTexture", 1);
        shader.setInt("texture1", 0);
    }
    else {
        shader.setInt("useTexture", 0);
    }

    object.getMesh()->draw();
}