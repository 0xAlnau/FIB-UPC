#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;
uniform sampler2D colormap;

void main()
{
    vec2 fant = vec2(0.0, 0.0);
    vec2 pacm = vec2(1.0 * 1.0/6.0, 0.0);
    vec2 noth = vec2(2.0 * 1.0/6.0, 0.0);
    vec2 stra = vec2(3.0 * 1.0/6.0, 0.0);
    vec2 curv = vec2(4.0 * 1.0/6.0, 0.0);
    vec2 pind = vec2(5.0 * 1.0/6.0, 0.0);

    int n = 10; //mida matriu nxn
    vec2 coordMat = fract(vtexCoord * n); //coordText dins de la cela, va de 0.0 a 0.99
    vec2 cela = floor(vtexCoord * n); //numero de cela entre 0 i 9

    vec2 escalat = vec2(coordMat.x / 6.0, coordMat.y); //nova base

    vec2 offseet;

    if ((cela.x == 0 || cela.x == 9) && (cela.y == 0 || cela.y == 9)) offseet = curv;
    else if (cela.x == 0 || cela.x == 9) offseet = stra;
    else if (cela.y == 0 || cela.y == 9) offseet = stra;
    else offseet = pacm;

    fragColor = texture(colormap, escalat + offseet);
}
