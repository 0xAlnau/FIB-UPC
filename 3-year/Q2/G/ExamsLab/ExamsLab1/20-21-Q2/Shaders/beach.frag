#version 330 core

in vec4 frontColor;
in vec3 nEye;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D window; // interior
uniform sampler2D palm1; // palm-tree
uniform sampler2D background2; // dunes
uniform float time;

void main()
{
    vec4 color;
    vec4 C = texture(window, vtexCoord);
    if (C.a == 1.0) color = C;
    else {
        vec3 N = normalize(nEye);
        vec4 D = texture(palm1, vtexCoord + 0.25*N.xy + vec2(0.1*sin(2*time)*vtexCoord.t, 0));
        if (D.a >= 0.5) color = D;
        else color = texture(background2, vtexCoord + 0.5*N.xy);
    }
    fragColor = color;
}
