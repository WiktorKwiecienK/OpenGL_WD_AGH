#include "Camera.h"

Camera::Camera(glm::vec3 startPos)
    : Position(startPos), Front(0.0f, 0.0f, -1.0f), Up(0.0f, 1.0f, 0.0f),
    Yaw(-90.0f), Pitch(0.0f), Speed(0.000002f), Sensitivity(0.1f) {
}
glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::processKeyboard(char key, float deltaTime) {

    float velocity = Speed * deltaTime;

    if (key == 'W') Position += velocity * Front;
    if (key == 'S') Position -= velocity * Front;
    if (key == 'A') Position -= glm::normalize(glm::cross(Front, Up)) * velocity;
    if (key == 'D') Position += glm::normalize(glm::cross(Front, Up)) * velocity;
}

void Camera::processMouse(float xOffset, float yOffset) {
    xOffset *= Sensitivity;
    yOffset *= Sensitivity;

    Yaw += xOffset;
    Pitch += yOffset;

     if (Pitch > 179.0f) Pitch = 179.0f;
     if (Pitch < -179.0f) Pitch = -179.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

    Front = glm::normalize(front);
}