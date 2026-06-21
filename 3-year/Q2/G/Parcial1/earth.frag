#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
in vec3 vert;

out vec4 fragColor;

uniform mat4 modelViewMatrix;

uniform float time;
uniform vec4 lightPosition;
uniform sampler2D dayMap;
uniform sampler2D nightMap1;
uniform sampler2D normalMap2;
uniform sampler2D cloudsMap3;

void main()
{
    vec2 earthUV = vtexCoord;
    earthUV.s += time*0.01;
    vec2 cloudUV = vtexCoord;
    cloudUV.s += time*0.02;

    vec3 normal = texture(normalMap2, vtexCoord).xyz;

    normal.z = normal.z * 0.75;


    vec3 N = normal;
    vec3 T = cross(vec3(0.0,1.0,0.0), N);
    vec3 B = cross(T, N);

    mat3 TBN = mat3(T, B, N);

    vec3 normGeom = texture(normalMap2, vtexCoord).xyz;
    normGeom = TBN * normGeom;

    vec3 P_eye = (modelViewMatrix * vec4(vert, 1.0)).xyz; //punt en eye space
    vec3 L = normalize(lightPosition.xyz - P_eye);
    float lightIntensity = smoothstep(-0.25, 0.25, dot(normGeom, L));

    vec4 colD = texture(dayMap, earthUV);
    vec4 colN = texture(nightMap1, earthUV);
    vec4 colE = mix(colD, colN, lightIntensity);

    vec4 ombra = texture(cloudsMap3, vec2(cloudUV.s + 0.005, cloudUV.t));

    vec4 colNuv = texture(cloudsMap3, cloudUV);
    vec4 C = mix(colE, colNuv, dot(normGeom, L));

    fragColor = C;
}
