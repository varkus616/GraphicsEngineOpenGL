#version 430

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 texCoord;

uniform mat4 model_view_matrix;
uniform mat4 projection_matrix;
uniform float time;

out vec2 tc;
out vec4 color2;

layout (binding=0) uniform sampler2D samp;

void main() 
{
	gl_Position = projection_matrix * model_view_matrix * vec4(vPos, 1.0);
	color2 = gl_Position * time;
	tc = texCoord;
}