#version 330 core

in vec4 frontColor;
in vec3 P;
in vec3 nEye;
in vec2 vtexCoord;
out vec4 fragColor;

uniform int mode = 3;

void main()
{
    vec4 C;
    vec3 N = normalize(nEye);

    if (mode == 0) C = vec4(N.z);
    else if (mode == 1) {
        if (N.z < 0.4) C = vec4(0.0);
        else C = vec4(1.0);
        C.b = C.b * 0.9;
    }
    else if (mode == 2) {
        vec3 V = normalize(-P);
        if (dot(V,N) < 0.4) C = vec4(0.0);
        else C = vec4(1.0);
        C.r = C.r * 0.8;
    }
    else {
        vec3 V = normalize(-P);
        if (dot(V,N) < 0.4) {
            C = vec4(0.0);
            C.r = C.r * 0.8;
        }
        else if (dot(V,N) > 0.95) C = vec4(1.0);
        else {
            C = vec4(1.0);
            C.r = C.r * 0.8;
        }
    }
    fragColor = C;
}
