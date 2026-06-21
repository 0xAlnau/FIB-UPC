#version 330 core

in vec4 frontColor;
in vec3 normEye;
in vec4 vertexEye;
in float fraccTextS;
in float fraccTextT;

out vec4 fragColor;

uniform vec4 lightSpecular;
uniform vec4 lightPosition;

uniform vec4 matSpecular;
uniform float matShininess;

uniform sampler2D colorMap;

uniform float time;

void main()
{
    vec3 V = normalize(-vertexEye.xyz);
    vec3 N = normalize(normEye);
    vec3 L = normalize(lightPosition.xyz - vertexEye.xyz);			//vector unitari cap a la font de la llum (0,0,0) - P_eye
    vec3 R = reflect(-L,N); 			//vector reflexio

    float m = mod(time, 2.0);
    float intensity = 0.8 * (1.0 - abs(m - 1.0));
    vec3 lightDiffuse = vec3(intensity);

    int frame = int(time / 2.0) % 12;
    int col = frame / 3;
    int row = frame % 3;

    float s = (fraccTextS + float(col)) / 4.0;
    float t = (fraccTextT + float(2 - row)) / 3.0;

    vec2 coordText = vec2(s,t);
    vec3 matDiffuse = texture(colorMap, coordText).rgb;
    vec3 colorDiff = vec3(matDiffuse*lightDiffuse*max(0.0,dot(N,L)));

    vec3 colorSpec = vec3(matSpecular*lightSpecular*pow(max(0.0, dot(R,V)),matShininess));

    vec3 colorTot = colorDiff + colorSpec;

    fragColor = vec4(colorTot, 1.0);
}
