#version 330 core

in vec4 frontColor;
in vec3 v;
in vec3 norm;
out vec4 fragColor;

uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition;

 // (sempre estarà en eye space)
uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

uniform int n = 4;
const float pi = 3.141592;
const float radi = 10.0;

void main()
{
    vec3 N = normalize(norm);
    vec3 V = normalize(-v);
    vec4 novaLlum = vec4(0.0);

    for (int i = 0; i < n; ++i) {
        float angle = float(i) * (2.0 * pi) / float(n);
        vec3 LlumPos = vec3(radi * cos(angle), radi * sin(angle), 0.0);

        vec3 L = normalize(LlumPos - v);
        vec3 R = reflect(-L, N);

        float dotNL = max(0.0, dot(N, L));
        float dotRV = max(0.0, dot(R, V));

        // Difusa: se divide por sqrt(n)
        novaLlum += (matDiffuse * lightDiffuse * dotNL) / sqrt(float(n));

        // Especular: solo si hay contribución difusa (evita artefactos en el fandisk)
        if (dotNL > 0.0) {
            novaLlum += matSpecular * lightSpecular * pow(dotRV, matShininess);
        }
    }

    fragColor = vec4(novaLlum.rgb, 1.0);
}
