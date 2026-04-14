#pragma once
#include "RenderProgram.h"
#include <iostream>

using namespace std;

class GLSLProgram : public RenderProgram {
public:
    // Constructor
    GLSLProgram();

    // Destructor
    ~GLSLProgram() override;

    // Setters
    void setInt(const string& name, int val) override;
    void setFloat(const string& name, float val) override;
    void setVec3(const string& name, const glm::vec3& vec) override;
    void setVec4(const string& name, const glm::vec4& vec) override;
    void setMatrix(const string& name, const glm::mat4& mat) override;

    void setCulling(bool culling) override;
    void setDepthWrite(bool depthWrite) override;
    void setBlendMode(BlendMode blendMode) override;

    // Métodos
    void addProgram(string& fileName) override;
    void linkProgram() override;
    void use() override;
    void checkLinkerErrors() override;
    void setColorTextEnable(string name) override;
    void setColorTextDisable(string name) override;
    void bindColorTextureSampler(int binding, Texture* text, string name) override;
   
private:
    // Métodos propios
    void readVarList();
    unsigned int getVarLocation(std::string varName);
};
