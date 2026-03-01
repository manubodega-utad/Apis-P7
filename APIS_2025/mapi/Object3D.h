#pragma once
#include "Object.h"

class Object3D : public Object {
public:
    // Constructor
    Object3D(string mshFile, glm::vec4 position, glm::vec4 rotation, glm::vec4 scale);

    // Destructor
    virtual ~Object3D();

    // Métodos
    void loadDataFromFile(const std::string& file) override;
    virtual void step(float deltaTime) override;

private:
    bool loadObj(string objFile, Mesh3D* mesh);
    void recomputeNormals();
};