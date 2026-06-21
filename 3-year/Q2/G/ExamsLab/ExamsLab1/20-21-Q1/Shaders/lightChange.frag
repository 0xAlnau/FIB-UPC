#version 330 core

in vec4 frontColor;
in vec3 vEye;
in vec3 nEye;
in vec2 vtexCoord;
out vec4 fragColor;

vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition;

vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

uniform float time;
uniform sampler2D colorMap;

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
    float time2 = mod(time, 2.0);
    if (time2 < 1.0) lightDiffuse = mix(vec4(vec3(0.0), 1.0), vec4(vec3(0.8), 1.0), time2);
    else lightDiffuse = mix(vec4(vec3(0.8), 1.0), vec4(vec3(0.0), 1.0), time2 - 1.0);

    int frame = int(time / 2.0) % 12;
    int row = frame % 3; // es / perque anem de esq a dre, si es amunt a abais usem %
    int col = frame / 3; //
    float offsetX = float(col) * (1.0/4.0);
    float offsetY = float(2 - row) * (1.0/3.0);
    // canvi_base + quin_quadre
    vec2 vtexCoordNou = vec2(vtexCoord.s * (1.0/4.0) + offsetX, vtexCoord.t * (1.0/3.0) + offsetY);
    matDiffuse = texture(colorMap, vtexCoordNou);

    vec3 V = -vEye; //vector unitari vertex cap a camera (0,0,0) - P_eye
    vec3 N = nEye; //vector normal com sempre
    vec3 L = lightPosition.xyz - vEye; //[(0,0,0) - P_eye] o [lightPosition - P_eye]

    fragColor = light(N,V,L);
}
