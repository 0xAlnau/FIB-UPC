#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform float n = 8;

void main()
{
    int n_x = int(floor(vtexCoord.s * n)); //passar de [0,1] a [0,8]
    int n_y = int(floor(vtexCoord.t * n));
    
    if (n_x % 2 == 0 && n_y % 2 == 0) fragColor = vec4(0.8);
    else if (n_x % 2 == 0 && n_y % 2 != 0) fragColor = vec4(0.0);
    else if (n_x % 2 != 0 && n_y % 2 == 0) fragColor = vec4(0.0);
    else if (n_x % 2 != 0 && n_y % 2 != 0) fragColor = vec4(0.8);
}
