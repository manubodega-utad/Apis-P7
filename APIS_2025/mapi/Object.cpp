#include "Object.h"


// Constructor
Object::Object() : tipo(ObjectType::Object1) {}

// Destructor
Object::~Object() {}

// Getters
Mesh3D* Object::getMesh() const {
    if (meshes.empty()) return nullptr;
    return meshes[0];   // por compatibilidad con el render actual
}

const std::vector<Mesh3D*>& Object::getMeshes() const {
    return meshes;
}

int Object::getTipo() const {
    return static_cast<int>(tipo);
}

// Setters
void Object::setMesh(Mesh3D* mesh) {
    if (mesh) {
        meshes.push_back(mesh);
    }
}

void Object::setTipo(int newTipo) {
    tipo = static_cast<ObjectType>(newTipo);
}