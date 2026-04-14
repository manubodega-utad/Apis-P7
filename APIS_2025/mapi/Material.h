#pragma once
#include <vector>
#include <string>
#include <map>
#include "RenderProgram.h"

using namespace std;

class Material {
protected:
    RenderProgram* program;
    std::map<std::string, Texture*> textures;
    glm::vec4 colorRGBA;
    int shininess = 1;
    BlendMode blendMode = BlendMode::NONE;
    bool lighting = true;
    bool culling = false;
    bool depthWrite = true;
    bool reflection = false;
    bool refraction = false;
    float refractionCoef = 1.0f;

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
    virtual std::map<std::string, Texture*>& getColorTextures() {
        return textures;
    }
    virtual Texture* getColorTexture(std::string name) { 
        return textures.count(name) ? textures[name] : nullptr;
    }
    glm::vec4 getColorRGBA() const { 
        return colorRGBA; 
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
    bool getReflection() const {
        return reflection;
    }
    bool getRefraction() const {
        return refraction;
    }
    float getRefractionCoef() const {
        return refractionCoef;
    }

    // Setters
    virtual void setColorTexture(std::string name, Texture* t) { 
        textures[name] = t; 
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
    void setReflection(bool r) { 
        reflection = r; 
    }
    void setRefraction(bool r) { 
        refraction = r; 
    }
    void setRefractionCoef(float f) { 
        refractionCoef = f; 
    }


    // Métodos
    virtual void loadPrograms(vector<string>& files) = 0;
    virtual void prepare() = 0;
};
