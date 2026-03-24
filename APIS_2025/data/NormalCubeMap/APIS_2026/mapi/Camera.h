#pragma once
#include "common.h"

class Camera
{
public:
    glm::vec4  pos;
    glm::vec4  rot = { 0,0,0,0 };
    glm::vec4 lookAt;
    glm::vec4 lookAtPrime;//look at original, usado en el constructor
    glm::vec4 up;
    
    glm::vec4 direction;
    float speed = 0.5; //movimiento
    float rotSpeed = 40.0f; //rotacion


    double fovy=90.0; //angulo de apertura en grados
    double aspectRatio=4.0/3.0; //4:3



    glm::mat4 cameraModel = glm::mat4(1);

    glm::mat4 cameraView = glm::mat4(1);
    glm::mat4 cameraProjection= glm::mat4(1);

    Camera() {};
    
    Camera(glm::vec4  pos, glm::vec4  lookAt, double fovy=45.0f, double aspectRatio=4.0/3.0 );

    void step(float timeStep);

};

