#version 330 core

in vec3 FragPos;
in vec2 TexCord;
in vec3 Normal;
out vec4 FragColor;

uniform sampler2D tex;

void main() {
    FragColor = texture(tex, TexCord) + vec4(0.1,0.1,0.1,0.0);
}
