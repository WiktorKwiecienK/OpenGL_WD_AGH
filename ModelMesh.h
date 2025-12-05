// ModelMesh.h
#pragma once
#include <iostream>
#include "Mesh.h"
#include "OBJLoader.h"
#include <string>
#include <glm.hpp>

class ModelMesh : public Mesh {
private:
    std::string modelPath;
    OBJLoader loader;

public:
    ModelMesh(const std::string& objPath, const glm::vec3& color = glm::vec3(1.0f));

    // Konstruktor dla fragmentu modelu
    ModelMesh(const std::string& objPath, int startFace, int endFace, const glm::vec3& color = glm::vec3(1.0f));

    int getFaceCount() const { return loader.getFaceCount(); }
};