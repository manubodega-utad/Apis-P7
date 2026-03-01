#pragma once
#include "Camera.h"
#include <glm/glm.hpp>

class CamaraOrbital : public Camera {
private:
    glm::vec4 center;
    float radio;
    float speed;

public:
    // Constructor
    CamaraOrbital(projectionType_e type, glm::vec3 position, glm::vec3 up, glm::vec3 lookAt, glm::vec4 center, float radio, float speed);

    // Métodos
    virtual void step(float deltaTime) override;
    void computeViewMatrix();
};