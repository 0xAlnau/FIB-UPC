#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

void main()
{
    vec4 grey = vec4(vec3(0.1), 1.0);
    vec4 taro = vec4(vec3(1.0, 0.7, 0.0), 1.0);
    vec4 blac = vec4(vec3(0.0), 1.0);
    vec4 C;
    float r = 0.5; //per fer el radi gradient!

    float d = distance(vtexCoord, vec2(0.5,0.5));
    vec4 fons = mix(taro, blac, d/r);

    if (0.47 <= vtexCoord.s && vtexCoord.s <= 0.53 && 0.78 <= vtexCoord.t && vtexCoord.t <= 0.88) C = grey;
    else if (step(0.3, d) == 0.0) {
        float dUE = distance(vtexCoord, vec2(0.4, 0.6));
        float dUD = distance(vtexCoord, vec2(0.6, 0.6));
        float dBo = distance(vtexCoord, vec2(0.5, 0.5));
        if (step(0.08, dUE) == 0.0) C = fons;
        else if (step(0.08, dUD) == 0.0) C = fons;
        else if (step(0.23, dBo) == 0.0) {
            float dBo2 = distance(vtexCoord, vec2(0.5,0.55));
            if (step(0.23, dBo2) == 0.0) C = grey;
            else C = fons;
        }
        else C = grey;
    }
    else C = fons;
    fragColor = C;
}
