#pragma once
#include "mapi/common.h"

using namespace std;
class Shader
{

public:
    bool compiled = false;
    unsigned int shaderId; //identificador openGL
    unsigned int shaderType; //vertex/fragment

    Shader(string fileName); //archivo a compilar
};

