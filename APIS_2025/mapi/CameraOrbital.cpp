#include "CameraOrbital.h"
#include "System.h"

CamaraOrbital::CamaraOrbital(projectionType_e type, glm::vec3 position, glm::vec3 up, glm::vec3 lookAt, glm::vec4 center, float radio, float speed)
    : Camera(type, position, up, lookAt), center(center), radio(radio), speed(speed)
{
}

void CamaraOrbital::step(float deltaTime) {
    // Calculamos el ángulo
    float angle = static_cast<float>(deltaTime * speed);
    float theta = std::atan2(pos.z - center.z, pos.x - center.x);

    // Sumamos el movimiento
    theta += angle;

    // Actualizamos posición orbital
    pos.x = center.x + radio * cos(theta);
    pos.z = center.z + radio * sin(theta);

    // Recalcular matrices
    computeModelMatrix();
    computeViewMatrix();      
}

void CamaraOrbital::computeViewMatrix()
{
    this->view = glm::lookAt(glm::vec3(pos), lookAt, up);
}
