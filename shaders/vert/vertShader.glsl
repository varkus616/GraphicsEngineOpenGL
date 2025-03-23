#version 430

layout (location=0) in vec2 textureCoords;
layout (location=1) in vec3 vertPos;
layout (location=2) in vec3 vertNormal;
layout (location=3) in vec4 vertColor;

uniform mat4 model;
uniform mat4 proj_matrix;
uniform mat4 norm_matrix;
uniform mat4 view;
uniform mat4 mvpmatrix;
uniform mat4 mvmatrix;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out vec4 VertColor;
out vec4 vEyeSpacePos;

void main() 
{
	Normal = mat3(norm_matrix) * vertNormal;
	FragPos=vec3(model * vec4(vertPos, 1.0));	
	
	TexCoords = textureCoords;
	VertColor = vertColor;

	gl_Position=proj_matrix * view * vec4(FragPos, 1);
	vEyeSpacePos = mvmatrix*vec4(vertPos, 1);
	
}



