#version 330 core
out vec4 FragColor;

struct Material 
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

// Add padding to align with std140 layout
struct Sun 
{
    vec3 dir;
    vec4 colorAndIntensity;
};

struct SpotLight 
{
    vec3 pos;
    vec3 dir;
    vec4 colorAndIntensity;
};

struct AreaLight 
{
    vec3 pos;
    vec4 colorAndIntensity;
};

#define AMBIENT 0.0f

// Define UBO arrays for lights
#define MAX_SUNS 3
#define MAX_SPOTLIGHTS 15
#define MAX_AREALIGHTS 15

layout(std140) uniform Lighting 
{
    Sun suns[MAX_SUNS];
    SpotLight spotlights[MAX_SPOTLIGHTS];
    AreaLight areaLights[MAX_AREALIGHTS];
    vec3 numOfLights; // x = numSuns, y = numAreaLights, z = numSpotlights
};

// Fragment shader inputs
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

// Other uniforms
uniform vec3 viewPos;
uniform Material material;

vec3 CalcSunLight(Sun light, vec3 normal, vec3 viewDir, vec3 diffuseColor, vec3 specularColor);
vec3 CalcAreaLight(AreaLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseColor, vec3 specularColor); 
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseColor, vec3 specularColor); 

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Precompute diffuse and specular textures
    vec3 diffuseColor = vec3(texture(material.diffuse, TexCoords));
    vec3 specularColor = vec3(texture(material.specular, TexCoords));

    // Initialize the final color with global ambient light
    vec3 result = vec3(AMBIENT) * diffuseColor;


    // Apply Sun lights
    for (int i = 0; i < numOfLights.x; i++) 
    {
        result += CalcSunLight(suns[i], norm, viewDir, diffuseColor, specularColor);
    }

    // Apply Spotlights
    for (int i = 0; i < numOfLights.y; i++) 
    {
        result += CalcSpotLight(spotlights[i], norm, FragPos, viewDir, diffuseColor, specularColor);
    }

    // Apply Area lights (similar to point lights)
    for (int i = 0; i < numOfLights.z; i++) 
    {
        result += CalcAreaLight(areaLights[i], norm, FragPos, viewDir, diffuseColor, specularColor);
    }

    FragColor = vec4(result, 1.0);
}



// Helper function to calculate attenuation based on distance
float CalculateAttenuation(float distance, float constant, float linear, float quadratic) 
{
    return 1.0 / (constant + linear * distance + quadratic * distance * distance);
}


// Improved Sun Light Calculation
vec3 CalcSunLight(Sun light, vec3 normal, vec3 viewDir, vec3 diffuseColor, vec3 specularColor) 
{
    vec3 color = light.colorAndIntensity.xyz;  // Extract color
    float intensity = light.colorAndIntensity.w; // Intensity as the w component
    
    vec3 lightDir = normalize(-light.dir);
    float diff = max(dot(normal, lightDir), 0.0);
    //float spec = CalculateSpecular(lightDir, normal, viewDir, material.shininess);

    float spec = pow(max(dot(viewDir, lightDir), 0.0), material.shininess);


    vec3 diffuse = color * diff * diffuseColor;
    vec3 specular = color * 0.0f * specularColor;

    
    return intensity * (diffuse + specular); // intensity * (diffuse + specular);
}

// Improved Area Light Calculation
vec3 CalcAreaLight(AreaLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseColor, vec3 specularColor) 
{
    vec3 color = light.colorAndIntensity.xyz; // Extract color
    float intensity = light.colorAndIntensity.w; // Intensity as the w component

    vec3 lightDir = normalize(light.pos - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);

    float spec = pow(max(dot(viewDir, lightDir), 0.0), material.shininess);

    float distance = length(light.pos - fragPos);
    float attenuation = CalculateAttenuation(distance, 1.0, 0.14, 0.07); // Customize attenuation factors

    vec3 diffuse = color * diff * diffuseColor;
    vec3 specular = color *  0.0f * specularColor;

    return intensity * attenuation * (diffuse + specular);
}

// Improved Spot Light Calculation
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseColor, vec3 specularColor) 
{
    vec3 color = light.colorAndIntensity.xyz; // Extract color
    float intensity = light.colorAndIntensity.w; // Intensity as the w component

    vec3 lightDir = normalize(light.pos - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    float spec = pow(max(dot(viewDir, lightDir), 0.0), material.shininess);

    float distance = length(light.pos - fragPos);
    float attenuation = CalculateAttenuation(distance, 1.0, 0.14, 0.07); // Customize attenuation factors

    // Spot light intensity based on angle
    float theta = dot(lightDir, normalize(-light.dir));
    float innerCutoff = 0.9; // Adjust as needed
    float outerCutoff = 0.8; // Adjust as needed
    float epsilon = innerCutoff - outerCutoff;
    float spotIntensity = clamp((theta - outerCutoff) / epsilon, 0.0, 1.0);

    vec3 diffuse = color * diff * diffuseColor;
    vec3 specular = color *  0.0f * specularColor;

    return intensity * attenuation * spotIntensity * (diffuse + specular);
}
