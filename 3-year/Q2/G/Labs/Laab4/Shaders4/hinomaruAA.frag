#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

float aastep(float threshold, float x)
{
    float width = 0.7*length(vec2(dFdx(x), dFdy(x)));
    return smoothstep(threshold-width, threshold+width, x);
}

void main()
{
    float d = distance(vtexCoord, vec2(0.5,0.5)); //distancia del centre al vtexCoord
    float step_aa = aastep(0.2, d);
    fragColor = mix(vec4(1.0,0.0,0.0,1.), vec4(1.), step_aa);
        
}
