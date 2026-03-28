#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

void main()
{
    int n_x = int(floor(vtexCoord.s * 8.0)); //per passar de [0,1] a [0,8]
    int n_y = int(floor(vtexCoord.t * 8.0));
    
    if      (n_x % 2 == 0 && n_y % 2 == 0) fragColor = vec4(0.8);
    else if (n_x % 2 == 0 && n_y % 2 != 0) fragColor = vec4(0.0);
    else if (n_x % 2 != 0 && n_y % 2 == 0) fragColor = vec4(0.0);
    else if (n_x % 2 != 0 && n_y % 2 != 0) fragColor = vec4(0.8);
}
