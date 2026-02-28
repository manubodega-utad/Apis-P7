#include "World.h"

// Constructor
World::World() : activeCamera(0), ambient(0.2f) {}

// Getters
size_t World::getNumObjects() const {
    return objects.size();
}

Object* World::getObject(size_t index) const {
    if (index >= objects.size()) {
        throw std::out_of_range("Índice fuera de rango");
    }

    auto it = objects.begin();
    std::advance(it, index);
    return *it;
}

std::list<Object*>& World::getObjects() {
    return objects;
}

size_t World::getNumCameras() const {
    return cameras.size();
}

Camera* World::getActiveCamera() const {
    if (cameras.empty() || activeCamera < 0 || activeCamera >= cameras.size()) {
        return nullptr;
    }
    auto it = cameras.begin();
    std::advance(it, activeCamera);
    return *it;
}

// Métodos para cámaras
void World::addCamera(Camera* cam) {
    if (cam) {
        cameras.push_back(cam);
    }
}

void World::removeCamera(Camera* cam) {
    cameras.remove(cam);
}

void World::setActiveCamera(int index) {
    if (index >= 0 && index < cameras.size()) {
        activeCamera = index;
    }
}

// Métodos para ambientes
float World::getAmbient() const { 
    return ambient; 
}
void World::setAmbient(float a) { 
    ambient = a; 
}

// Métodos para luces
std::list<Light*>& World::getLights() {
    return lights;
}

Light* World::getLight(int pos) {
    if (pos < 0 || pos >= (int)lights.size()) return nullptr;
    auto it = lights.begin();
    std::advance(it, pos);
    return *it;
}

void World::addLight(Light* light) {
    if (light) lights.push_back(light);
}

void World::deleteLight(int lightPos) {
    if (lightPos < 0 || lightPos >= (int)lights.size()) return;
    auto it = lights.begin();
    std::advance(it, lightPos);
    lights.erase(it);
}

// Métodos
// Añadir un objeto
void World::addObject(Object* obj) {
    if (obj != nullptr) {
        objects.push_back(obj);
    }
}

// Eliminar un objeto
void World::removeObject(Object* obj) {
    objects.remove(obj);
}

// Actualiza el estado del mundo
void World::update(float deltaTime) {
    for (Light* l : lights) {
        if (l) {
            l->step(deltaTime);
        }
    }
    for (Camera* cam : cameras) {
        if (cam) {
            cam->step(deltaTime);
        }
    }
    for (Object* obj : objects) {
        if (obj) {
            obj->step(deltaTime);
        }
    }
}
