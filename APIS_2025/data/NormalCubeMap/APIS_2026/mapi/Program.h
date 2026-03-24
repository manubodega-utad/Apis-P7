#pragma once
#include "mapi/common.h"
#include "Shader.h"
#include "Light.h"
#include "Camera.h"
using namespace std;

class Program
{
private:
    vector<string> shaderList;//lista de archivos de codigo GLSL shader
    unsigned int programId; //identificador OpenGl de programa GLSL
    map<string, unsigned int> varList; //Lista de variables en programa
    bool linked = false;
public:
    Program() { programId = -1; };
    void addShader(string fileName) { shaderList.push_back(fileName); };
    void linkProgram();
    void readVarList();
    void activate() { glUseProgram(programId); };
    //set datos de atributos
    void setAttributeMetaData(string attribName, GLint size, GLenum type, GLboolean
        normalized, GLsizei stride, const GLvoid* pointer);
    //set datos de uniform
    void setMVP(glm::mat4 m);
    void setM(glm::mat4 m);
    void resetTextureData();
    void setTextureData(int textureUnit, int textureId, GLenum textureType,string name, bool isNormal);
    void setLight(Light& l);
    void setCamera(Camera& c);
    void setShininess(int s);
    void setReflection(bool value);

    void setComputeLight(bool value);

    void setRefraction(bool value, float rIndex);


};

