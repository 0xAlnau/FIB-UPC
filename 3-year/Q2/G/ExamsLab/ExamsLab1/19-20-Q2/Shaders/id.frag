#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

const int pri = 4;
const int seg = 3;
const int ter = 5;
const int qua = 7;
const int cin = 3;
const int sis = 7;

uniform sampler2D colorMap;

void main()
{
    float offset;
    if (vtexCoord.s <= 1.0) {
        offset = pri / 10.0;
    }
    else if (vtexCoord.s <= 2.0) {
        offset = seg / 10.0;
    }
    else if (vtexCoord.s <= 3.0) {
        offset = ter / 10.0;
    }
    else if (vtexCoord.s <= 4.0) {
        offset = qua / 10.0;
    }
    else if (vtexCoord.s <= 5.0) {
        offset = cin / 10.0;
    }
    else {
        offset = sis / 10.0;
    }

    vec2 text = vtexCoord;
    text.x = fract(vtexCoord.x) / 10.0 + offset;
    vec4 C = texture(colorMap, text);

    if (C.a < 0.5) discard;
    fragColor = vec4(0.0,0.0,1.0,1.0);
}
