#pragma once
#include "Render.h"
#include "InputManager.h"
#include "Factory.h"
#include "World.h"
#include <chrono>

class System {
protected:
    
    
    static bool end;
    static World* world;
    static glm::mat4 ModelMatrix;

public:
    static Render* render;
    static InputManager* inputManager;
    // Getters
    static World* getWorld();
    static const glm::mat4& getModelMatrix();

    // Setters
    static void setWorld(World* newWorld);
    static void setModelMatrix(const glm::mat4& modelMatrix);

    // Métodos estáticos
    static void initSystem();
    static void addObject(Object* obj);
    static void exit();
    static void mainLoop();
};
