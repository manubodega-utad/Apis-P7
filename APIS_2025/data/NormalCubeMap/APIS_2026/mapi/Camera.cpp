#include "Camera.h"
#include "GLFWKeyManager.h"

Camera::Camera(vec4 pos, vec4 lookAt, double fovy, double aspectRatio ):
    fovy(fovy), aspectRatio(aspectRatio), lookAt(lookAt),pos(pos)
{
    //calcular matriz proyección
    cameraProjection = perspective(radians(fovy),aspectRatio, 0.01, 1000.0);
    //calcular matriz vista
    this->up = vec4(0, 1, 0, 0);
    cameraView = glm::lookAt(vec3(pos), vec3(lookAt), vec3(up));
    direction = normalize(lookAt - pos);
    lookAtPrime = direction;
    lookAtPrime.w = 1;
}

void Camera::step(float timeStep) {

    //actualizar movimientos
    vec4 strafeDir = normalize(vec4(cross(vec3(this->up), vec3(direction)),0));
    if (GLFWKeyManager::keyboardState[GLFW_KEY_D])
    {
        this->pos -= speed * timeStep * strafeDir;
    }
    if (GLFWKeyManager::keyboardState[GLFW_KEY_A])
    {
        this->pos += speed * timeStep * strafeDir;
    }
    if (GLFWKeyManager::keyboardState[GLFW_KEY_W])
    {
        this->pos += speed * timeStep * direction;
    }
    if (GLFWKeyManager::keyboardState[GLFW_KEY_S])
    {
        this->pos -= speed * timeStep * direction;
    }

    if (GLFWKeyManager::keyboardState[GLFW_KEY_LEFT])
    {
        this->rot.y += this->rotSpeed * timeStep;
    }
    if (GLFWKeyManager::keyboardState[GLFW_KEY_RIGHT])
    {
        this->rot.y -= rotSpeed * timeStep;
    }
    if (GLFWKeyManager::keyboardState[GLFW_KEY_UP])
    {
        this->rot.x += rotSpeed * timeStep;
    }
    if (GLFWKeyManager::keyboardState[GLFW_KEY_DOWN])
    {
        this->rot.x -= rotSpeed * timeStep;
    }

    //conseguir lookAt en reposo, pos=(0,0,0)
    
    mat4 rotMatrix = glm::rotate(mat4(1), glm::radians(rot.y), vec3(0, 1, 0));
    rotMatrix = glm::rotate(rotMatrix, glm::radians(rot.x), vec3(1, 0, 0));

    lookAt = rotMatrix * lookAtPrime;
    lookAt += pos; lookAt.w = 1;
    direction= vec4(normalize(vec3(lookAt) - vec3(pos)),0);

    cameraView = glm::lookAt(vec3(pos), vec3(lookAt), vec3(0, 1, 0));

}