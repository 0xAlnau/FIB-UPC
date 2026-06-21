#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

void main()
{
    vec4 gre = vec4(vec3(0.0,0.75,0.0), 1.0);
    vec4 yel = vec4(vec3(1.0,1.0,0.0), 1.0);
    vec4 blu = vec4(vec3(0.0,0.0,1.0), 1.0);
    vec4 C;
    vec2 st = vec2(vtexCoord.s, vtexCoord.t * 0.5);

    if (0.1 <= st.s && st.s <= 0.9 && 0.2*0.5 <= st.t && st.t <= 0.8*0.5) {
        float d = distance(st, vec2(0.5,0.5*0.5)); //distancia del centre al vtexCoord
        if (step(0.1,d) == 0.0) {
            float d2 = distance(st, vec2(0.5, 0.6*0.5));
            if (step(0.12, d2) == 0.0) {
                float d3 = distance(st, vec2(0.5, 0.63*0.5));
                if (step(0.12, d3) == 0) C = blu;
                else C = yel;
            }
            else C = blu;
        }
        else C = yel;
    }
    else C = gre;

    fragColor = C;
}
