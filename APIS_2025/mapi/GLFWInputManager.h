#pragma once
#include "InputManager.h"
#include <GLFW/glfw3.h>

class GLFWInputManager : public InputManager {
private:
    GLFWwindow* window;
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mousePositionCallback(GLFWwindow* window, double x, double y);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

public:
    // Constructor
    GLFWInputManager(GLFWwindow* window);

    // Destructor
    ~GLFWInputManager() override;

    // Métodos
    void init() override;
};
