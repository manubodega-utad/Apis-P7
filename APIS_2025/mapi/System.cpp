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
    Factory::setSelectedGraphicsBackend(GraphicsBackend::GL1);
    Factory::setSelectedInputBackend(InputBackend::GLFW);

    // Crear los objetos
    render = Factory::getNewRender(800, 600);
    GLFWwindow* window = nullptr;
    if (auto* glRender = dynamic_cast<GL1Render*>(render)) {
        window = glRender->getWindow();
    }
    inputManager = Factory::getNewInputManager(window);

    // Inicializar sistemas
    render->init();
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

    // Preparar los objetos para el renderizado
    for (Object* obj : world->getObjects()) {
        render->setupObject(obj);
    }

    // Bucle principal
    auto lastTime = std::chrono::high_resolution_clock::now();
    while (!end) {
        // Calcular deltaTime
        auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - lastTime).count();
        lastTime = currentTime;

        // Actualizar el mundo
        world->update(deltaTime);
        std::vector<Object*> objectVector(world->getObjects().begin(), world->getObjects().end());

        // Dibujar los objetos
        render->drawObjects(&objectVector);

        if (Factory::isClosed(dynamic_cast<GL1Render*>(render)->getWindow())) {
            exit();
        }
    }

    // Limpiar recursos
    delete render;
    delete inputManager;
    delete world;
}
