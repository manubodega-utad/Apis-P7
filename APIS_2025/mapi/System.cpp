#include "System.h"
#include <iostream>

// Inicialización
Render* System::render = nullptr;
InputManager* System::inputManager = nullptr;
bool System::end = false;
World* System::world = nullptr;
glm::mat4 System::ModelMatrix = glm::mat4(1.0f);

// Getters
World* System::getWorld() {
    return world;
}

const glm::mat4& System::getModelMatrix() {
    return ModelMatrix;
}

// Setters
void System::setWorld(World* newWorld) {
    if (world) {
        delete world;
    }
    world = newWorld;
}

void System::setModelMatrix(const glm::mat4& modelMatrix) {
    ModelMatrix = modelMatrix;
}

// Métodos
void System::initSystem() {
    // Seleccionar los backends
    Factory::setSelectedGraphicsBackend(GraphicsBackend::GL4);
    Factory::setSelectedInputBackend(InputBackend::GLFW);

    // Inicializar Render
    render = Factory::getNewRender(1600, 1200);
    render->init();

    // Validación para obtener ventana
    GLFWwindow* window = nullptr;
    if (auto* glRender = dynamic_cast<GL1Render*>(render)) {
        window = glRender->getWindow();
    }

    // Inicializar inputManager
    inputManager = Factory::getNewInputManager(window);
    inputManager->init();

    // Inicializar mundo
    world = new World();
}

// Añade un objeto al mundo
void System::addObject(Object* obj) {
    if (world) {
        world->addObject(obj);
    }
}

// Termina la ejecución del sistema
void System::exit() {
    end = true;
}

// Bucle principal del sistema
void System::mainLoop() {
    if (!render || !inputManager || !world) {
        std::cerr << "Error: El sistema no está completamente inicializado." << std::endl;
        return;
    }

    // Obtener ventana
    auto* glRender = dynamic_cast<GL1Render*>(render);
    GLFWwindow* window = glRender->getWindow();

    // Preparar los objetos para el renderizado
    for (Object* obj : world->getObjects()) {
        render->setupObject(obj);
    }

    // Bucle principal
    float newTime = static_cast<float>(glfwGetTime());
    float deltaTime = 0;
    float lastTime = newTime;

    while (!end) {
        // Calcular deltaTime
        newTime = static_cast<float>(glfwGetTime());
        deltaTime = newTime - lastTime;
        lastTime = newTime;

        // Actualizar el mundo
        world->update(deltaTime);

        // Dibujar los objetos
        std::vector<Object*> objectList(world->getObjects().begin(), world->getObjects().end());
        render->drawObjects(&objectList);

        glfwSwapBuffers(window);
        glfwPollEvents();

        // Cierre de Ventana
        if (Factory::isClosed(window)) {
            exit();
        }
    }

    // Limpiar recursos
    delete render;

}
