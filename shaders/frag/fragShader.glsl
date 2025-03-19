#version 430

//layout(location = 0) out vec4 vFragColor;
//layout(location = 1) out vec4 vVertexColor;

layout (location=3) in vec4 vertColor;
// uniforms match those in the vertex shader,
// but are not used directly in this fragment shader
struct PositionalLight
{	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 position;
};
struct Material
{	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};


uniform vec4 globalAmbient;
//uniform PositionalLight light;
//uniform Material material;
uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform mat4 norm_matrix;
uniform vec3 objectColor;

uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec3 lightPosition;


in vec3 varyingNormal;
in vec3 varyingLightDir;
in vec3 varyingVertPos;
in vec3 FragPos;
in vec3 Normal;
out vec4 fragColor;

const float ambientStrenght = 0.1f;

void main() 
{
	//vec3 L = normalize(varyingLightDir);
	//vec3 N = normalize(varyingNormal);
	//vec3 V = normalize(-varyingVertPos);
	//// compute light reflection vector with respect to N:
	//vec3 R = normalize(reflect(-L, N));
	//// get the angle between the light and surface normal:
	//float cosTheta = dot(L,N);
	//// angle between the view vector and reflected light:
	//float cosPhi = dot(V,R);
	// compute ADS contributions (per pixel), and combine to build output color:


	//vec3 diffuse = light.diffuse.xyz * material.diffuse.xyz * max(cosTheta,0.0);
	//vec3 specular =
	//light.specular.xyz * material.specular.xyz * pow(max(cosPhi,0.0), material.shininess);
	
	//vec3 ambient = ((globalAmbient * material.ambient) + (light.ambient * material.ambient)).xyz * ambientStrenght;
	vec3 ambient = ambientStrenght * vec3(lightAmbient);

	vec3 norm = normalize(Normal);
	vec3 lighDir = normalize(lightPosition - FragPos);

	float diff = max(dot(norm, lighDir), 0.f); 
	vec3 diffuse =  diff * vec3(lightDiffuse); 

	vec3 result = (ambient + diffuse) * objectColor;
	fragColor = vec4(result, 1.f);

}