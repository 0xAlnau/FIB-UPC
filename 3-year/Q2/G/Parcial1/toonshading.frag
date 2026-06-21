#version 330 core

in vec4 frontColor;
in vec3 norm;
in vec3 vert;
out vec4 fragColor;

uniform int mode = 1;
uniform int n = 4;
uniform float outlineThreshold = 0.2;
uniform float edgeThreshold = 0.2;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;

uniform vec4 lightAmbient;
uniform vec4 matAmbient;
uniform vec4 lightDiffuse;
uniform vec4 matDiffuse;

void main()
{
    vec4 C;
    vec3 vEye = (modelViewMatrix * vec4(vert, 1.0)).xyz;
    vec3 nEye = normalize(normalMatrix * norm);
    vec3 L = normalize(-vEye);

    float intensitat = max(0.0, dot(nEye,L));
    if (intensitat <= 0.25) intensitat = 0.0;
    else if (intensitat <= 0.5) intensitat = 1.0/3.0;
    else if (intensitat <= 0.75) intensitat = 2.0/3.0;
    else if (intensitat <= 1.0) intensitat = 1.0;

    if (mode == 0) {
        C = matAmbient * lightAmbient + matDiffuse * lightDiffuse * intensitat;
    }
    else if (mode == 1) {
        float angle = dot(normalize(vEye),nEye);
        vec3 derX = dFdx(nEye);
        vec3 derY = dFdy(nEye);
        float magn = length(derX) + length(derY);

        if (angle < outlineThreshold) C = vec4(1.0); //fora
        if (magn > edgeThreshold) C = vec4(0.0); //dintre
    }
    else if (mode == 2) {
        vec4 C2 = matAmbient * lightAmbient + matDiffuse * lightDiffuse * intensitat;

        float angle = dot(normalize(vEye),nEye);
        vec3 derX = dFdx(nEye);
        vec3 derY = dFdy(nEye);
        float magn = length(derX) + length(derY);

        if (angle < outlineThreshold) C = vec4(1.0); //fora
        if (magn > edgeThreshold) C =  matAmbient * lightAmbient + matDiffuse * lightDiffuse * intensitat; //dintre
    }

    fragColor = C;
}
