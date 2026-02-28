#pragma once
#include "Camera.h"

class CameraFPS : public Camera {
private:
    float speed;
    float sensitivity;
    float yaw, pitch;
    glm::vec3 front;

    void updateCameraVectors();

public:
    CameraFPS(projectionType_e type, glm::vec3 position, glm::vec3 up, glm::vec3 lookAt, float speed = 5.0f, float sensitivity = 0.01f);
    virtual void step(float deltaTime) override;
};
