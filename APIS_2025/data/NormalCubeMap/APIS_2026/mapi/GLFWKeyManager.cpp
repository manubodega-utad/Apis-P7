#include "GLFWKeyManager.h"

void GLFWKeyManager::initKeyManager(GLFWwindow* window)
{

    glfwSetKeyCallback(window, GLFWKeyManager::windowKeyboardEvent);//init de funcion de teclado
    glfwSetMouseButtonCallback(window, GLFWKeyManager::mouseButtonEvent);//init de funcion boton raton
    glfwSetCursorPosCallback(window, GLFWKeyManager::mousePosEvent);//init posicion de raton
    GLFWKeyManager::window = window;
    setKMCursorPos(0, 0);
}


void GLFWKeyManager::setKMCursorPos(double x, double y) {
    mouseState.xPos = x; mouseState.yPos = y;
    glfwSetCursorPos(window, x, y);


}

void GLFWKeyManager::windowKeyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch (action) {
        case GLFW_PRESS:
        {
            keyboardState[key] = true;
        }break;
        case GLFW_RELEASE:
        {
            keyboardState[key] = false;
        }break;
    }
}

void GLFWKeyManager::mousePosEvent(GLFWwindow* window, double xpos, double ypos)
{
    mouseState.xPos = xpos;
    mouseState.yPos = ypos;

}

void GLFWKeyManager::mouseButtonEvent(GLFWwindow* window, int button, int action, int mods)
{
    switch (action) {
    case GLFW_PRESS:
    {
        mouseState.buttonState[button] = true;
    }break;
    case GLFW_RELEASE:
    {
        mouseState.buttonState[button] = false;
    }break;
    }
}

void GLFWKeyManager::updateEvents()
{
    glfwPollEvents();
}
