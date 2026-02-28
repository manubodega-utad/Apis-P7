#include "CameraKeyboard.h"

// Constructor
CameraKeyboard::CameraKeyboard(projectionType_e type, glm::vec3 position, glm::vec3 up, glm::vec3 lookAt, float speed)
    : Camera(type, position, up, lookAt), speed(speed) {
    direction = glm::normalize(lookAt - position);
}

// Método para actualizar la posición de la cámara
void CameraKeyboard::step(float deltaTime) {
    InputManager* input = System::inputManager;
    glm::vec4 pos = getPosition();
    glm::vec4 rot = getRotation();

    float velocity = speed * deltaTime;
    float velocityRot = 1.0f * deltaTime;

    if (input->isPressed(GLFW_KEY_UP)) {
        // std::cout << "[DEBUG] Avanzando" << std::endl;
        pos.z += velocity;
    }
    if (input->isPressed(GLFW_KEY_DOWN)) {
        // std::cout << "[DEBUG] Retrocediendo" << std::endl;
        pos.z -= velocity;
    }

    // Movimiento lateral
    if (input->isPressed(GLFW_KEY_RIGHT)) {
        // std::cout << "[DEBUG] Moviendo a la derecha" << std::endl;
        pos.x += velocity;
    }
    if (input->isPressed(GLFW_KEY_LEFT)) {
        // std::cout << "[DEBUG] Moviendo a la izquierda" << std::endl;
        pos.x -= velocity;
    }

    // Rotación
    if (input->isPressed(GLFW_KEY_R)) {
        rot.y += velocityRot;
    }
    if (input->isPressed(GLFW_KEY_T)) {
        rot.y -= velocityRot;
    }

    // pos.w = 1.0f;
    setPosition(pos);
    setRotation(rot);
    computeModelMatrix();
    lookAt = glm::vec3(getModel() * glm::vec4(lookAtRel, 1.0f));
    computeViewMatrix();
}
