#version 430

layout (location=0) in vec3 vertPos;
layout (location=1) in vec3 vertNormal;
layout (location=2) in vec2 TextCoords;

uniform mat4 mvpmatrix;
uniform mat4 model;
uniform mat4 lightSpaceMatrix;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec4 FragPosLightSpace;
    vec2 TexCoords;
} vs_out;


void main()
{
    vs_out.TexCoords = TextCoords;
    vs_out.FragPos = vec3(model * vec4(vertPos, 1));

    vs_out.Normal = normalize(mat3(inverse(transpose(model)))* vertNormal);
    
    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
    gl_Position = mvpmatrix * vec4(vertPos, 1);
}