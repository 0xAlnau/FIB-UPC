#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

void main()
{
    vec4 red = vec4(1.0,0.0,0.0,1.0);
    vec4 whi = vec4(1.0);
    vec4 C;
    //reusar factor de 0.75 per no deformació!!!
    float d = distance(vec2(vtexCoord.x, vtexCoord.y * 0.75), vec2(0.75,0.5 * 0.75));
    float d1 = distance(vec2(vtexCoord.x, vtexCoord.y * 0.75), vec2(0.25,0.5 * 0.75));
    float d2 = distance(vec2(vtexCoord.x, vtexCoord.y * 0.75), vec2(0.375,0.5 * 0.75));

    if (step(0.13, d) == 0) C = whi;
    else if (step(0.20, d1) == 0) {
        if (step(0.20, d2) == 0.0) C = red;
        else C = whi;
    }
    else C = red;

    fragColor = C;
}
