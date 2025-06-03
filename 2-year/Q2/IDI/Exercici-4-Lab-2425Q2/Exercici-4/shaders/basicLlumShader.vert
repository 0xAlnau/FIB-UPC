#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3  matamb;
in vec3  matdiff;
in vec3  matspec;
in float matshin;

uniform mat4 TG;
uniform mat4 Proj;
uniform mat4 View;
uniform vec3 colorFocusCam;
uniform vec3 colorFocusEspe;
uniform vec3 posFocusEspe1;
uniform vec3 posFocusEspe2;

out vec3  fmatamb;
out vec3  fmatdiff;
out vec3  fmatspec;
out float fmatshin;
out vec3  fvertex;
out vec3  fnormal;
out vec3 L1;
out vec3 L2;
out vec3 L3;

void main()
{	
    vec4 vertexSCO = View * TG * vec4 (vertex, 1.0); //vertex
    fvertex = vertexSCO.xyz;

    vec3 posFocusCam = vec3(0.0, 0.0, 0.0); // 1

    vec4 posFocEs1 = View * vec4 (posFocusEspe1, 1.0); // 2

    vec4 posFocEs2 = View * vec4 (posFocusEspe2, 1.0); // 3

    mat3 NormalMatrix = inverse (transpose (mat3 (View * TG)));
    fnormal = NormalMatrix * normal;

    L1 = posFocusCam.xyz - fvertex;
    L2 = posFocEs1.xyz - fvertex;
    L3 = posFocEs2.xyz - fvertex;

    // Passem les dades al fragment shader
    fmatamb  = matamb;
    fmatdiff = matdiff;
    fmatspec = matspec;
    fmatshin = matshin;

    gl_Position = Proj * View * TG * vec4 (vertex, 1.0);
}
