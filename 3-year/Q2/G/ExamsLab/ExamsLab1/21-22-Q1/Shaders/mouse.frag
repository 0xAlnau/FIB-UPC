#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;
uniform int mode = 2;

void main()
{
    vec4 whi = vec4(vec3(1.0), 1.0);
    vec4 bla = vec4(vec3(0.0), 1.0);
    vec4 gre = vec4(vec3(0.8), 1.0);
    vec4 ski = vec4(vec3(1.0, 0.8, 0.6), 1.0);
    vec4 C;

    float dCara = distance(vtexCoord, vec2(0.5, 0.4));
    float dOrE  = distance(vtexCoord, vec2(0.19, 0.8));
    float dOrD  = distance(vtexCoord, vec2(0.81, 0.8));

    if (step(0.35, dCara) == 0.0) C = bla;
    else if (step(0.19, dOrE) == 0.0) C = bla;
    else if (step(0.19, dOrD) == 0.0) C = bla;
    else C = gre;

    if (mode >= 1 && mode <= 2) {
        //vec2 v = vtexCoord - vec2(0.5, 0.3);
        //v.x = v.x * 0.4;
        //if (length(v) < 0.11) C = ski;
        float dBoca = distance(vec2(vtexCoord.s * 0.4, vtexCoord.t), vec2(0.5 * 0.4, 0.3));
        float dE = distance(vec2(vtexCoord.s, vtexCoord.t * 0.4), vec2(0.45, 0.45 * 0.4));
        float dD = distance(vec2(vtexCoord.s, vtexCoord.t * 0.4), vec2(0.55, 0.45 * 0.4));
        if (step(0.11, dBoca) == 0.0) C = ski;
        else if (step(0.1, dE) == 0.0) C = ski;
        else if (step(0.1, dD) == 0.0) C = ski;

        if (mode == 2) {
            float dUE = distance(vec2(vtexCoord.s, vtexCoord.t * 0.4), vec2(0.45, 0.5 * 0.4));
            float dUD = distance(vec2(vtexCoord.s, vtexCoord.t * 0.4), vec2(0.55, 0.5 * 0.4));
            if (step(0.06, dUE) == 0.0) {
                float dIE = distance(vec2(vtexCoord.s, vtexCoord.t * 0.4), vec2(0.45, 0.44 * 0.4));
                if (step(0.03, dIE) == 0.0) C = bla;
                else C = whi;
            }
            else if (step(0.06, dUD) == 0.0) {
                float dID = distance(vec2(vtexCoord.s, vtexCoord.t * 0.4), vec2(0.55, 0.44 * 0.4));
                if (step(0.03, dID) == 0.0) C = bla;
                else C = whi;
            }
        }
    }

    fragColor = C;
}
