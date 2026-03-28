#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

void main()
{
    float d = distance(vtexCoord, vec2(0.5,0.5)); //distancia del centre al vtexCoord
    
    if (step(0.2,d) == 0.0) fragColor = vec4(1.0, 0.0, 0.0, 0.0);
    else fragColor = vec4(1.0, 1.0, 1.0, 1.0);
    
}
