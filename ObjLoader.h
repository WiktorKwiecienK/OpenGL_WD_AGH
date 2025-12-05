// OBJLoader.h
#pragma once
#include <vector>
#include <string>
#include <glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texCoord;
    glm::vec3 normal;
};

struct Face {
    std::vector<unsigned int> vertexIndices;
    std::vector<unsigned int> texCoordIndices;
    std::vector<unsigned int> normalIndices;
};

class OBJLoader {
private:
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_texCoords;
    std::vector<glm::vec3> temp_normals;
    std::vector<Face> temp_faces;

    void parseLine(const std::string& line);
    void parseVertex(const std::string& line);
    void parseTexCoord(const std::string& line);
    void parseNormal(const std::string& line);
    void parseFace(const std::string& line);

public:
    OBJLoader();

    bool loadFromFile(const std::string& filepath);
    std::vector<float> getVertexData(const glm::vec3& color = glm::vec3(1.0f));
    std::vector<float> getVertexDataRange(int startFace, int endFace, const glm::vec3& color = glm::vec3(1.0f));

    int getFaceCount() const { return temp_faces.size(); }
    void printInfo() const;
};