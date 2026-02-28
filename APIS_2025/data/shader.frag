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

	// ===== NORMAL =====
    vec3 N = normalize(fNorm.xyz);

    // ===== AMBIENT =====
    vec3 result = baseColor.rgb * ambient;

    // ===== LUZ =====
    if (activeLights > 0 && lights[0].enable == 1) {

        vec3 L;
        float att = 1.0;

        if (lights[0].type == DIRECTIONAL) {
            L = normalize(-lights[0].direction.xyz);
        } 
        else if (lights[0].type == POINT) {
            vec3 toL = lights[0].position.xyz - fPos.xyz;
            float dist = length(toL);
            L = (dist > 0.0001) ? (toL / dist) : vec3(0,0,1);
            att = 1.0 / (1.0 + lights[0].linearAttenuation * dist);
        }

        // Diffuse
        float diff = max(dot(N, L), 0.0);

        // Specular
        vec3 V = normalize(eyePos.xyz - fPos.xyz);
        vec3 R = reflect(-L, N);
        float spec = pow(max(dot(V, R), 0.0), float(mat.shininess));

        vec3 lightRGB = lights[0].color.rgb;

        result += att * (baseColor.rgb * diff * lightRGB);
        result += att * (spec * lightRGB);
    }

    fragColor = vec4(result, baseColor.a);
}