#version 330 core

in vec3 normalO;
out vec4 fragColor;

void main()
{
    vec3 color = (normalO + 1.0) / 2.0;
    fragColor = vec4(color, 1.0);
} 
