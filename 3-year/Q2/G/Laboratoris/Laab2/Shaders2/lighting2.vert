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

void main()
{
    vec3 P_eye = (modelViewMatrix * vec4(vertex, 1.0)).xyz; //punt en eye space

    vec3 V = normalize(-P_eye); 		//vector unitari vertex cap a camera (0,0,0) - P_eye
    vec3 N = normalize(normalMatrix * normal);  //vector normal com sempre
    vec3 L = normalize(-P_eye);			//vector unitari cap a la font de la llum (0,0,0) - P_eye
    vec3 R = reflect(-L,N); 			//vector reflexio
    
    vec3 colorLlum = vec3(matAmbient*lightAmbient + matDiffuse*lightDiffuse*max(0.0,dot(N,L)) + matSpecular*lightSpecular*pow(max(0.0, dot(R,V)),matShininess));
    
    frontColor = vec4(colorLlum,1.0);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
