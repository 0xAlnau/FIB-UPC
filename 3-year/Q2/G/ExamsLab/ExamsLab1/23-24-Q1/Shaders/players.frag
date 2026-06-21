#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
in vec2 P;
out vec4 fragColor;

uniform int mode = 3;
uniform vec2 p1 = vec2(-3, -8);
uniform vec2 p2 = vec2( 3, -8);
uniform vec2 p3 = vec2(-2, 2);
uniform vec2 p4 = vec2( 2, 2);
uniform sampler2D courtMap;
uniform sampler2D player1;

void main()
{
    vec4 C;
    vec4 court = texture(courtMap, vtexCoord);
    if (mode == 0) C = court;
    else {
        if (fract(P.x) < 0.05 || fract(P.y) < 0.05) C = vec4(court.xyz * 1.2, 1.0);
        else C = court;

        if (mode == 2) {
            float dP1 = distance(P, p1);
            float dP2 = distance(P, p2);
            float dP3 = distance(P, p3);
            float dP4 = distance(P, p4);

            if (step(0.5, dP1) == 0.0) {
                if (step(0.4, dP1) == 0.0) C = vec4(1.0);
                else C = vec4(0.0);
            }
            else if (step(0.5, dP2) == 0.0) {
                if (step(0.4, dP2) == 0.0) C = vec4(1.0);
                else C = vec4(0.0);
            }
            else if (step(0.5, dP3) == 0.0) {
                if (step(0.4, dP3) == 0.0) C = vec4(1.0);
                else C = vec4(0.0);
            }
            else if (step(0.5, dP4) == 0.0) {
                if (step(0.4, dP4) == 0.0) C = vec4(1.0);
                else C = vec4(0.0);
            }
        }
        else if (mode == 3) {
            if (p1.x - 1.0 <= P.x && P.x <= p1.x + 1.0 && p1.y - 1.0 <= P.y && P.y <= p1.y + 1.0) {
                vec2 cordText = (P - p1) / 2.0 + 0.5;
                vec4 color = texture(player1, cordText);
                if (color.r > 0.5 || color.b < 0.5) C = color;
            }
            else if (p2.x - 1.0 <= P.x && P.x <= p2.x + 1.0 && p2.y - 1.0 <= P.y && P.y <= p2.y + 1.0) {
                vec2 cordText = (P - p2) / 2.0 + 0.5;
                vec4 color = texture(player1, cordText);
                if (color.r > 0.5 || color.b < 0.5) C = color;
            }
            else if (p3.x - 1.0 <= P.x && P.x <= p3.x + 1.0 && p3.y - 1.0 <= P.y && P.y <= p3.y + 1.0) {
                vec2 cordText = (p3 - P) / 2.0 + 0.5;
                vec4 color = texture(player1, cordText);
                if (color.r > 0.5 || color.b < 0.5) C = color;
            }
            else if (p4.x - 1.0 <= P.x && P.x <= p4.x + 1.0 && p4.y - 1.0 <= P.y && P.y <= p4.y + 1.0) {
                vec2 cordText = (p4 - P) / 2.0 + 0.5;
                vec4 color = texture(player1, cordText);
                if (color.r > 0.5 || color.b < 0.5) C = color;
            }
        }
    }
    fragColor = C;
}
