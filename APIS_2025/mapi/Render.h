#pragma once
#pragma once
#include <vector>
#include "Object.h"

class Render {
protected:
    int width;
    int height;

public:
    // Constructor y destructor
    Render() : width(1600), height(1200) {}
    virtual ~Render() = default;

    // Getters
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;

    // Setters
    virtual void setWidth(int newWidth) = 0;
    virtual void setHeight(int newHeight) = 0;

    //Metodos virtuales
    virtual void init() = 0;
    virtual void setupObject(Object* obj) = 0;
    virtual void removeObject(Object* obj) = 0;
    virtual void drawObjects(const std::vector<Object*>* objs) = 0;
    virtual bool isClosed() const = 0;
};