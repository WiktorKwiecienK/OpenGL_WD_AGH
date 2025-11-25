#include "Application.h"
#include <GL/glew.h>

Application::Application() :
   
    window(sf::VideoMode(1200, 800), "OpenGL 3D Kamera FPS", sf::Style::Close) {

    window.setMouseCursorGrabbed(true);
    window.setMouseCursorVisible(false);

	window.setFramerateLimit(165);
	
    glewExperimental = GL_TRUE;
    glewInit();



    shader = new Shader("vertex.glsl", "fragment.glsl");
    cube = new Cube();
    renderer = new Renderer(1200, 800);
}

Application::~Application() {
    delete shader;
    delete cube;
    delete renderer;
}

void Application::run() {

    bool running = true;
    sf::Clock clock;
    sf::Clock fpsClockForTitle;
    int frameCount = 0;

    while (running) {

        sf::Time deltaTime = clock.restart(); 
        float dt = deltaTime.asMicroseconds();

        // FPS counter
        frameCount++;
        if (fpsClockForTitle.getElapsedTime().asSeconds() >= 1.0f) {
            window.setTitle("OpenGL 3D Kamera FPS - FPS: " + std::to_string(frameCount));
            frameCount = 0;
            fpsClockForTitle.restart();
        }

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                running = false;
            
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    running = false;
            }
            
            if (event.type == sf::Event::MouseMoved) {
                static float lastX = 600, lastY = 400; 

                float xoffset = event.mouseMove.x - lastX;
                float yoffset = lastY - event.mouseMove.y;

                lastX = event.mouseMove.x;
                lastY = event.mouseMove.y;

                camera.processMouse(xoffset, yoffset);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) camera.processKeyboard('W', dt);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) camera.processKeyboard('S', dt);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) camera.processKeyboard('A', dt);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) camera.processKeyboard('D', dt);

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer->render(*shader, *cube, camera, clock.getElapsedTime().asSeconds());

        window.display();
    }
}