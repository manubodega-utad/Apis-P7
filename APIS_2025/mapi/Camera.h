#pragma once
#include "common.h"
#include "Entity.h"

enum class projectionType_e { ORTHOGRAPHIC, PERSPECTIVE };

class Camera : public Entity {
protected:
    // Constantes camara perspectiva
    static constexpr float FOVY = glm::radians(45.0f); // Ángulo de apertura
    static constexpr float ASPECT_RATIO = 4.0f / 3.0f; // Realicion de aspecto 4/3
    static constexpr float NEAR_PLANE = 0.01f; // Plano cercano
    static constexpr float FAR_PLANE = 1000.0f; // Plano lejano

    // Constantes camara ortográfica
    static constexpr float ORTHO_LEFT = -10.0f;
    static constexpr float ORTHO_RIGHT = 10.0f;
    static constexpr float ORTHO_BOTTOM = -10.0f;
    static constexpr float ORTHO_TOP = 10.0f;

    glm::mat4 view;
    glm::mat4 projection;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 front;
    glm::vec3 lookAt;
    glm::vec3 lookAtRel;
    projectionType_e type;

public:
    // Constructor
    Camera(projectionType_e type, glm::vec3 position, glm::vec3 up, glm::vec3 lookAt);

    // Getters
    glm::mat4 getProjection() const;
    glm::mat4 getView() const;

    // Métodos
    void computeProjectionMatrix();
    void computeViewMatrix();

    // Método virtual
    virtual void step(float deltaTime) = 0;
};

