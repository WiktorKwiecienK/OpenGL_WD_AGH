<<<<<<< HEAD
ï»¿#include "OBJLoader.h"
=======
#include "OBJLoader.h"
>>>>>>> f548684fc4b9fc87d9e22157b8360ae2e11358c9
#include <fstream>
#include <sstream>
#include <iostream>

OBJLoader::OBJLoader() {}

bool OBJLoader::loadFromFile(const std::string& filepath) {
    std::ifstream file(filepath);

    if (!file.is_open()) {
<<<<<<< HEAD
        std::cerr << "Nie moÅ¼na otworzyÄ‡ pliku: " << filepath << std::endl;
        return false;
    }

    // WyczyÅ›Ä‡ poprzednie dane
=======
        std::cerr << "Nie mo¿na otworzyæ pliku: " << filepath << std::endl;
        return false;
    }

    // Wyczyœæ poprzednie dane
>>>>>>> f548684fc4b9fc87d9e22157b8360ae2e11358c9
    temp_vertices.clear();
    temp_texCoords.clear();
    temp_normals.clear();
    temp_faces.clear();

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        parseLine(line);
    }

    file.close();

<<<<<<< HEAD
    std::cout << "ZaÅ‚adowano model: " << filepath << std::endl;
=======
    std::cout << "Za³adowano model: " << filepath << std::endl;
>>>>>>> f548684fc4b9fc87d9e22157b8360ae2e11358c9
    printInfo();

    return true;
}

void OBJLoader::parseLine(const std::string& line) {
    std::stringstream ss(line);
    std::string prefix;
    ss >> prefix;

    if (prefix == "v") {
        parseVertex(line);
    }
    else if (prefix == "vt") {
        parseTexCoord(line);
    }
    else if (prefix == "vn") {
        parseNormal(line);
    }
    else if (prefix == "f") {
        parseFace(line);
    }
}

void OBJLoader::parseVertex(const std::string& line) {
    std::stringstream ss(line);
    std::string prefix;
    glm::vec3 vertex;

    ss >> prefix >> vertex.x >> vertex.y >> vertex.z;
    temp_vertices.push_back(vertex);
}

void OBJLoader::parseTexCoord(const std::string& line) {
    std::stringstream ss(line);
    std::string prefix;
    glm::vec2 texCoord;

    ss >> prefix >> texCoord.x >> texCoord.y;
    temp_texCoords.push_back(texCoord);
}

void OBJLoader::parseNormal(const std::string& line) {
    std::stringstream ss(line);
    std::string prefix;
    glm::vec3 normal;

    ss >> prefix >> normal.x >> normal.y >> normal.z;
    temp_normals.push_back(normal);
}

void OBJLoader::parseFace(const std::string& line) {
    std::stringstream ss(line);
    std::string prefix;
    ss >> prefix;

    Face face;
    std::string vertexData;

    while (ss >> vertexData) {
        std::stringstream vss(vertexData);
        std::string indexStr;
        int indices[3] = { 0, 0, 0 }; // vertex, texCoord, normal
        int i = 0;

        while (std::getline(vss, indexStr, '/') && i < 3) {
            if (!indexStr.empty()) {
                indices[i] = std::stoi(indexStr);
            }
            i++;
        }

<<<<<<< HEAD
        face.vertexIndices.push_back(indices[0] - 1);  // OBJ uÅ¼ywa indeksÃ³w od 1
=======
        face.vertexIndices.push_back(indices[0] - 1);  // OBJ u¿ywa indeksów od 1
>>>>>>> f548684fc4b9fc87d9e22157b8360ae2e11358c9
        if (indices[1] > 0) face.texCoordIndices.push_back(indices[1] - 1);
        if (indices[2] > 0) face.normalIndices.push_back(indices[2] - 1);
    }

    temp_faces.push_back(face);
}

std::vector<float> OBJLoader::getVertexData(const glm::vec3& color) {
    return getVertexDataRange(0, temp_faces.size(), color);
}

std::vector<float> OBJLoader::getVertexDataRange(int startFace, int endFace, const glm::vec3& color) {
    std::vector<float> vertexData;

    // Ogranicz zakres
    if (startFace < 0) startFace = 0;
    if (endFace > temp_faces.size()) endFace = temp_faces.size();

    for (int faceIdx = startFace; faceIdx < endFace; faceIdx++) {
        const Face& face = temp_faces[faceIdx];

<<<<<<< HEAD
        // Dla kaÅ¼dego wierzchoÅ‚ka w Å›cianie
=======
        // Dla ka¿dego wierzcho³ka w œcianie
>>>>>>> f548684fc4b9fc87d9e22157b8360ae2e11358c9
        for (size_t i = 0; i < face.vertexIndices.size(); i++) {
            unsigned int vertexIdx = face.vertexIndices[i];

            // Pozycja
            if (vertexIdx < temp_vertices.size()) {
                vertexData.push_back(temp_vertices[vertexIdx].x);
                vertexData.push_back(temp_vertices[vertexIdx].y);
                vertexData.push_back(temp_vertices[vertexIdx].z);
            }

            // Kolor
            vertexData.push_back(color.r);
            vertexData.push_back(color.g);
            vertexData.push_back(color.b);

<<<<<<< HEAD
            // Tekstura (jeÅ›li jest)
=======
            // Tekstura (jeœli jest)
>>>>>>> f548684fc4b9fc87d9e22157b8360ae2e11358c9
            if (i < face.texCoordIndices.size() && face.texCoordIndices[i] < temp_texCoords.size()) {
                vertexData.push_back(temp_texCoords[face.texCoordIndices[i]].x);
                vertexData.push_back(temp_texCoords[face.texCoordIndices[i]].y);
            }
            else {
                vertexData.push_back(0.0f);
                vertexData.push_back(0.0f);
            }

<<<<<<< HEAD
            // Normalna (jeÅ›li jest)
=======
            // Normalna (jeœli jest)
>>>>>>> f548684fc4b9fc87d9e22157b8360ae2e11358c9
            if (i < face.normalIndices.size() && face.normalIndices[i] < temp_normals.size()) {
                vertexData.push_back(temp_normals[face.normalIndices[i]].x);
                vertexData.push_back(temp_normals[face.normalIndices[i]].y);
                vertexData.push_back(temp_normals[face.normalIndices[i]].z);
            }
            else {
<<<<<<< HEAD
                // JeÅ›li nie ma normalnych, oblicz je
=======
                // Jeœli nie ma normalnych, oblicz je
>>>>>>> f548684fc4b9fc87d9e22157b8360ae2e11358c9
                vertexData.push_back(0.0f);
                vertexData.push_back(1.0f);
                vertexData.push_back(0.0f);
            }
        }
    }

    return vertexData;
}

void OBJLoader::printInfo() const {
<<<<<<< HEAD
    std::cout << "  WierzchoÅ‚ki: " << temp_vertices.size() << std::endl;
    std::cout << "  Koordynaty tekstur: " << temp_texCoords.size() << std::endl;
    std::cout << "  Wektory normalne: " << temp_normals.size() << std::endl;
    std::cout << "  Åšciany: " << temp_faces.size() << std::endl;
=======
    std::cout << "  Wierzcho³ki: " << temp_vertices.size() << std::endl;
    std::cout << "  Koordynaty tekstur: " << temp_texCoords.size() << std::endl;
    std::cout << "  Wektory normalne: " << temp_normals.size() << std::endl;
    std::cout << "  Œciany: " << temp_faces.size() << std::endl;
>>>>>>> f548684fc4b9fc87d9e22157b8360ae2e11358c9
}