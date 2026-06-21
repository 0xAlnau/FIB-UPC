#version 330 core

in vec4 frontColor;
in vec3 vertex2;
in vec3 normal2;
out vec4 fragColor;

uniform int n = 4;
const float pi = 3.141592;

uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition;

uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

vec4 light(vec3 N, vec3 V, vec3 L)
{
    N = normalize(N); V = normalize(V); L = normalize(L);
    vec3 R = normalize( 2.0*dot(N,L)*N-L );
    float NdotL = max( 0.0, dot( N,L ) );
    float RdotV = max( 0.0, dot( R,V ) );
    float Idiff = NdotL;
    float Ispec = 0;
    if (NdotL>0) Ispec = pow( RdotV, matShininess );
    return
    matDiffuse * lightDiffuse * Idiff +
    matSpecular * lightSpecular * Ispec;
}

void main()
{
    int radi = 10;
    vec3 P_eye = (modelViewMatrix * vec4(vertex2, 1.0)).xyz; //punt en eye space
    vec3 P_llum = vec3(10.0,0.0,0.0);
    float angle = (2*pi) / float(n);
    vec3 V = normalize(-P_eye); //vector unitari vertex cap a camera (0,0,0) - P_eye
    vec3 N = normalize(normalMatrix * normal2); //vector normal com sempre
    vec4 difusa[10];
    vec4 specul[10];

    for (int i = 0; i < n; ++i) {
        P_llum.x = radi * cos(float(i) * angle);
        P_llum.y = radi * sin(float(i) * angle);
        vec3 L = normalize(P_llum - P_eye); //[(0,0,0) - P_eye] o [lightPosition - P_eye]
        vec3 R = reflect(-L,N);
        difusa[i] = matDiffuse*lightDiffuse*max(0.0,dot(N,L));
        specul[i] = matSpecular*lightSpecular*pow(max(0.0, dot(R,V)),matShininess);

    }

    vec4 partDif = vec4(0.0);
    vec4 partEsp = vec4(0.0);

    for (int i = 0; i < n; ++i) partDif += difusa[i];
    for (int i = 0; i < n; ++i) partEsp += specul[i];

    partDif = partDif / sqrt(float(n));

    fragColor = partDif + partEsp;
}
