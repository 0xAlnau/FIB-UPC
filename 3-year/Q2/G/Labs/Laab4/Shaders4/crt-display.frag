#version 330 core

in vec4 frontColor;
out vec4 fragColor;
uniform int n;

void main()
{
    int linia = int(gl_FragCoord.y - 0.5);
    if (linia % n == 0) fragColor = frontColor;
    else discard;
}
