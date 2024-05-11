// vertex

#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 LightPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat3 normalMatrix;

uniform vec3 lightPos;

void main()
{
    Normal = normalMatrix * aNormal;
    LightPos = vec3(view * vec4(lightPos, 1.0)); // world to view space
    FragPos = vec3(view * model * vec4(aPos.xyz, 1.0));
    TexCoords = aTexCoords;

    gl_Position = projection * view * model * vec4(aPos.xyz, 1.0);
}
