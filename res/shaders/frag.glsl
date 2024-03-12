// fragment

#version 410 core
in vec4 ourColor; // Use ourColor from the vertex shader
out vec4 FragColor; // Changed to 'out' variable

// uniform vec4 u_Time;

void main()
{
    // FragColor = 1 - ourColor * u_Time;
    FragColor = 1 - ourColor;
    // FragColor = 1 - normalize(vec4(ourColor.r, u_Time.g, u_Time.b, 1.0));
};
