#include "ModelMesh.h"

ModelMesh::ModelMesh(const std::string& objPath, const glm::vec3& color)
    : Mesh({}, 11), modelPath(objPath) {

    if (!loader.loadFromFile(objPath)) {
        std::cerr << "B³¹d ³adowania modelu: " << objPath << std::endl;
        return;
    }

    std::vector<float> vertices = loader.getVertexData(color);

    if (vertices.empty()) {
        std::cerr << "Brak danych wierzcho³ków!" << std::endl;
        return;
    }

    vertexCount = vertices.size() / stride;

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Pozycja (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Kolor (location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Tekstura (location = 2)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Normalna (location = 3)
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}

ModelMesh::ModelMesh(const std::string& objPath, int startFace, int endFace, const glm::vec3& color)
    : Mesh({}, 11), modelPath(objPath) {

    if (!loader.loadFromFile(objPath)) {
        std::cerr << "B³¹d ³adowania modelu: " << objPath << std::endl;
        return;
    }

    std::cout << "£adowanie fragmentu modelu: œciany " << startFace << " do " << endFace << std::endl;

    std::vector<float> vertices = loader.getVertexDataRange(startFace, endFace, color);

    if (vertices.empty()) {
        std::cerr << "Brak danych wierzcho³ków dla fragmentu!" << std::endl;
        return;
    }

    vertexCount = vertices.size() / stride;

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);

    std::cout << "Za³adowano " << vertexCount << " wierzcho³ków dla fragmentu" << std::endl;
}