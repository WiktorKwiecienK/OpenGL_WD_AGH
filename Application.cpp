#include "Application.h"
#include <GL/glew.h>
#include <iostream>
#include "ModelMesh.h"

Application::Application() :
    window(sf::VideoMode(1200, 800), "OpenGL 3D Kamera FPS", sf::Style::Close,
        sf::ContextSettings(24, 8, 0, 3, 3)) {

    window.setMouseCursorGrabbed(true);
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(165);

    glewExperimental = GL_TRUE;
    glewInit();

    shader = new Shader("vertex.glsl", "fragment.glsl");
    scene = new Scene();
    renderer = new Renderer(1200, 800);
    lighting = new LightingSystem();

    setupScene();
    displayLightingInfo();
}

Application::~Application() {
    delete shader;
    delete scene;
    delete renderer;
    delete lighting;
}

void Application::setupScene() {

    Texture* dirtTexture = new Texture("textures/dirt.png");
    Texture* JosephTexture = new Texture("textures/Pan_zywiec_zdroj_wynalazca_wody.png");

    Cube* cube1 = new Cube();
    scene->addObject(new SceneObject(cube1, glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f), glm::vec3(1.0f), dirtTexture));

    Cube* JosephCube = new Cube();
	scene->addObject(new SceneObject(cube1, glm::vec3(0.0f, 2.0f, 0.0f),
        glm::vec3(0.0f), glm::vec3(1.0f), JosephTexture));

   /* ModelMesh* testObj = new ModelMesh("models/basicObj.obj", 0, 28, glm::vec3(0.3f, 0.3f, 0.9f));
    scene->addObject(new SceneObject(testObj, glm::vec3(3.0f, -1.0f, 0.0f),
        glm::vec3(0.0f), glm::vec3(1.0f), dirtTexture));

    ModelMesh* josephObj = new ModelMesh("models/basicObj.obj", 0, 28, glm::vec3(0.3f, 0.3f, 0.9f));
    scene->addObject(new SceneObject(testObj, glm::vec3(-3.0f, -1.0f, 0.0f),
        glm::vec3(0.0f), glm::vec3(1.0f), JosephTexture));*/

    std::cout << "\n=== MODELE ZAŁADOWANE ===" << std::endl;
    std::cout << "Naciśnij '8' aby wyświetlić info o modelach" << std::endl;
}

void Application::handleInput(float dt) {
    // Ruch kamery
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) camera.processKeyboard('W', dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) camera.processKeyboard('S', dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) camera.processKeyboard('A', dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) camera.processKeyboard('D', dt);
}

void Application::displayLightingInfo() {
    std::cout << "\n=== STEROWANIE OSWIETLENIEM ===" << std::endl;
    std::cout << "1 - Wlacz/Wylacz Ambient (otoczenie)" << std::endl;
    std::cout << "2 - Wlacz/Wylacz Diffuse (rozproszone)" << std::endl;
    std::cout << "3 - Wlacz/Wylacz Specular (odblyski)" << std::endl;
    std::cout << "Q/E - Zwieksz/Zmniejsz Ambient" << std::endl;
    std::cout << "R/F - Zwieksz/Zmniejsz Specular" << std::endl;
    std::cout << "4 - Biale swiatlo" << std::endl;
    std::cout << "5 - Czerwone swiatlo" << std::endl;
    std::cout << "6 - Zielone swiatlo" << std::endl;
    std::cout << "7 - Niebieskie swiatlo" << std::endl;
    std::cout << "8 - Informacje o scenie" << std::endl;
    std::cout << "================================\n" << std::endl;
}

void Application::run() {
    bool running = true;
    sf::Clock clock;
    sf::Clock fpsClockForTitle;
    int frameCount = 0;

    while (running) {
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asMicroseconds();

        frameCount++;
        if (fpsClockForTitle.getElapsedTime().asSeconds() >= 1.0f) {
            window.setTitle("OpenGL 3D - FPS: " + std::to_string(frameCount) +
                " | Ambient: " + (lighting->useAmbient ? "ON" : "OFF") +
                " | Diffuse: " + (lighting->useDiffuse ? "ON" : "OFF") +
                " | Specular: " + (lighting->useSpecular ? "ON" : "OFF"));
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

                if (event.key.code == sf::Keyboard::Num1) {
                    lighting->toggleAmbient();
                    std::cout << "Ambient: " << (lighting->useAmbient ? "ON" : "OFF") << std::endl;
                }
                if (event.key.code == sf::Keyboard::Num2) {
                    lighting->toggleDiffuse();
                    std::cout << "Diffuse: " << (lighting->useDiffuse ? "ON" : "OFF") << std::endl;
                }
                if (event.key.code == sf::Keyboard::Num3) {
                    lighting->toggleSpecular();
                    std::cout << "Specular: " << (lighting->useSpecular ? "ON" : "OFF") << std::endl;
                }
                if (event.key.code == sf::Keyboard::Num8) {
                    std::cout << "\n=== INFORMACJE O SCENIE ===" << std::endl;
                    std::cout << "Liczba obiektów: " << scene->getObjects().size() << std::endl;
                    for (size_t i = 0; i < scene->getObjects().size(); i++) {
                        auto obj = scene->getObject(i);
                        std::cout << "Obiekt " << i << ": Pozycja("
                            << obj->position.x << ", "
                            << obj->position.y << ", "
                            << obj->position.z << ")" << std::endl;
                    }
                }
                if (event.key.code == sf::Keyboard::Q) {
                    lighting->increaseAmbient();
                    std::cout << "Ambient strength: " << lighting->ambientStrength << std::endl;
                }
                if (event.key.code == sf::Keyboard::E) {
                    lighting->decreaseAmbient();
                    std::cout << "Ambient strength: " << lighting->ambientStrength << std::endl;
                }
                if (event.key.code == sf::Keyboard::R) {
                    lighting->increaseSpecular();
                    std::cout << "Specular strength: " << lighting->specularStrength << std::endl;
                }
                if (event.key.code == sf::Keyboard::F) {
                    lighting->decreaseSpecular();
                    std::cout << "Specular strength: " << lighting->specularStrength << std::endl;
                }

                if (event.key.code == sf::Keyboard::Num4) {
                    lighting->changeLightColor(glm::vec3(1.0f, 1.0f, 1.0f));
                    std::cout << "Kolor swiatla: BIALY" << std::endl;
                }
                if (event.key.code == sf::Keyboard::Num5) {
                    lighting->changeLightColor(glm::vec3(1.0f, 0.0f, 0.0f));
                    std::cout << "Kolor swiatla: CZERWONY" << std::endl;
                }
                if (event.key.code == sf::Keyboard::Num6) {
                    lighting->changeLightColor(glm::vec3(0.0f, 1.0f, 0.0f));
                    std::cout << "Kolor swiatla: ZIELONY" << std::endl;
                }
                if (event.key.code == sf::Keyboard::Num7) {
                    lighting->changeLightColor(glm::vec3(0.0f, 0.0f, 1.0f));
                    std::cout << "Kolor swiatla: NIEBIESKI" << std::endl;
                }
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

        handleInput(dt);

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->use();
        shader->setVec3("lightPos", lighting->lightPos.x, lighting->lightPos.y, lighting->lightPos.z);
        shader->setVec3("viewPos", camera.Position.x, camera.Position.y, camera.Position.z);
        shader->setVec3("lightColor", lighting->lightColor.x, lighting->lightColor.y, lighting->lightColor.z);
        shader->setInt("useAmbient", lighting->useAmbient);
        shader->setInt("useDiffuse", lighting->useDiffuse);
        shader->setInt("useSpecular", lighting->useSpecular);
        shader->setFloat("ambientStrength", lighting->ambientStrength);
        shader->setFloat("specularStrength", lighting->specularStrength);
        shader->setInt("shininess", lighting->shininess);

        renderer->render(*shader, *scene, camera, clock.getElapsedTime().asSeconds());

        window.display();
    }
}