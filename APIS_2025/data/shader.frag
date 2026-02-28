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
	int shininess;
};

uniform sampler2D colorText;
uniform Light lights[8];
uniform int activeLights;
uniform Material mat;
uniform vec4 eyePos;
uniform float ambient;

in vec4 fPos;
in vec4 fColor;
in vec4 fNorm;
in vec2 fTextCoords;


out vec4 fragColor;

void main() 
{
    // ===== COLOR BASE =====
    vec4 baseColor = mat.color;
    if (mat.useColorText) {
        baseColor = texture(colorText, fTextCoords);
    }

    // ===== NORMAL Y VISTA =====
    vec3 N = normalize(fNorm.xyz);
    vec3 V = normalize(eyePos.xyz - fPos.xyz);

    // ===== AMBIENT =====
    // El ambiente se suma una sola vez de forma global
    vec3 result = baseColor.rgb * ambient;

    // ===== BUCLE MULTI-LUZ (Soporta hasta 8 luces simultáneas) =====
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

        // 2. Cálculo de Componentes (Solo si la luz alcanza este fragmento)
        if (spotEffect > 0.0) {
            // Difusa (Lambert)
            float diff = max(dot(N, L), 0.0);
            
            // Especular (Phong)
            vec3 R = reflect(-L, N);
            float spec = pow(max(dot(V, R), 0.0), float(mat.shininess));

            vec3 lightRGB = lights[i].color.rgb;

            // Acumulamos el resultado de esta luz al color final
            result += att * spotEffect * (baseColor.rgb * diff * lightRGB);
            result += att * spotEffect * (spec * lightRGB);
        }
    }

    // Proyección final del color al fragmento
    fragColor = vec4(result, baseColor.a);
}