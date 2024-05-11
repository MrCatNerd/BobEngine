// fragment

#version 330 core

out vec4 FragColor;

uniform vec3 lightColor;

void main() {
    FragColor = vec4(lightColor.rgb, 1.0);
}
