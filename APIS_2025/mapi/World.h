#pragma once

#include <list>
#include <stdexcept>
#include "Object.h"
#include "Camera.h"
#include "Light.h"

class World {
private:
    std::list<Object*> objects;
    std::list<Camera*> cameras;
    int activeCamera;
    std::list<Light*> lights;
    float ambient;

public:
    // Constructor
    World();

    // Objects
    size_t getNumObjects() const;
    Object* getObject(size_t index) const;
    std::list<Object*>& getObjects();
    void addObject(Object* obj);
    void removeObject(Object* obj);

    // Cameras
    size_t getNumCameras() const;
    Camera* getActiveCamera() const;
    void addCamera(Camera* cam);
    void removeCamera(Camera* cam);
    void setActiveCamera(int index);

    // P5 - Ambient
    float getAmbient() const;
    void setAmbient(float a);

    // P5 - Lights
    std::list<Light*>& getLights();
    Light* getLight(int pos);
    void addLight(Light* light);
    void deleteLight(int lightPos);

    // Update
    void update(float deltaTime);
};