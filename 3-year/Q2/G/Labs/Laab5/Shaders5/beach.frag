#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
in vec3 normEye;
out vec4 fragColor;

uniform float time;
uniform sampler2D window; // interior
uniform sampler2D palm1; // palm tree
uniform sampler2D background2; // dunes

void main()
{
    vec4 C = texture(window, vtexCoord);
    if (C.w == 1.0) fragColor = C;
    else {
        vec2 coordD = vtexCoord + 0.25*normEye.xy + vec2(0.1*sin(2*time)*vtexCoord.t, 0);
        vec4 D = texture(palm1, coordD);
        if (D.w >= 0.5) fragColor = D;
        else {
            fragColor = texture(background2, vtexCoord + 0.5*normEye.xy);
        }
    }
}
