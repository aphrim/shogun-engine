#version 410 core
in vec3 FragPos;
in vec2 TexCord;
in vec3 Normal;
in vec3 Color;
out vec4 FragColor;

uniform sampler2D tex;

void main() {
    FragColor = texture(tex, TexCord) + vec4(Color,0.0);
}
