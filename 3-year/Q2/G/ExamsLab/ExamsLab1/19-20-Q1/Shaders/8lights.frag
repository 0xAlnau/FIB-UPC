#version 330 core

in vec4 frontColor;
in vec3 vert;
in vec3 norm;
out vec4 fragColor;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;

uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

uniform mat3 normalMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelViewMatrix;

void main()
{
    vec3 posLlums[8];
    vec4 diff = vec4(0.0);
    vec4 spec = vec4(0.0);
    float d = distance(boundingBoxMax, vec3(boundingBoxMax.x, 0.0, boundingBoxMax.z));
    posLlums[0] = vec3(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMin.z);
    posLlums[1] = vec3(boundingBoxMin.x, boundingBoxMin.y, boundingBoxMax.z);
    posLlums[2] = vec3(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMin.z);
    posLlums[3] = vec3(boundingBoxMin.x, boundingBoxMax.y, boundingBoxMax.z);
    posLlums[4] = vec3(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMin.z);
    posLlums[5] = vec3(boundingBoxMax.x, boundingBoxMin.y, boundingBoxMax.z);
    posLlums[6] = vec3(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMin.z);
    posLlums[7] = vec3(boundingBoxMax.x, boundingBoxMax.y, boundingBoxMax.z);

    vec3 P_eye = (modelViewMatrix * vec4(vert, 1.0)).xyz; //punt en eye space
    vec3 V = normalize(-P_eye); //vector unitari vertex cap a camera (0,0,0) - P_eye
    vec3 N = normalize(normalMatrix * norm); //vector normal com sempre

    for (int i = 0; i < 8; ++i) {
        vec3 L = normalize((viewMatrix * vec4(posLlums[i], 1.0)).xyz - P_eye); //[(0,0,0) - P_eye] o [lightPosition - P_eye]
        vec3 R = reflect(-L,N); //vector reflexio

        diff += matDiffuse*lightDiffuse*max(0.0,dot(N,L));
        spec += matSpecular*lightSpecular*pow(max(0.0, dot(R,V)),matShininess);
    }

    diff = diff / 2.0;
    fragColor = diff + spec;
}
