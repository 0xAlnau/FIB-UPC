#version 330 core

out vec4 FragColor;

in vec3 matambSH;
in vec3 matdiffSH;
in vec3 matspecSH;
in float matshinSH;

in vec3 NormSCO2;
in vec3 L2;
in vec4 SCO_vertex2;

//uniforms per tots els models
uniform vec3 posFocus;
uniform vec3 colorFocus;

//coordenades
uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

// Valors per als components que necessitem del focus de llum
vec3 llumAmbient = vec3(0.2, 0.2, 0.2);



vec3 Ambient() {
    return llumAmbient * matambSH;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus)
{
    // Tant sols retorna el terme difús
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
    vec3 colRes = vec3(0);
    // Càlcul component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colFocus * matdiffSH * dot (L, NormSCO);
    return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec4 vertSCO, vec3 colFocus)
{
    // Tant sols retorna el terme especular!
    // Els vectors rebuts com a paràmetres (NormSCO i L) estan normalitzats
    vec3 colRes = vec3 (0);
    // Si la llum ve de darrera o el material és mate no fem res
    if ((dot(NormSCO,L) < 0) || (matshinSH == 0))
      return colRes;  // no hi ha component especular

    // Calculem R i V
    vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
    vec3 V = normalize(-vertSCO.xyz); // perquè la càmera està a (0,0,0) en SCO

    if (dot(R, V) < 0)
      return colRes;  // no hi ha component especular

    // Calculem i retornem la component especular
    float shine = pow(max(0.0, dot(R, V)), matshinSH);
    return (matspecSH * colFocus * shine);
}

//     *TG*   *view*   *proj*
//MODEL    SCA      SCO      CLIP
//  <-*NormalMatrix*->

void main()
{
	vec3 NormSCO3 = normalize(NormSCO2); //in nomes de lectura són
	vec3 L3 = normalize(L2);

	vec3 color = Ambient() + Difus(NormSCO3, L3, colorFocus) + Especular(NormSCO3, L3, SCO_vertex2, colorFocus); //matdiff no cal, es té en compte després
 	FragColor = vec4(color, 1);
}
