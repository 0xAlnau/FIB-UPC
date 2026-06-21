#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D fbm;
uniform float time;
const float pi = 3.14159;
const float A = 1.0;
const float f = 0.1;

// vermell -- groc -- verd -- cian -- blau -- magenta -- vermell

void main()
{
    vec4 red = vec4(1.0, 0.0, 0.0, 1.0);
    vec4 gro = vec4(1.0, 1.0, 0.0, 1.0);
    vec4 gre = vec4(0.0, 1.0, 0.0, 1.0);
    vec4 cia = vec4(0.0, 1.0, 1.0, 1.0);
    vec4 blu = vec4(0.0, 0.0, 1.0, 1.0);
    vec4 mag = vec4(1.0, 0.0, 1.0, 1.0);

    vec4 C = texture(fbm, vtexCoord);
    float phi = 2*pi*C.r;
    float v = A*sin(2*pi*f*time + phi);
    vec4 color;
    float t = (v + 1.0) / 2.0;
    if (v == -1.0) color = red;
    else if ( -1.0 < v && v <= -0.667) color = mix(red, gro, t);
    else if ( -0.667 < v && v <= -0.334) color = mix(gro, gre, t);
    else if ( -0.334 < v && v <= 0.0) color = mix(gre, cia, t);
    else if ( 0.0 < v && v <= 0.334) color = mix(cia, blu, t);
    else if ( 0.334 < v && v <= 0.667) color = mix(blu, mag, t);
    else if ( 0.667 < v && v < 1.0) color = mix(mag, red, t);
    else color = red;

    fragColor = color;
}
