#include "Renderer.h"
#include <gtc/type_ptr.hpp>

Renderer::Renderer(int width, int height) {

    projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
    glEnable(GL_DEPTH_TEST);

}

void Renderer::render(const Shader& shader, const Mesh& mesh, const Camera& camera, float time) {
   
    shader.use();

	float speed_cube = .3f;

    glm::mat4 model = glm::rotate(glm::mat4(1.0f), time * speed_cube, glm::vec3(0.5f, 1.0f, 0.0f));

  //macierz widoku

    glm::mat4 view = camera.getViewMatrix();

    shader.setMat4("model", glm::value_ptr(model));
    shader.setMat4("view", glm::value_ptr(view));
    shader.setMat4("proj", glm::value_ptr(projection));

    mesh.draw();

}
