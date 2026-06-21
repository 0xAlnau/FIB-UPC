#version 330 core

in vec4 gfrontColor;
in vec2 gtexCoord;
out vec4 fragColor;

uniform sampler2D colorMap;

void main()
{
    if (gtexCoord.x < 0.0) fragColor = gfrontColor;
    else {
        vec4 col = texture(colorMap, gtexCoord);
        if (col.a < 0.1) discard;
        else fragColor = col * col.a;
    }
}
