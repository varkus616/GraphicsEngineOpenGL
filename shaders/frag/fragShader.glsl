#version 430
#define MAX_POINT_LIGHTS 10
#define MAX_SPOT_LIGHTS 10

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    vec3 diffuseColor;
    vec3 specularColor;
    vec3 ambient;
    float shininess;

    bool useTexture;
};

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float  constant;
    float  linear;
    float  quadratic;
};


struct SpotLight {
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float cutOff;
    float outerCutOff;

    float  constant;
    float  linear;
    float  quadratic;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

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
uniform int numSpotLights;
uniform DirLight dirLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform Material material;

uniform vec3 viewPos;
uniform vec4 objectColor;
uniform mat4 mvpmatrix;
uniform mat4 mvmatrix;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec4 VertColor;
in vec4 vEyeSpacePos;

out vec4 FragColor;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}  

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return vec3(1);//(ambient + diffuse + specular);
} 

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    float theta = dot(lightDir, normalize(-light.direction));
    if (theta > light.outerCutOff) {
        
        float diff = max(dot(normal, lightDir), 0.0);
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        float distance = length(light.position - fragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
        
        float theta     = dot(lightDir, normalize(-light.direction));
        float epsilon   = light.cutOff - light.outerCutOff;
        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 0.6); 

        vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
        vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
        
        diffuse *= intensity;
        ambient *= intensity;
        specular *= intensity;

        return (ambient + diffuse + specular) * attenuation;
    } else {
          return light.ambient * vec3(texture(material.diffuse, TexCoords));
    }
}


void main()
{    
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = vec3(0);
    

    //result = pointLights[0].ambient;

    for (int i = 0; i < numPointLights; i++) {
        vec4 eyeSpaceLightPos = mvmatrix * vec4(pointLights[i].position, 1);
        vec3 L = normalize(eyeSpaceLightPos.xyz - vEyeSpacePos.xyz);
        vec3 V = normalize(viewPos.xyz - vEyeSpacePos.xyz);
        vec3 H = normalize(L+V);
        float diff = max(0, dot(norm, L));
        float spec = max(0, pow(dot(norm, H), 32));
        //
        vec3 diffuse = diff * pointLights[i].diffuse;
        vec3 specular = spec * pointLights[i].specular;
        result += diffuse + specular;
    }
    
    // Sumujemy œwiat³o od Spot Lightów
    //for (int i = 0; i < numSpotLights; i++) {
    //    result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);
    //}
    
    //FragColor = vec4(result * 1, 1.0);// + VertColor * 0.1 + objectColor * 0.1;
    FragColor = vec4(1);
}