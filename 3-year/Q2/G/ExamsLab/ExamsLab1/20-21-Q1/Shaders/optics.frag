#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
in vec3 v;
out vec4 fragColor;

uniform sampler2D tex;
uniform float time;
const float eta = 1.7;

// Necesario para calcular la posición de la cámara en Object Space
uniform mat4 modelViewMatrixInverse;

void trace(vec3 V, out vec3 P, out vec3 dir) {
    // 1. Rayo incidente desde la cámara hasta V
    vec3 cameraPos = (modelViewMatrixInverse * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
    vec3 I = normalize(V - cameraPos);

    // 2. Primera refracción (Entrada a la esfera)
    vec3 T1 = refract(I, V, 1.0 / eta);

    // 3. Calcular el punto de salida (P) en la superficie posterior
    float t = -2.0 * dot(V, T1);
    P = V + t * T1;

    // 4. Segunda refracción (Salida de la esfera)
    dir = refract(T1, -P, eta);
}

void main()
{
    if (v.z < -1.1) fragColor = texture(tex, vtexCoord); //sabem rodona entre [-1,1]
    else {
        vec3 P, dir;
        trace(v, P, dir);
        if (length(dir) == 0.0) fragColor = vec4(0.97);
        else {
            // Posición actual del plano animado en el eje Z
            float planoZ = -1.5 - pow(sin(time), 2.0);

            // Calcular a qué distancia (lambda) el rayo impacta con el plano infinito
            // Ecuación de la recta: hit.z = P.z + lambda * dir.z = planoZ
            float lambda = (planoZ - P.z) / dir.z;

            // Si lambda es positivo, el rayo viaja hacia adelante (hacia el plano)
            if (lambda > 0.0) {
                // Calculamos las coordenadas 3D del impacto exacto
                vec3 hit = P + lambda * dir;

                // El plano mide 4 unidades y está centrado, sus límites son de -2.0 a 2.0 en X e Y
                if (hit.x >= -2.0 && hit.x <= 2.0 && hit.y >= -2.0 && hit.y <= 2.0) {

                    // Mapear el punto de impacto del rango [-2, 2] al rango de textura [0, 1]
                    vec2 hitTexCoord;
                    hitTexCoord.x = (hit.x + 2.0) / 4.0;
                    hitTexCoord.y = (hit.y + 2.0) / 4.0;

                    // Leemos el color de la textura en el punto que ha visto el rayo
                    fragColor = texture(tex, hitTexCoord);

                } else {
                    // El rayo golpea el plano infinito, pero fuera del cuadrado físico de 4x4
                    fragColor = vec4(0.97);
                }
            } else {
                // El rayo sale de la esfera pero apunta hacia otro lado (nunca cruzará el plano)
                fragColor = vec4(0.97);
            }
        }

    }
}
