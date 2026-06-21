#version 330 core

in vec4 gfrontColor;
in vec2 gtexCoord;
out vec4 fragColor;

uniform vec2 viewport;

void main()
{
    vec4 yellow = vec4(1.0, 1.0, 0.0, 1.0);

    if (gfrontColor == yellow) {
        float x = gtexCoord.x;
        float y = gtexCoord.y;

        if (x >= 2.0 && x <= 3.0 && y >= 1.0 && y <= 6.0) fragColor = vec4(0.0);
        else if (x >= 2.0 && x <= 5.0 && y >= 5.0 && y <= 6.0) fragColor = vec4(0.0);
        else if (x >= 2.0 && x <= 4.0 && y >= 3.0 && y <= 4.0) fragColor = vec4(0.0);
        else fragColor = gfrontColor;
    }
    else fragColor = gfrontColor;
}
