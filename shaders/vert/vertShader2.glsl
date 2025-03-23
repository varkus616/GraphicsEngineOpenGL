#version 420

#define MAX_POINT_LIGHTS 10
#define MAX_SPOT_LIGHTS 10

layout (location=0) in vec2 textureCoords;
layout (location=1) in vec3 vertPos;
layout (location=2) in vec3 vertNormal;
layout (location=3) in vec4 vertColor;

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

uniform int numPointLights;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

uniform mat4 mvpmatrix;
uniform mat4 mvmatrix;
uniform mat4 norm_matrix;
uniform vec3 vEyeSpaceCameraPos ;
out vec4 color;
//const vec3 vEyeSpaceCameraPos = vec3(0);


void main()
{
    vec4 res = vec4(0);
    for (int i=0;i<numPointLights;i++)
    {
        vec4 eyeLightPos = mvmatrix * vec4(pointLights[i].position, 1);
        vec4 eyeSpacePos = mvmatrix * vec4(vertPos, 1);
        vec3 eyeSpaceNormal = normalize(mat3(norm_matrix) * vertNormal);
        vec3 L = normalize(eyeLightPos.xyz - eyeSpacePos.xyz);
        vec3 V = normalize(vEyeSpaceCameraPos.xyz - eyeSpacePos.xyz);
        vec3 H = normalize(L + V);

        float diff = max(0, dot(eyeSpaceNormal, L));
        float spec = max(0, pow(dot(eyeSpaceNormal, H), 32));
        res += diff * vec4(pointLights[i].diffuse, 1);
        res += spec * vec4(pointLights[i].specular, 1);
    }
    color = res;
    gl_Position = mvpmatrix * vec4(vertPos, 1);

}