#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D spiral;
uniform float time;
uniform int mult = 1;
const float pi = 3.141592;


void main()
{
    vec2 st = mult * vtexCoord;
    vec2 st_loc = fract(st);

    float angle = 2*pi*sin(0.3*time);
    mat2 rot = mat2(vec2(cos(angle), sin(angle)), vec2(-sin(angle), cos(angle)));

    vec2 vtexRot = rot*(st_loc - vec2(0.5)) + vec2(0.5); //traslladem al mig !!!
    vtexRot = clamp(vtexRot, 0.0, 1.0);

    fragColor = texture(spiral, vtexRot);
}
