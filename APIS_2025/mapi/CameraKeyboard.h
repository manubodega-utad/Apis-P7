#pragma once
#include "Camera.h"
#include "System.h"
#include "Entity.h"

class CameraKeyboard : public Camera {
private:
    float speed;
    glm::vec3 direction;

public:
    // Constructor
    CameraKeyboard(projectionType_e type, glm::vec3 position, glm::vec3 up, glm::vec3 lookAt, float speed = 5.0f);

    // Métodos
    void step(float deltaTime) override;

};
