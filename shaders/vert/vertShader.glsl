#version 430

layout (location=1) in vec3 vertPos;
layout (location=2) in vec3 vertNormal;
layout (location=3) in vec4 vertColor;


layout (binding=0) uniform sampler2D samp;

out vec4 varyingColor;
out vec3 varyingNormal;		
out vec3 varyingLightDir;	
out vec3 varyingVertPos;
noperspective out vec2 tc;

const float PI = 3.14159;

struct PositionalLight
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 position;
};
struct Material
{	
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

uniform float time;
uniform vec4 globalAmbient;
uniform PositionalLight light;
uniform Material material;
uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform mat4 norm_matrix;

void main() 
{
	varyingVertPos=(mv_matrix * vec4(vertPos,1.0)).xyz;
	varyingLightDir = light.position - varyingVertPos;
	varyingNormal=(norm_matrix * vec4(vertNormal,1.0)).xyz;
	gl_Position=proj_matrix * mv_matrix * vec4(vertPos,1.0);

}



