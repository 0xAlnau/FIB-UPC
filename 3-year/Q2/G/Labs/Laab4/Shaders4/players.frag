#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
in vec2 P;
out vec4 fragColor;

uniform int mode = 3;
uniform sampler2D courtMap;
uniform sampler2D player1;
uniform vec2 p1 = vec2(-3,-8);
uniform vec2 p2 = vec2(3,-8);
uniform vec2 p3 = vec2(-2,2);
uniform vec2 p4 = vec2(2,2);

//passar de unas coord de textura a unes altres
//exemple, quadrat 2m x 2m => interval [-1,1]
//hem de passar a [0,1]:
//      -> dividint entre 2: [-0.5, 0.5]
//      -> sumant 0.5:       [0.0, 0.0] :)

//a on posem la textura amb un if indicant la zona


void main()
{
    if (mode == 0) {
        fragColor = texture(courtMap, vtexCoord);
    }
    else {

        if ((0.0 <= fract(P.x) && fract(P.x) <= 0.05) || (0.0 <= fract(P.y) && fract(P.y) <= 0.05)) {
            fragColor = vec4(texture(courtMap, vtexCoord).rgb * 1.2, 1.0);
        }
        else fragColor = texture(courtMap, vtexCoord);


        if (mode == 2) {
            float r_int = 0.4;
            float r_ext = 0.5;
            float d_P1 = distance(P, p1);
            float d_P2 = distance(P, p2);
            float d_P3 = distance(P, p3);
            float d_P4 = distance(P, p4);
            if (step(r_ext, d_P1) == 0.0) {
                if (step(r_int, d_P1) == 0.0) fragColor = vec4(1.0);
                else fragColor = vec4(0.0);
            }
            if (step(r_ext, d_P2) == 0.0) {
                if (step(r_int, d_P2) == 0.0) fragColor = vec4(1.0);
                else fragColor = vec4(0.0);
            }
            if (step(r_ext, d_P3) == 0.0) {
                if (step(r_int, d_P3) == 0.0) fragColor = vec4(1.0);
                else fragColor = vec4(0.0);
            }
            if (step(r_ext, d_P4) == 0.0) {
                if (step(r_int, d_P4) == 0.0) fragColor = vec4(1.0);
                else fragColor = vec4(0.0);
            }
        }
        else if (mode == 3) {
            if (-4.0 <= P.x && P.x <= -2.0 && -9.0 <= P.y && P.y <= -7.0) {
                vec2 vtexCoordNoves = (P - p1) / 2.0 + 0.5; //passem de [-1,1] a [0,1]
                vec4 col = texture(player1, vtexCoordNoves);
                if (col.r > 0.5 || col.b < 0.5) fragColor = col;
            }
            if (2.0 <= P.x && P.x <= 4.0 && -9.0 <= P.y && P.y <= -7.0) {
                vec2 vtexCoordNoves = (P - p2) / 2.0 + 0.5; //passem de [-1,1] a [0,1]
                vec4 col = texture(player1, vtexCoordNoves);
                if (col.r > 0.5 || col.b < 0.5) fragColor = col;
            }
            if (-3.0 <= P.x && P.x <= -1.0 && 1.0 <= P.y && P.y <= 3.0) {
                vec2 vtexCoordNoves = (P - p3) / 2.0 + 0.5; //passem de [-1,1] a [0,1]
                vtexCoordNoves.y = 1.0 - vtexCoordNoves.y;
                vec4 col = texture(player1, vtexCoordNoves);
                if (col.r > 0.5 || col.b < 0.5) fragColor = col;
            }
            if (1.0 <= P.x && P.x <= 3.0 && 1.0 <= P.y && P.y <= 3.0) {
                vec2 vtexCoordNoves = (P - p4) / 2.0 + 0.5; //passem de [-1,1] a [0,1]
                vtexCoordNoves.y = 1.0 - vtexCoordNoves.y;
                vec4 col = texture(player1, vtexCoordNoves);
                if (col.r > 0.5 || col.b < 0.5) fragColor = col;
            }
        }
    }

}
