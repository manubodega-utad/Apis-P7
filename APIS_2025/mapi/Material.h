#pragma once
#include <vector>
#include <string>
#include "RenderProgram.h"

using namespace std;


class Material {
protected:
    RenderProgram* program;
    Texture* colorText;
    glm::vec4 colorRGBA;
    int shininess = 1;

public:
    // Constructor
    Material() : program(nullptr) {}

    // Destructor
    virtual ~Material() {
        if (program) {
            delete program;
            program = nullptr;
        }
    }

    // Getters
    RenderProgram* getProgram() const 
    {
        return program; 
    }
    Texture* getColorText() const { 
        return colorText; 
    }
    glm::vec4 getColorRGBA() const {
        return colorRGBA;
    }
    int  getShininess() const { 
        return shininess; 
    }

    // Setters
    void setColorText(Texture* texture) {
        colorText = texture;
    }
    void setColorRGBA(const glm::vec4& color) {
        colorRGBA = color;
    }
    void setShininess(int s) { 
        shininess = s; 
    }


    // Métodos
    virtual void loadPrograms(vector<string>& files) = 0;
    virtual void prepare() = 0;
};
