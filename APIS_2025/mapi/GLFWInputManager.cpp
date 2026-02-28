#include "GLFWInputManager.h"
#include <iostream>

using namespace std;

GLFWInputManager::GLFWInputManager(GLFWwindow* wnd)
    : window(wnd)
{
}

GLFWInputManager::~GLFWInputManager() {
}

void GLFWInputManager::init() {
    glfwSetWindowUserPointer(window, this);  // Asignar instancia a la ventana
    glfwSetKeyCallback(window, keyCallback);

    glfwSetCursorPosCallback(window, mousePositionCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
}

void GLFWInputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    GLFWInputManager* inputManager = static_cast<GLFWInputManager*>(glfwGetWindowUserPointer(window));
    switch (action) {
    case GLFW_PRESS:
    {
        inputManager->keyState[key] = true;
    }break;

    case GLFW_RELEASE:
    {
        inputManager->keyState[key] = false;
    }break;
    }
}

void GLFWInputManager::mousePositionCallback(GLFWwindow* wnd, double xpos, double ypos) {
    InputManager::mouseState.x = xpos;
    InputManager::mouseState.y = ypos;
}

void GLFWInputManager::mouseButtonCallback(GLFWwindow* wnd, int button, int action, int mods) {
    if (action == GLFW_PRESS)
        InputManager::mouseState.button[button] = true;
    else if (action == GLFW_RELEASE)
        InputManager::mouseState.button[button] = false;
}
