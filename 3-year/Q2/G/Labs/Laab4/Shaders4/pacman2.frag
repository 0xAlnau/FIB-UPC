#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D colormap;

void main()
{
    vec2 fant = vec2(0.0,0.0);
    vec2 pacm = vec2(1.0/6.0,0.0);
    vec2 blac = vec2(2.0/6.0,0.0);
    vec2 stra = vec2(3.0/6.0,0.0);
    vec2 curv = vec2(4.0/6.0,0.0);
    vec2 punt = vec2(5.0/6.0,0.0);

    int n = 15;
    vec2 coordMat = fract(vtexCoord * n);
    vec2 cela = floor(vtexCoord * n);

    vec2 offseet;
    vec2 coordRot = coordMat;

    if (cela.x == 0 && cela.y == 0) { //esq inf esq
        offseet = curv;
        coordRot = vec2(1.0 - coordMat.x, 1.0 - coordMat.y);
    }
    else if (cela.x == n-1 && cela.y == n-1) offseet = curv; //esq sup dre
    else if (cela.x == n-1 && cela.y == 0) { //esq inf dre
        offseet = curv;
        coordRot = vec2(1.0 - coordMat.y, coordMat.x);
    }
    else if (cela.x == 0 && cela.y == n-1) { //esq sup esq
        offseet = curv;
        coordRot = vec2(coordMat.y, 1.0 - coordMat.x);
    }
    else if (cela.x == 0 || cela.x == n-1) { //col esq
        offseet = stra;
        coordRot = vec2(coordMat.y, 1.0 - coordMat.x);
    }
    else if (cela.y == 0 || cela.y == n-1) offseet = stra; //abaix i adalt

    else if (cela.x == 4 && cela.y == 1) offseet = pacm;
    else if (cela.x == 5 && cela.y == 1) offseet = fant;
    else if (cela.y == 1 || cela.y == n-2 || cela.y == n/2) offseet = punt;
    else if (cela.x == 1 || cela.x == n-2 || cela.x == n/2) offseet = punt;
    else if (mod(cela.x, 2) == 1.0) offseet = punt;

    else {
        offseet = stra;
        coordRot = vec2(coordMat.y, 1.0 - coordMat.x);
    }

    vec2 escalat = vec2(coordRot.x / 6.0, coordRot.y);

    fragColor = texture(colormap, escalat + offseet);
}
