#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition;

// (sempre estarà en eye space)
uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform sampler2D positionMap;
uniform sampler2D normalMap1;
uniform int mode = 2;

void main()
{
    vec2 st = 0.496 * vertex.xy + vec2(0.5);
    vec3 v = texture(positionMap, st).xyz;

    if (mode == 0) frontColor = vec4(v, 1.0);
    else {
        vec3 normal2 = texture(normalMap1, st).xyz;
        normal2 = normal2 * 2 - 1.0;
        vec3 N2 = normalize(normalMatrix * normal2);
        if (mode == 1) frontColor = vec4(v * N2.z, 1.0);
        else if (mode == 2) {
            vec3 P_eye = (modelViewMatrix * vec4(v, 1.0)).xyz; //punt en eye space

            vec3 V = normalize(-P_eye); 		//vector unitari vertex cap a camera (0,0,0) - P_eye
            vec3 N = normalize(normalMatrix * normal2);  //vector normal com sempre
            vec3 L = normalize(lightPosition.xyz -P_eye);			//vector unitari cap a la font de la llum (0,0,0) - P_eye
            vec3 R = reflect(-L,N); 			//vector reflexio

            frontColor = vec4(matAmbient*lightAmbient + matDiffuse*lightDiffuse*max(0.0,dot(N,L)) + matSpecular*lightSpecular*pow(max(0.0, dot(R,V)),matShininess));
        }
        else {
            vec3 P_eye = (modelViewMatrix * vec4(v, 1.0)).xyz; //punt en eye space

            vec3 V = normalize(-P_eye); 		//vector unitari vertex cap a camera (0,0,0) - P_eye
            vec3 N = normalize(normalMatrix * normal2);  //vector normal com sempre
            vec3 L = normalize(lightPosition.xyz -P_eye);			//vector unitari cap a la font de la llum (0,0,0) - P_eye
            vec3 R = reflect(-L,N); 			//vector reflexio

            frontColor = vec4(matAmbient*lightAmbient + vec4(v, 1.0)*lightDiffuse*max(0.0,dot(N,L)) + matSpecular*lightSpecular*pow(max(0.0, dot(R,V)),matShininess));
        }
    }

    gl_Position = modelViewProjectionMatrix * vec4(v, 1.0);
}
