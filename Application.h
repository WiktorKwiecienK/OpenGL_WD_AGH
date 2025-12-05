// Application.h
#pragma once
#include <SFML/Window.hpp>
#include "Shader.h"
#include "Camera.h"
#include "Cube.h"
#include "Renderer.h"
#include "Scene.h"
#include "LightingSystem.h"
#include <SFML/System/Time.hpp>

class Application {
private:
    sf::Window window;
    bool running = true;
    Shader* shader;
    Camera camera;
    Scene* scene;
    Renderer* renderer;
    LightingSystem* lighting;
    sf::Clock clock;

public:
    Application();
    ~Application();
    void run();
    void setupScene();
    void handleInput(float dt);
    void displayLightingInfo();
};