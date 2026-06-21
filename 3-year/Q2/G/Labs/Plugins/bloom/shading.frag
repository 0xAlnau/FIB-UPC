#version 330 core
out vec4 fragColor;
in vec4 vFragColor;

void main()
{
    fragColor = vFragColor;
}
