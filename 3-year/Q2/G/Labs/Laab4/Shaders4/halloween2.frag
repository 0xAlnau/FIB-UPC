#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

void main()
{
    float radi = 0.5;
    float d = distance(vtexCoord, vec2(0.5,0.5));

    if (step(0.3, d) == 0.0) {
        float ull_e = distance(vtexCoord, vec2(0.4,0.6));
        float ull_d = distance(vtexCoord, vec2(0.6,0.6));
        float boca = distance(vtexCoord, vec2(0.5, 0.35));
        if (step(0.08, ull_e) == 0.0) {
            float d_esc = clamp(d/radi, 0.0, 1.0);
            fragColor = mix(vec4(0.9,0.6,0.0,0.0), vec4(0.0), d_esc);
        }
        else if (step(0.08, ull_d) == 0.0) {
            float d_esc = clamp(d/radi, 0.0, 1.0);
            fragColor = mix(vec4(0.9,0.6,0.0,0.0), vec4(0.0), d_esc);
        }
        else if (step(0.13, boca) == 0.0) {
            float orange = distance(vtexCoord, vec2(0.5, 0.4));
            if (step(0.13, orange) == 1.0) {
                float d_esc = clamp(d/radi, 0.0, 1.0);
                fragColor = mix(vec4(0.9,0.6,0.0,0.0), vec4(0.0), d_esc);
            }
            else fragColor = vec4(0.1);

        }
        else fragColor = vec4(0.1);
    }
    else if (vtexCoord.s >= 0.47 && vtexCoord.s <= 0.53 && vtexCoord.t >= 0.78 && vtexCoord.t <=0.90) {
        fragColor = vec4(0.1);
    }
    else {
        float d_esc = clamp(d/radi, 0.0, 1.0); //clamp fa que d/radi com a mínim sea 0.0 i màxim 1.0
        fragColor = mix(vec4(0.9,0.6,0.0,0.0), vec4(0.0), d_esc);
    }


}
