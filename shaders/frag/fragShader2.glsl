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

    float  constant;
    float  linear;
    float  quadratic;
};


uniform int numPointLights;
uniform int numSpotLights;

uniform PointLight pointLights[MAX_LIGHTS];
uniform SpotLight spotLights[MAX_LIGHTS];
uniform DirLight dirLight;

uniform vec4 objectColor;
uniform vec3 viewPos;
uniform bool calculateLight;

uniform sampler2D shadowMap;

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec4 FragPosLightSpace;
} fs_in;

float CalcShadowFactor()
{
    vec3 ProjCoords = fs_in.FragPosLightSpace.xyz / fs_in.FragPosLightSpace.w;
    
    ProjCoords = ProjCoords * 0.5 + 0.5; // [-1,1] -> [0,1]
    //vec2 UVCoords;
    //UVCoords.x = 0.5 * ProjCoords.x + 0.5;
    //UVCoords.y = 0.5 * ProjCoords.y + 0.5;

    if(ProjCoords.z > 1.0 
    || ProjCoords.x < 0.0 || ProjCoords.x > 1.0 
    || ProjCoords.y < 0.0 || ProjCoords.y > 1.0) {
        return 1.0; // No shadow
    }

    float z = 0.5 * ProjCoords.z + 0.5;
    //float Depth = texture(shadowMap, UVCoords).x;
    float shadow = texture(shadowMap, ProjCoords.xy).r;
    float current = ProjCoords.z;

    float bias = 0.0025;
    //if (Depth + bias < z)
    //    return 0.0;
    //else return 1.0f;
    return current - bias > shadow ? 1.0 : 0.0;
}

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float bias = 0.0055;
    float shadow = currentDepth  - bias > closestDepth  ? 1.0 : 0.0;

    return shadow;
}  

vec3 CalcDirLight(DirLight light, vec3 viewDir)
{
    vec3 lightDir = normalize(light.direction);


    float diff = max(0, dot(Normal, lightDir));

    vec3 reflectDir = reflect(-lightDir, Normal);
    float spec = pow(max(0, dot(viewDir, reflectDir)), 32);

    vec3 ambient = light.ambient;
    vec3 diffuse = light.diffuse * diff;
    vec3 specular = light.specular * spec;
    
    //float shadow = ShadowCalculation(fs_in.FragPosLightSpace);       
    
    float shadow = CalcShadowFactor();
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular));    

    return (lighting);
    //return (diffuse + ambient + specular);

}

vec3 CalcPointLight(PointLight light, vec3 viewDir)
{
    vec3 ambient = light.ambient;
    vec3 lightVec = light.position - FragPos;
    
    //diffuse
    vec3 lightDir = normalize(lightVec);
    float diff = max(0, dot(Normal, lightDir));


    //specular
    vec3 reflectDir = reflect(-lightDir, Normal);
    float spec = pow(max(0,dot(viewDir, reflectDir)), 32);
    

    //attenuation
    float distance = length(lightVec);
    float attenuation =  1.0 / 
    (light.constant + 
        light.linear * distance +
        light.quadratic * (distance * distance));

    diff *= attenuation;
    spec *= attenuation;
    ambient *= attenuation;
    
    vec3 specular = light.specular * spec;
    vec3 diffuse = light.diffuse * diff;

    //float shadow = ShadowCalculation(fs_in.FragPosLightSpace);                      
        float shadow = CalcShadowFactor();
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular));    
    return lighting;
    //return (specular + diffuse + ambient);
}

vec3 CalcSpotLight(SpotLight light, vec3 viewDir) 
{
    vec3 ambient = light.ambient;
    vec3 lightVec = light.position - FragPos;
    
    //diffuse
    vec3 lightDir = normalize(lightVec);
    float theta = dot(lightDir, normalize(-light.direction));
    
    //attenuation
    float distance = length(lightVec);
    float attenuation =  1.0 / 
    (light.constant + 
        light.linear * distance +
        light.quadratic * (distance * distance));
    
    float diff = max(0, dot(Normal, lightDir));
    vec3 diffuse = light.diffuse * diff;

    //specular
    vec3 reflectDir = reflect(-lightDir, Normal);
    float spec = pow(max(0, dot(viewDir, reflectDir)), 32);
    vec3 specular = light.specular * spec;

    //soft edge
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    diffuse *= intensity;
    specular *= intensity;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    float shadow = ShadowCalculation(fs_in.FragPosLightSpace);       
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular));    

    return lighting;
    //return (ambient + diffuse + specular);
}


void main()
{
    vec4 result = vec4(0);
    if ( calculateLight ) {
       vec3 lightResult = vec3(0);
       vec3 viewDir = normalize(viewPos - FragPos);
        
        for (int i = 0; i < numPointLights; i++)
        {
            //lightResult += CalcPointLight(pointLights[i], viewDir);   
        }
        for (int i = 0; i < numSpotLights; i++)
        {
           // lightResult += CalcSpotLight(spotLights[i], viewDir);   
        }
        lightResult += CalcDirLight(dirLight, viewDir);
       result += vec4(lightResult, 1) ;
    }
    
    result += objectColor * 0.5;
    FragColor = result;
}