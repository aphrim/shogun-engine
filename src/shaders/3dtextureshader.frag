in vec2 TexCord;
in vec3 FragPos;
in vec3 Color;
in vec3 Normal;
out vec4 FragColor;

// material parameters
uniform sampler2D albedoMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D normalMap;
uniform sampler2D aoMap;

struct PointLight {
    vec3 color;
    vec3 position;
    float strength;
};

#define NR_LIGHTS 100
uniform PointLight pointLights[NR_LIGHTS];
uniform float lightCount;

uniform vec3 viewPos;

void main() 
{
    vec3 albedo = pow(texture(albedoMap, TexCord).rgb, vec3(2.2));
    vec3 ambient = vec3(0.03) * albedo * ao;
    FragColor = vec4(color, 1.0);
}
