#version 430

#define MAX_LIGHTS 20

struct PointLight {    
    vec3 position;    
    float constant;
    float linear;
    float quadratic;  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
};

uniform int numPointLights;
uniform int numSpotLights;
uniform PointLight pointLights[MAX_LIGHTS];
uniform SpotLight spotLights[MAX_LIGHTS];
uniform DirLight dirLight;

uniform vec4 objectColor;
uniform vec3 viewPos;
uniform bool calculateLight;
uniform bool hasTexture;
uniform bool calculateShadows; 

uniform sampler2D shadowMap;
uniform sampler2D diffuseTexture;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec4 FragPosLightSpace;
    vec2 TexCoords;
} fs_in;

out vec4 FragColor;

float CalculateShadow(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir) {
    if(!calculateShadows) return 0.0;
    
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;

    if (projCoords.z > 1.0 || any(lessThan(projCoords.xy, vec2(0.0)))) 
        return 0.0;
   

    float bias = max(0.005 * (1.0 - dot(normal, lightDir)), 0.001);
    float depth = texture(shadowMap, projCoords.xy).r;
    return (projCoords.z - bias > depth) ? 1.0 : 0.0;
}

vec3 CalculateLight(vec3 lightDir, vec3 normal, vec3 viewDir, 
                   vec3 ambientColor, vec3 diffuseColor, vec3 specularColor) {
    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    
    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    
    return ambientColor + (diff * diffuseColor + spec * specularColor);
}

// --- Funkcje œwiate³ ---
vec3 CalculateDirectionalLight(DirLight light, vec3 normal, vec3 viewDir, vec3 material) {
    vec3 lightDir = normalize(-light.direction);
    float shadow = CalculateShadow(fs_in.FragPosLightSpace, normal, lightDir);
    
    vec3 ambient = light.ambient * material;
    vec3 color = CalculateLight(lightDir, normal, viewDir, 
                               light.ambient, light.diffuse, light.specular) * material;
    return ambient + (1.0 - shadow) * (color - ambient);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 material) {
    vec3 lightDir = normalize(light.position - fragPos);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
                             light.quadratic * (distance * distance));
    
    vec3 color = CalculateLight(lightDir, normal, viewDir, 
                               light.ambient, light.diffuse, light.specular);
    return (color * attenuation) * material;
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 material) {
    vec3 lightDir = normalize(light.position - fragPos);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    
    vec3 color = CalculateLight(lightDir, normal, viewDir, 
                               light.ambient, light.diffuse, light.specular);
    return color * intensity * material;
}

void main() {
    vec3 material = hasTexture ? texture(diffuseTexture, fs_in.TexCoords).rgb : objectColor.rgb;
    vec3 normal = normalize(fs_in.Normal);
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    
    vec3 result = vec3(0.0);
    if (calculateLight) {
        result += CalculateDirectionalLight(dirLight, normal, viewDir, material);
        
        for (int i = 0; i < numPointLights; i++)
            result += CalculatePointLight(pointLights[i], normal, fs_in.FragPos, viewDir, material);
        
        for (int i = 0; i < numSpotLights; i++)
            result += CalculateSpotLight(spotLights[i], normal, fs_in.FragPos, viewDir, material);
    } else {
        result = vec3(0);//material;
    }
    
    FragColor = vec4(result, hasTexture ? texture(diffuseTexture, fs_in.TexCoords).a : objectColor.a);
}