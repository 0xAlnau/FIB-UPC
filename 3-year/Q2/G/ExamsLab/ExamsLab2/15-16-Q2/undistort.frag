#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D colorMap;

void main()
{
    vec2 st = (2.0 * vtexCoord) - 1.0;

    float r = length(st - vec2(0.0));
    float r2 = r + 0.22*r*r*r + 0.24*r*r*r*r*r;

    vec2 st2 = r2 * normalize(st);

    st2 = (st2 + 1.0) / 2.0;

    if (0.0 <= st2.s && st2.s <= 1.0 && 0.0 <= st2.t && st2.t <= 1.0) fragColor = texture(colorMap, st2);
    else fragColor = vec4(0.0);
}
