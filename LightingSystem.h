#pragma once
#include <glm.hpp>

class LightingSystem {
public:

    glm::vec3 lightPos;

    glm::vec3 lightColor;

    bool useAmbient;
    bool useDiffuse;
    bool useSpecular;

    float ambientStrength;
    float specularStrength;
    int shininess;

    LightingSystem()
        : lightPos(0.0f, 5.0f, 0.0f),
        lightColor(1.0f, 1.0f, 1.0f),
        useAmbient(true),
        useDiffuse(true),
        useSpecular(true),
        ambientStrength(0.2f),
        specularStrength(1.0f),
        shininess(32) {
    }

    void toggleAmbient() { useAmbient = !useAmbient; }
    void toggleDiffuse() { useDiffuse = !useDiffuse; }
    void toggleSpecular() { useSpecular = !useSpecular; }

    void increaseAmbient() {
        ambientStrength += 0.1f;
        if (ambientStrength > 1.0f) ambientStrength = 1.0f;
    }

    void decreaseAmbient() {
        ambientStrength -= 0.1f;
        if (ambientStrength < 0.0f) ambientStrength = 0.0f;
    }

    void increaseSpecular() {
        specularStrength += 0.1f;
        if (specularStrength > 10.0f) specularStrength = 1.0f;
    }

    void decreaseSpecular() {
        specularStrength -= 0.1f;
        if (specularStrength < 0.0f) specularStrength = 0.0f;
    }

    void changeLightColor(glm::vec3 color) {
        lightColor = color;
    }
};