#version 460 core
out vec4 FragColor;

in vec2 TexCoords;
uniform sampler2D depthMap;

void main() {
    float d = texture(depthMap, TexCoords).r;
    FragColor = vec4(d, d, d, 1.0);
}