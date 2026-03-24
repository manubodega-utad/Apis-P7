#pragma once
#include "common.h"
using namespace std;
using namespace glm;
class Light
{

public:


    glm::vec4  pos;
    glm::vec4  rot;

    float intensity=1.0f;
    vec3 color = {0,0,0};
    Light() {};
    Light(glm::vec4  pos,  glm::vec4  rot, glm::vec3 color):pos(pos),rot(rot),color(color) { };
};

