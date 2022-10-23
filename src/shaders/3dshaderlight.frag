#version 410 core

in vec3 FragPos;
in vec2 TexCord;
in vec3 Normal;
in vec3 Color;
out vec4 FragColor;

struct PointLight {
    vec3 color;
    vec3 position;
    float strength;
};

#define NR_LIGHTS 100
uniform PointLight pointLights[NR_LIGHTS];
uniform float lightCount;
uniform vec3 viewPos;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    float dis = length(light.position - fragPos);
    float attenuation = light.strength / dis + 1.0 / (light.strength / 10 * (dis * dis));
    return diff * vec3(attenuation) * light.color;
}

void main() {
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 base = Color;
    vec3 light = vec3(0.1,0.1,0.1); 
    for (int i = 0; i < lightCount; i++) {
        light += CalcPointLight(pointLights[i], Normal, FragPos, viewDir);
    }
    FragColor = vec4(base * light, 0);
}
