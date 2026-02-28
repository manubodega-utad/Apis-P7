#include "CameraFPS.h"
#include "System.h"

CameraFPS::CameraFPS(projectionType_e type, glm::vec3 position, glm::vec3 up, glm::vec3 lookAt, float speed, float sensitivity)
    : Camera(type, position, up, lookAt), speed(speed), sensitivity(sensitivity) {

    front = glm::normalize(lookAt - position);
    yaw = -90.0f;
    pitch = 0.0f;
    updateCameraVectors();
}

void CameraFPS::updateCameraVectors() {
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);
    lookAt = glm::vec3(getPosition()) + front;
}

void CameraFPS::step(float deltaTime) {
    InputManager* input = System::inputManager;
    glm::vec3 pos = glm::vec3(getPosition());
    glm::vec3 right = glm::normalize(glm::cross(front, up));
    float dt = static_cast<float>(deltaTime);
    float velocity = speed * dt;

    // Movimiento WSAD
    if (input->isPressed(GLFW_KEY_W)) pos += front * velocity;
    if (input->isPressed(GLFW_KEY_S)) pos -= front * velocity;
    if (input->isPressed(GLFW_KEY_D)) pos += right * velocity;
    if (input->isPressed(GLFW_KEY_A)) pos -= right * velocity;

    setPosition(glm::vec4(pos, 1.0f));

    // Movimiento del ratón
    double mouseX = input->getMouseX();
    double mouseY = input->getMouseY();
    static bool firstFrame = true;
    static double lastX = 0.0, lastY = 0.0;

    if (firstFrame) {
        lastX = mouseX;
        lastY = mouseY;
        firstFrame = false;
    }

    double offsetX = mouseX - lastX;
    double offsetY = lastY - mouseY;
    lastX = mouseX;
    lastY = mouseY;

    yaw += static_cast<float>(offsetX) * sensitivity;
    pitch += static_cast<float>(offsetY) * sensitivity;

    // Limitar pitch
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    updateCameraVectors();
    computeViewMatrix();

    // Reiniciar ratón al centro
    //glfwSetCursorPos(System::getWindow(), 0.0, 0.0);
}
