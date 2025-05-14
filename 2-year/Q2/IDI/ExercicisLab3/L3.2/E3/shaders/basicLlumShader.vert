#version 330 core

//part dels atributs de cada model
in vec3 vertex;
in vec3 normal;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

out vec3 matambSH;
out vec3 matdiffSH;
out vec3 matspecSH;
out float matshinSH;

out vec3 NormSCO2;
out vec3 L2;
out vec4 SCO_vertex2;

//uniforms per tots els models
uniform vec3 posFocus;
uniform vec3 colorFocus;
uniform float focus_escena;

//coordenades
uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

void main()
{	
    // PRIMER NORMALITZAR nomes: normal i L!!!! (les fletxes que surten rebotant només)
    mat3 NormalMatrix = inverse (transpose (mat3 (view * TG)));

    SCO_vertex2 = view * TG * vec4 (vertex, 1.0);

    vec4 SCO_focus;
    if (focus_escena == 1.0) SCO_focus = view * vec4 (posFocus, 1.0);
    else vec4 SCO_focus = vec4(0.0, 0.0, 0.0, 0.0);

    vec3 VertexSCO = SCO_vertex2.xyz;//aquest NO normalitzar

    NormSCO2 = NormalMatrix * normal;
    NormSCO2 = normalize(NormSCO2);

    vec3 FocusSCO = SCO_focus.xyz;

    L2 = FocusSCO - VertexSCO; // Focus - Vertex !!!!
    L2 = normalize(L2);

    matambSH = matamb;
    matdiffSH = matdiff;
    matspecSH = matspec;
    matshinSH = matshin;

    gl_Position = proj * view * TG * vec4 (vertex, 1.0);
}
