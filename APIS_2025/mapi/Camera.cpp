#include "Camera.h"

// Constructor
Camera::Camera(projectionType_e type, glm::vec3 position, glm::vec3 up, glm::vec3 lookAt)
    : Entity(), type(type), up(up), lookAt(lookAt) {

    setPosition(glm::vec4(position, 1.0f));
    setRotation(glm::vec4(0, 0, 0, 0));

    lookAtRel = lookAt - position;
    computeProjectionMatrix();
    computeViewMatrix();
}

// Getters
glm::mat4 Camera::getProjection() const {
    return projection;
}

glm::mat4 Camera::getView() const {
    return view;
}

// Métodos
void Camera::computeProjectionMatrix() {
    if (type == projectionType_e::PERSPECTIVE) {
        projection = glm::perspective(FOVY, ASPECT_RATIO, NEAR_PLANE, FAR_PLANE);
    }
    else {
        projection = glm::ortho(ORTHO_LEFT, ORTHO_RIGHT, ORTHO_BOTTOM, ORTHO_TOP,
            NEAR_PLANE, FAR_PLANE
        );
    }
}

void Camera::computeViewMatrix() {
    view = glm::lookAt(glm::vec3(getPosition()), lookAt, up);
}