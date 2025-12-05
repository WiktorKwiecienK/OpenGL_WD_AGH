// SceneObject.h
#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "Mesh.h"
#include "Texture.h"

class SceneObject {
public:
    Mesh* mesh;
    Texture* texture;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    SceneObject(Mesh* mesh, glm::vec3 pos = glm::vec3(0.0f),
        glm::vec3 rot = glm::vec3(0.0f),
        glm::vec3 scl = glm::vec3(1.0f),
        Texture* tex = nullptr)
        : mesh(mesh), texture(tex), position(pos), rotation(rot), scale(scl) {
    }

    glm::mat4 getModelMatrix() const {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, scale);
        return model;
    }

    const Mesh* getMesh() const {
        return mesh;
    }

    Texture* getTexture() const {
        return texture;
    }

    void setTexture(Texture* tex) {
        texture = tex;
    }
};