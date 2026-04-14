#version 330
uniform mat4 MVP;
uniform mat4 M;
uniform mat4 N;
uniform mat4 depthBias;

struct Material {
    vec4 color;
    bool useColorText;
    bool usetextureNormal;
    bool reflection;
    bool refraction;
    bool computeShadows;
    float refractionIndex;
    int shininess;
    int textureType;
    bool computeLight;
};

uniform Material mat;
uniform vec3 camPos;


layout(location = 0) in vec4 vPos;
layout(location = 1) in vec4 vColor;
layout(location = 2) in vec4 vNorm;
layout(location = 3) in vec2 vTextCoords;
layout(location = 4) in vec4 vTan;


out vec4 fPos;
out vec4 fColor;
out vec4 fNorm;
out vec2 fTextCoords;
out vec3 fTexCube;
out mat3 TBN;
out vec4 fDepthCoord;



void main() {
    gl_Position = MVP * vPos;
    fPos = M * vPos;
    fColor = vColor;
    fNorm = normalize(N * vNorm);
    fTextCoords = vTextCoords;
    fTexCube = (fPos.xyz);

    if (mat.reflection)
    {
        vec3 I = normalize(fPos.xyz - camPos.xyz);
        fTexCube = reflect(I, fNorm.xyz);
    }

    if (mat.refraction)
    {
        vec3 I = normalize(fPos.xyz - camPos.xyz);
        fTexCube = refract(I, fNorm.xyz, 1 / mat.refractionIndex);
    }

    vec3 tan = normalize(N * vTan).xyz;
    vec3 bitan = cross(tan.xyz, fNorm.xyz);
    TBN = transpose(mat3(tan, bitan, fNorm.xyz));

    fDepthCoord = depthBias * vPos;
}
