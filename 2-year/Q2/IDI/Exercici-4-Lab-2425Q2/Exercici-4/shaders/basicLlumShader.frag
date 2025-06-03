#version 330 core

in vec3  fmatamb;
in vec3  fmatdiff;
in vec3  fmatspec;
in float fmatshin;
in vec3  fvertex;
in vec3  fnormal;
in vec3 L1;
in vec3 L2;
in vec3 L3;

const vec3 llumAmbient = vec3(0.1, 0.1, 0.1);

uniform mat4 TG;
uniform mat4 Proj;
uniform mat4 View;
uniform vec3 colorFocusCam;
uniform vec3 colorFocusEspe;

out vec4 FragColor;


vec3 Ambient() {
  return llumAmbient*fmatamb;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme de Lambert!
  // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
  vec3 colRes = vec3(0);
  if (dot (L, NormSCO) > 0)
    colRes = colFocus * fmatdiff * dot (L, NormSCO);
  return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec3 vertSCO, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme especular!
  // Assumim que els vectors estan normalitzats
  vec3 colRes = vec3 (0);
  // Si la llum ve de darrera o el material és mate no fem res
  if ((dot(NormSCO,L) < 0) || (fmatshin == 0))
    return colRes;  // no hi ha component especular

  vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
  vec3 V = normalize(-vertSCO); // perquè la càmera està a (0,0,0) en SCO

  if (dot(R, V) < 0)
    return colRes;  // no hi ha component especular

  float shine = pow(max(0.0, dot(R, V)), fmatshin);
  return (colRes + fmatspec * colFocus * shine);
}

void main()
{
    vec3 fnorm2 = normalize(fnormal);
    vec3 L11 = normalize(L1);
    vec3 L22 = normalize(L2);
    vec3 L33 = normalize(L3);

    vec3 amb = Ambient();
    vec3 dif = Difus(fnorm2, L11, colorFocusCam) + Difus(fnorm2, L22, colorFocusEspe) + Difus(fnorm2, L33, colorFocusEspe);
    vec3 especul = Especular(fnorm2, L11, fvertex, colorFocusCam) + Especular(fnorm2, L22, fvertex, colorFocusEspe) + Especular(fnorm2, L33, fvertex, colorFocusEspe);

    vec3 color = amb + dif + especul;
    FragColor = vec4(color, 1);
}
