#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform int mode = 2;
uniform vec4 matAmbient, matDiffuse, matSpecular;
uniform float matShininess;
uniform vec4 lightAmbient, lightDiffuse, lightSpecular, lightPosition;
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
    matAmbient  * lightAmbient +
    matDiffuse  * lightDiffuse  * Idiff +
    matSpecular * lightSpecular * Ispec;
}

void main()
{
    float d = distance(vtexCoord, vec2(0.0, 0.0));
    if (step(1.0, d) == 0.0) {
        if (mode >= 1) {
            float s = vtexCoord.s;
            float t = vtexCoord.t;
            vec3 P = vec3(s, t, sqrt(1 - (s*s) - (t*t)));
            vec3 N = P;

            if (mode == 2) {
                vec3 Peye = (modelViewMatrix * vec4(P, 1.0)).xyz;
                N = normalMatrix * N;
                vec3 V = -Peye;
                vec3 L = lightPosition.xyz - Peye;
                fragColor = light(N,V,L);
            }
            else fragColor = vec4(vec3(N.z), 1.0);

        }
        else fragColor = vec4(vec3(0.0), 1.0);
    }
    else discard;
}
