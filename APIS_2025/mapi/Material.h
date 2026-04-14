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
    BlendMode blendMode = BlendMode::NONE;
    bool lighting = true;
    bool culling = false;
    bool depthWrite = true;

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
        return textures.count(name) ? textures[name] : nullptr; }
    }
    int  getShininess() const { 
        return shininess; 
    }
    BlendMode getBlendMode() const { 
        return blendMode; 
    }
    bool getLighting() const { 
        return lighting; 
    }
    bool getCulling() const { 
        return culling; 
    }
    bool getDepthWrite() const { 
        return depthWrite; 
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
    void setBlendMode(BlendMode mode) { 
        blendMode = mode; 
    }
    void setLighting(bool enable) { 
        lighting = enable; 
    }
    void setCulling(bool enable) { 
        culling = enable; 
    }
    void setDepthWrite(bool enable) {
        depthWrite = enable; 
    }


    // Métodos
    virtual void loadPrograms(vector<string>& files) = 0;
    virtual void prepare() = 0;
};
