#version 330

#define DIRECTIONAL 0
#define POINT 1
#define SPOT 2

struct Light{
    vec4 position;
    vec4 direction;
    vec4 color;
    int type;
    int enable;
    float linearAttenuation;
    float cutOff;
};

struct Material{
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

uniform sampler2D textureColor;
uniform sampler2D textureNormal;
uniform samplerCube cubeTextureColor;
uniform Material mat;
uniform Light lights[8];
uniform int activeLights;
uniform vec4 eyePos;
uniform float ambient;
uniform int useLighting;

in vec4 fPos;
in vec4 fColor;
in vec4 fNorm;
in vec2 fTextCoords;
in vec3 fTexCube;
in mat3 TBN;
in vec4 fDepthCoord;

out vec4 fragColor;

void main()
{
    // ===== COLOR BASE =====
    vec4 baseColor = mat.color;

    if (mat.useColorText) {
        if (mat.textureType == 1) {
            // Cubemap: reflexion, refraccion o skybox
            baseColor = texture(cubeTextureColor, fTexCube);
        } else {
            // Textura 2D
            vec4 texColor = texture(textureColor, fTextCoords);
            baseColor = vec4(texColor.rgb, texColor.a * mat.color.a);
        }
    }

    float alpha = baseColor.a;

    // ===== SIN ILUMINACION (skybox) =====
    if (useLighting == 0 || !mat.computeLight) {
        fragColor = baseColor;
        return;
    }

    // ===== NORMAL Y VISTA =====
    vec3 N = normalize(fNorm.xyz);
    if (mat.usetextureNormal) {
        vec3 normalSample = texture(textureNormal, fTextCoords).rgb * 2.0 - 1.0;
        N = normalize(TBN * normalSample);
    }

    vec3 V = normalize(eyePos.xyz - fPos.xyz);

    // ===== AMBIENT =====
    // Objetos refractables: cubemap a intensidad completa, sin calculo de ambient ni difusa
    vec3 result = mat.refraction ? baseColor.rgb : baseColor.rgb * ambient;

    // ===== LUCES =====
    for (int i = 0; i < activeLights; i++) {
        if (lights[i].enable == 0) continue;

        vec3 L;
        float att = 1.0;
        float spotEffect = 1.0;

        // 1. Vector L y Atenuación según el TIPO
        if (lights[i].type == DIRECTIONAL) {
            L = normalize(-lights[i].direction.xyz);
        }
        else {
        // POINT o SPOT
            vec3 toL = lights[i].position.xyz - fPos.xyz;
            float dist = length(toL);
            L = (dist > 0.0001) ? (toL / dist) : vec3(0.0, 0.0, 1.0);

            // Atenuación lineal
            att = 1.0 / (1.0 + lights[i].linearAttenuation * dist);

            if (lights[i].type == SPOT) {
                vec3 spotDir = normalize(lights[i].direction.xyz);
                float theta = dot(L, normalize(-spotDir));

                if (theta < lights[i].cutOff) {
                    spotEffect = 0.0;
                }
            }
        }

        // 2. Cálculo de Componentes
        if (spotEffect > 0.0) {
            vec3 lightRGB = lights[i].color.rgb;

            // Especular (Phong)
            vec3 R = reflect(-L, N);
            float spec = pow(max(dot(V, R), 0.0), float(mat.shininess));

            if (mat.refraction) {
                // Especular
                result += att * spotEffect * spec * lightRGB;
            } else {
                // Difusa + especular
                float diff = max(dot(N, L), 0.0);
                result += att * spotEffect * (baseColor.rgb * diff * lightRGB);
                result += att * spotEffect * (spec * lightRGB);
            }
        }
    }

    // Proyección final del color al fragmento
    fragColor = vec4(result, alpha);
}