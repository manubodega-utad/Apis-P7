#version 330

uniform samplerCube cubeTextureColor;
uniform sampler2D textureColor; //unidad de textura de color
uniform sampler2D textureNormal; //unidad de textura de color

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

struct Light {
    vec3 pos;
    vec3 color;
    float intensity;
    int enable;
    
};

uniform Light light;
uniform vec3 camPos;

in vec4 fColor; //variable de entrada
in vec2 fTexCoord;
in vec4 fNormal;
in vec4 fPos;
in vec3 fTexCube;
in mat3 TBN;

out vec4 FragColor;

void main()
{
    vec4 tColor = vec4(0, 0, 0, 0);
    
    if(mat.useColorText)
        if (mat.textureType == 0) //textura 2D
        {
            tColor = texture(textureColor, fTexCoord);
        }
        else if (mat.textureType == 1) //textura 2D
        {
            tColor=textureCube(cubeTextureColor, fTexCube);
        }
    
    vec3 normal = fNormal.xyz;

   if (mat.usetextureNormal)
   {
        vec3 normalTextValue =
                            vec3(texture2D(textureNormal, fTexCoord).xyz *4.0f)-1.0f;

       normal = (TBN * normalTextValue);
    }

    float alpha = tColor.a;
    float lightComponent = 1;
    float ambient = 0.2f;
    if(light.enable==1 && mat.computeLight){
        vec3 N = normalize(normal);
        vec3 L = normalize(light.pos- fPos.xyz);

        float diffuse = max(dot(L, N),0.0f);//coseno ángulo entre rayo de luz y normal del punto a iluminar 
        vec3 R = normalize(reflect(L, N));
        vec3 EYE= normalize(fPos.xyz - camPos); ;
    
        float specular = pow(max(dot(R, EYE), 0.0f), mat.shininess);
        lightComponent = ambient + (diffuse+specular)*light.intensity;
    }

    FragColor = (fColor+tColor)* lightComponent*vec4(light.color,1.0f); //asignar color de salida
    FragColor.a = alpha;
    //gl_FragColor = vec4(1, 1, 1, 1);
}