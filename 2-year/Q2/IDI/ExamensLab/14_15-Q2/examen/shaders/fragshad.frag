#version 330 core

in vec3 fcolor;
out vec4 FragColor;

in vec3 fmatamb;
in vec3 fmatdiff;
in vec3 fmatspec;
in float fmatshin;

in vec3 L;
in vec3 normalSCO;
in vec4 vertexSCO;

vec3 colFocus = vec3(1,1,1);
vec3 llumAmbient = vec3(0.1, 0.1, 0.1);
vec3 posFocus = vec3(0,0,0);

vec3 Lambert (vec3 NormSCO, vec3 L)
{
	// S'assumeix que els vectors que es reben com a paràmetres estan normalitzats

	// Inicialitzem color a component ambient
	vec3 colRes = llumAmbient * fmatamb;

	// Afegim component difusa, si n'hi ha
	if (dot (L, NormSCO) > 0)
		colRes = colRes + colFocus * fmatdiff * dot (L, NormSCO);
	return (colRes);
}

vec3 Phong (vec3 NormSCO, vec3 L, vec4 vertSCO)
{
	// Els vectors estan normalitzats

	// Inicialitzem color a Lambert
	vec3 colRes = Lambert (NormSCO, L);

	// Calculem R i V
	if (dot(NormSCO,L) < 0)
		return colRes;  // no hi ha component especular

		vec3 R = reflect(-L, NormSCO); // equival a: normalize (2.0*dot(NormSCO,L)*NormSCO - L);
	vec3 V = normalize(-vertSCO.xyz);

	if ((dot(R, V) < 0) || (fmatshin == 0))
		return colRes;  // no hi ha component especular

		// Afegim la component especular
		float shine = pow(max(0.0, dot(R, V)), fmatshin);
	return (colRes + fmatspec * colFocus * shine);
}

void main()
{	
	vec3 Lf = normalize(L);
	vec3 normalSCOf = normalize(normalSCO);

	FragColor = vec4(Phong(normalSCOf, Lf, vertexSCO),1);
}
