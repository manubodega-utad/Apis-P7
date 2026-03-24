#pragma once
#include "mapi/common.h"


typedef struct {
    glm::vec4 vPosition; //posicion vertice XYZW
    glm::vec4 vColor; //color RGBA
    glm::vec4 vNormal;
    glm::vec4 vTan;//tangente

    glm::vec2 vTexCoord; //coordenadas de textura por vértice
}vertex_t;
