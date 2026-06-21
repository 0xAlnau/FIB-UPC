#version 330 core

in vec4 gfrontColor;
in vec2 gtexCoord;
out vec4 fragColor;

void main()
{
    if (gtexCoord.s >= 0.05 && gtexCoord.s <= 0.95 && gtexCoord.t >= 0.05 && gtexCoord.t <= 0.95) fragColor = gfrontColor;
    else fragColor = vec4(0.0);
}
