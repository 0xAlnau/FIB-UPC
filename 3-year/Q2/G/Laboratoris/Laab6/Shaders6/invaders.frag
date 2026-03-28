#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D colorMap;

void main()
{
    vec2 pri = vec2(0.0, 0.0);
    vec2 seg = vec2(1.0 * 1.0/4.0, 0.0);
    vec2 ter = vec2(2.0 * 1.0/4.0, 0.0);
    vec2 qua = vec2(3.0 * 1.0/4.0, 0.0);
    vec2 cin = vec2(0.0 * 1.0/4.0, 1.0 * 1.0/4.0);
    vec2 sis = vec2(1.0 * 1.0/4.0, 1.0 * 1.0/4.0);
    vec2 set = vec2(2.0 * 1.0/4.0, 1.0 * 1.0/4.0);
    vec2 vui = vec2(3.0 * 1.0/4.0, 1.0 * 1.0/4.0);

    int n = 15; // 15x15 celes
    vec2 coordMat = fract(vtexCoord * n); //de 0.0 a 0.99
    vec2 cela = floor(vtexCoord * n); // entre [0..14] i [0..14]
    vec2 escalat = vec2(coordMat.x / 4.0, coordMat.y / 4.0); //nova base
    vec2 offseet;

    if ((cela.x == 0 || cela.x == 14) || (cela.y == 0 || cela.y == 14)) fragColor = vec4(vec3(0.0), 1.0);
    else if (cela.x == 6 && cela.y == 1) fragColor = texture(colorMap, escalat + vui);
    else if (cela.y == 1 || cela.y == 2 || cela.y == 4) fragColor = vec4(vec3(0.0), 1.0);
    else if (cela.y == 3 && (cela.x == 1 || cela.x == 5 || cela.x == 9 || cela.x == 13)) fragColor = texture(colorMap, escalat + qua);
    else if (cela.y == 3) fragColor = vec4(vec3(0.0), 1.0);
    else if (cela.y == 5) fragColor = texture(colorMap, escalat + pri);
    else if (cela.y == 6) fragColor = texture(colorMap, escalat + seg);
    else if (cela.y == 7) fragColor = texture(colorMap, escalat + ter);
    else if (cela.y == 8) fragColor = texture(colorMap, escalat + cin);
    else if (cela.y == 9) fragColor = texture(colorMap, escalat + sis);
    else if (cela.y == 10) fragColor = texture(colorMap, escalat + set);
    else fragColor = texture(colorMap, escalat + pri);
}
