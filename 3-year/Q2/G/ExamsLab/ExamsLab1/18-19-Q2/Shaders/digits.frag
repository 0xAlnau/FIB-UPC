#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D colorMap;
uniform float time;

void main()
{
    float s = vtexCoord.s;
    int time2 = int(time);

    int uni = time2 % 10;

    int des;
    if (time2 >= 10) des = (time2 / 10) % 10;
    else des = 0;

    int cen;
    if (time2 >= 100) cen = time2 / 100;
    else cen = 0;

    vec4 C;
    float offset;
    if (0 <= s && s < 1) {
        offset = (cen) / 10.0;
    }
    else if (1 <= s && s < 2) {
        offset = (des) / 10.0;
    }
    else {
        offset = (uni) / 10.0;
    }
    //                         al repertir-se varies vegades s ens qudem amb decimal i ens dona el correcte, cal posar-ho quan repetim textures!
    C = texture(colorMap, vec2(fract(vtexCoord.s) * (1.0/10.0) + offset, vtexCoord.t));

    if (C.a < 0.5) discard;
    else fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
