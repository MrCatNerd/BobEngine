// vertex

#version 410 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
out vec4 ourColor; // Changed to 'out' variable

void main()
{
    ourColor = aColor; // Assign aColor to ourColor

    // vec4 t = transpose(aPos.xyz)
    gl_Position = vec4(aPos.xyz, 1.0);
}
