#version 430
layout (location=3) in vec4 vertColor;


struct Material {
    sampler2D diffuse;
    sampler2D specular;
    vec3 ambient;
    //vec3 diffuse;
    //vec3 specular;
    float shininess;
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


uniform SpotLight light;  
uniform Material material;
uniform vec3 viewPos;

in vec3 varyingNormal;
in vec3 varyingLightDir;
in vec3 varyingVertPos;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

void main()
{    
    vec3 lightDir = normalize(light.position - FragPos);
    float theta = dot(lightDir, normalize(-light.direction));

    if (theta > light.cutOff)
    {
        float distance = length(light.position - FragPos);

        float attenuation =  1.0 / (light.constant  + light.linear * distance + light.quadratic * (distance * distance));

        // ambient
        //vec3 ambient = light.ambient * material.ambient;
        vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
  	    
        // diffuse 
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0);
        //vec3 diffuse = light.diffuse * (diff * material.diffuse);
        vec3 diffuse =  light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

        // specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        //vec3 specular = light.specular * (spec * material.specular);  
        vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));  


        //ambient *= attenuation;
        //diffuse *= attenuation;
        //specular *= attenuation;

        vec4 lightColor = vec4(ambient + diffuse + specular, 1.f);

        vec4 result = (vertColor * 0.5f) + (lightColor * 0.5f);

        FragColor = result;
    }else
       FragColor = vec4(light.ambient * vec3(texture(material.diffuse, TexCoords)), 1.0);
}

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
    return (ambient + diffuse + specular);
} 