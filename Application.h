// Application.h
#pragma once
#include <SFML/Window.hpp>
#include "Shader.h"
#include "Camera.h"
#include "Cube.h"
#include "Renderer.h"
#include <SFML/System/Time.hpp>

class Application {
private:

    sf::Window window;
    bool running = true;
    Shader* shader;
    Camera camera;
    Cube* cube;
    Renderer* renderer;
    sf::Clock clock;

public:
    Application();
    ~Application();
    void run();
};
