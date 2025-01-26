#pragma once

#include "Render.h"
#include <GLFW/glfw3.h>
#include <vector>
#include "Object.h"

class GL1Render : public Render {
private:
    GLFWwindow* window;

public:
    // Constructor
    GL1Render(int width, int height);

    // Destructor
    ~GL1Render() override;

    // Getters 
    int getWidth() const override;
    int getHeight() const override;
    GLFWwindow* getWindow() const;

    // Setters
    void setWidth(int newWidth) override;
    void setHeight(int newHeight) override;

    // Métodos
    void init() override;
    void setupObject(Object* obj) override;
    void removeObject(Object* obj) override;
    void drawObjects(const vector<Object*>* objs) override;
    bool isClosed() const override;
};
