#version 330

uniform mat4 MVP;
uniform mat4 M;
uniform mat4 N;

layout(location = 0) in vec4 vPos;
layout(location = 1) in vec4 vColor;
layout(location = 2) in vec4 vNorm;
layout(location = 3) in vec2 vTextCoords;

out vec4 fPos;
out vec4 fColor;
out vec4 fNorm;
out vec2 fTextCoords;


void main() {
    gl_Position = MVP * vPos;
    fPos = M * vPos;
    fColor = vColor;
    fNorm = N * vNorm;
    fTextCoords = vTextCoords;
}