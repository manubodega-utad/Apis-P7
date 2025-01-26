#include "Factory.h"

// Inicializar backend por defecto
GraphicsBackend Factory::selectedGraphicsBackend = GraphicsBackend::GL1;
InputBackend Factory::selectedInputBackend = InputBackend::GLFW;

// Getters
GraphicsBackend Factory::getSelectedGraphicsBackend() {
    return selectedGraphicsBackend;
}

InputBackend Factory::getSelectedInputBackend() {
    return selectedInputBackend;
}

//Setters
void Factory::setSelectedInputBackend(InputBackend backend) {
    selectedInputBackend = backend;
}

void Factory::setSelectedGraphicsBackend(GraphicsBackend backend) {
    selectedGraphicsBackend = backend;
}

// Metodos
Render* Factory::getNewRender(int width, int height) {
    if (selectedGraphicsBackend == GraphicsBackend::GL1) {
        return new GL1Render(width, height);
    }
    if (selectedGraphicsBackend == GraphicsBackend::GL4) {
        return new GL4Render(width, height);
    }
    return nullptr;
}

InputManager* Factory::getNewInputManager(GLFWwindow* window) {
    if (selectedInputBackend == InputBackend::GLFW) {
        return new GLFWInputManager(window);
    }

    return nullptr;
}

Material* Factory::getNewMaterial() {
    if (selectedGraphicsBackend == GraphicsBackend::GL4) {
        return new GLSLMaterial();
    }
    return nullptr;
}

bool Factory::isClosed(GLFWwindow* window) {
    if (!window) return true;
    return glfwWindowShouldClose(window);
}
