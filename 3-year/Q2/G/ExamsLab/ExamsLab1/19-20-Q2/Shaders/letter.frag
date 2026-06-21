#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

// dividir [0,1] en matriu de 7x7

void main()
{
    float radiC = (1.0 / 7.0) / 2.0;
    vec4 red = vec4(1.0, 0.0, 0.0, 1.0);
    vec4 bla = vec4(0.0,0.0,0.0,1.0);
    vec4 C;

    float ofset = radiC + radiC;
    vec2 puntA = vec2(ofset + radiC, radiC);
    vec2 puntB = vec2(ofset + radiC, ofset + radiC);
    vec2 puntC = vec2(ofset + radiC, 2.0*ofset + radiC);
    vec2 puntD = vec2(ofset + radiC, 3.0*ofset + radiC);
    vec2 puntE = vec2(ofset + radiC, 4.0*ofset + radiC);
    vec2 puntF = vec2(ofset + radiC, 5.0*ofset + radiC);

    vec2 puntG = vec2(5.0*ofset + radiC, radiC);
    vec2 puntH = vec2(5.0*ofset + radiC, ofset + radiC);
    vec2 puntI = vec2(5.0*ofset + radiC, 2.0*ofset + radiC);
    vec2 puntJ = vec2(5.0*ofset + radiC, 3.0*ofset + radiC);
    vec2 puntK = vec2(5.0*ofset + radiC, 4.0*ofset + radiC);
    vec2 puntL = vec2(5.0*ofset + radiC, 5.0*ofset + radiC);

    vec2 puntM = vec2(2.0*ofset + radiC, 2.0*ofset + radiC);
    vec2 puntN = vec2(3.0*ofset + radiC, 2.0*ofset + radiC);
    vec2 puntP = vec2(4.0*ofset + radiC, 2.0*ofset + radiC);

    vec2 puntQ = vec2(2.0*ofset + radiC, 6.0*ofset + radiC);
    vec2 puntR = vec2(3.0*ofset + radiC, 6.0*ofset + radiC);
    vec2 puntS = vec2(4.0*ofset + radiC, 6.0*ofset + radiC);

    float da = distance(vtexCoord, puntA);
    float db = distance(vtexCoord, puntB);
    float dc = distance(vtexCoord, puntC);
    float dd = distance(vtexCoord, puntD);
    float de = distance(vtexCoord, puntE);
    float df = distance(vtexCoord, puntF);

    float dg = distance(vtexCoord, puntG);
    float dh = distance(vtexCoord, puntH);
    float di = distance(vtexCoord, puntI);
    float dj = distance(vtexCoord, puntJ);
    float dk = distance(vtexCoord, puntK);
    float dl = distance(vtexCoord, puntL);

    float dm = distance(vtexCoord, puntM);
    float dn = distance(vtexCoord, puntN);
    float dp = distance(vtexCoord, puntP);

    float dq = distance(vtexCoord, puntQ);
    float dr = distance(vtexCoord, puntR);
    float ds = distance(vtexCoord, puntS);


    if (step(radiC, da) == 0.0) C = red;
    else if (step(radiC, db) == 0.0) C = red;
    else if (step(radiC, dc) == 0.0) C = red;
    else if (step(radiC, dd) == 0.0) C = red;
    else if (step(radiC, de) == 0.0) C = red;
    else if (step(radiC, df) == 0.0) C = red;
    else if (step(radiC, dg) == 0.0) C = red;
    else if (step(radiC, dh) == 0.0) C = red;
    else if (step(radiC, di) == 0.0) C = red;
    else if (step(radiC, dj) == 0.0) C = red;
    else if (step(radiC, dk) == 0.0) C = red;
    else if (step(radiC, dl) == 0.0) C = red;
    else if (step(radiC, dm) == 0.0) C = red;
    else if (step(radiC, dn) == 0.0) C = red;
    else if (step(radiC, dp) == 0.0) C = red;
    else if (step(radiC, dq) == 0.0) C = red;
    else if (step(radiC, dr) == 0.0) C = red;
    else if (step(radiC, ds) == 0.0) C = red;
    else C = bla;

    fragColor = C;
}
