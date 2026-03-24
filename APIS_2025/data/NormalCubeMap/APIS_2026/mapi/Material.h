#pragma once
#include "Program.h"
#include "GLTexture.h"

class Material
{

public:

    //propiedades de dibujado
    Program* renderProgram=nullptr;
    //GLTexture* textureColor = nullptr;
    //GLTexture* textureNormal = nullptr;
    map<string, GLTexture*> textureList;


    int shininess=1;
    bool reflection = false;
    bool refraction = false;
    float refractionIndex = 1.0f;
    bool lightEnable = true;


    Material();

};

