#pragma once
#include "common.h"
typedef struct
{
	glm::vec4 vPos; //Posición Vértice XYZW
	glm::vec4 vColor; //Color RGBA
	glm::vec4 vNorm; //Vector normal por vértice
	glm::vec2 vTextCoords; //Coordenadas de textura por vértice
	glm::vec4 vTan; //Tangente por vértice (para normal mapping)
}vertex_t;