#version 330
uniform mat4 MVP;
uniform mat4 M;
struct Material {
    bool useColorText;
    bool usetextureNormal;
    bool reflection;
    bool refraction;
    float refractionIndex;
    int shininess;
    int textureType;
    bool computeLight;
};

uniform Material mat;
uniform vec3 camPos;


attribute vec4 vPos; //buffer object para datos de posicion
attribute vec4 vColor;
attribute vec4 vNormal;
attribute vec4 vTan; //datos de tangente
attribute vec2 vTexCoord;


out vec4 fColor; //datos de salida extra para el siguiente shader
out vec2 fTexCoord;
out vec4 fNormal;
out vec4 fPos;
out vec3 fTexCube; //coordenada de textura cubica
out mat3 TBN;//matriz tangente bitangente normal para uso de normalMap

void main() {
    gl_Position = MVP * vPos; //calculo de posicion de vertice
    fColor = vColor; //pasamos el color al siguiente shader
    fTexCoord = vTexCoord;
    mat4 Normal = inverse(transpose(M));
    fNormal = normalize(Normal*vNormal);
    fPos = M*vPos; //mandamos el fragmento movido según indique Model
    fTexCube = (fPos.xyz);


    if (mat.reflection)
    {
        vec3 I = normalize(fPos.xyz - camPos.xyz);
        fTexCube = reflect(I, fNormal.xyz);
    }

    if (mat.refraction)
    {
        vec3 I = normalize(fPos.xyz - camPos.xyz);
        fTexCube = refract(I, fNormal.xyz, 1 / mat.refractionIndex);
    }

    //mat4 Normal = inverse(transpose(M));
    vec3 tan = normalize(Normal*vTan).xyz;
    vec3 bitan = cross(tan.xyz, fNormal.xyz);
    TBN = transpose(mat3(tan, bitan, fNormal.xyz));



}


