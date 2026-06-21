#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
out vec2 gtexCoord;
out vec4 isAmunt;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float step = 0.5;

void main( void )
{
	vec4 v0 = gl_in[0].gl_Position;
	vec4 v1 = gl_in[1].gl_Position;
	vec4 v2 = gl_in[2].gl_Position;

	vec3 baricentre = (vec3(v0) + vec3(v1) + vec3(v2)) / 3.0;
	//estem quantitzant!!
	vec3 punt = step * round(baricentre / step);
	float ms = step / 2.0;

	vec4 colorMig = (vfrontColor[0] + vfrontColor[1] + vfrontColor[2]) / 3.0;

	vec4 colorsLego[5] = vec4[](
		vec4(1.0, 0.0, 0.0, 1.0), // R
		vec4(0.0, 1.0, 0.0, 1.0), // G
		vec4(0.0, 0.0, 1.0, 1.0), // B
		vec4(0.0, 1.0, 1.0, 1.0), // C
		vec4(1.0, 1.0, 0.0, 1.0)  // Y
	);

	vec4 colorFinal = colorsLego[0];
	float min_dist = distance(colorMig, colorsLego[0]);
	//comprova si alguna distancia es més petita de la que ja hi ha
	for(int c = 1; c < 5; c++) {
		float d = distance(colorMig, colorsLego[c]);
		if(d < min_dist) {
			min_dist = d;
			colorFinal = colorsLego[c];
		}
	}

	vec4 cares0[4];
	vec4 cares1[4];
	vec4 cares2[4];
	vec4 cares3[4];
	vec4 cares4[4];
	vec4 cares5[4];

	//amunt
	cares0[0] = vec4(punt.x+ms, punt.y+ms, punt.z+ms, 1.0);
	cares0[1] = vec4(punt.x+ms, punt.y+ms, punt.z-ms, 1.0);
	cares0[2] = vec4(punt.x-ms, punt.y+ms, punt.z+ms, 1.0);
	cares0[3] = vec4(punt.x-ms, punt.y+ms, punt.z-ms, 1.0);

	//abaix
	cares1[0] = vec4(punt.x+ms, punt.y-ms, punt.z+ms, 1.0);
	cares1[1] = vec4(punt.x+ms, punt.y-ms, punt.z-ms, 1.0);
	cares1[2] = vec4(punt.x-ms, punt.y-ms, punt.z+ms, 1.0);
	cares1[3] = vec4(punt.x-ms, punt.y-ms, punt.z-ms, 1.0);

	//front
	cares2[0] = vec4(punt.x+ms, punt.y-ms, punt.z+ms, 1.0);
	cares2[1] = vec4(punt.x+ms, punt.y+ms, punt.z+ms, 1.0);
	cares2[2] = vec4(punt.x-ms, punt.y-ms, punt.z+ms, 1.0);
	cares2[3] = vec4(punt.x-ms, punt.y+ms, punt.z+ms, 1.0);

	//back
	cares3[0] = vec4(punt.x+ms, punt.y-ms, punt.z-ms, 1.0);
	cares3[1] = vec4(punt.x+ms, punt.y+ms, punt.z-ms, 1.0);
	cares3[2] = vec4(punt.x-ms, punt.y-ms, punt.z-ms, 1.0);
	cares3[3] = vec4(punt.x-ms, punt.y+ms, punt.z-ms, 1.0);

	//left
	cares4[0] = vec4(punt.x-ms, punt.y-ms, punt.z+ms, 1.0);
	cares4[1] = vec4(punt.x-ms, punt.y+ms, punt.z+ms, 1.0);
	cares4[2] = vec4(punt.x-ms, punt.y-ms, punt.z-ms, 1.0);
	cares4[3] = vec4(punt.x-ms, punt.y+ms, punt.z-ms, 1.0);

	//right
	cares5[0] = vec4(punt.x+ms, punt.y-ms, punt.z+ms, 1.0);
	cares5[1] = vec4(punt.x+ms, punt.y+ms, punt.z+ms, 1.0);
	cares5[2] = vec4(punt.x+ms, punt.y-ms, punt.z-ms, 1.0);
	cares5[3] = vec4(punt.x+ms, punt.y+ms, punt.z-ms, 1.0);

	vec3 n_amunt = normalize(normalMatrix * vec3(0.0, 1.0, 0.0));
	vec3 n_abaix = normalize(normalMatrix * vec3(0.0, -1.0, 0.0));
	vec3 n_front = normalize(normalMatrix * vec3(0.0, 0.0, 1.0));
	vec3 n_back  = normalize(normalMatrix * vec3(0.0, 0.0, -1.0));
	vec3 n_left  = normalize(normalMatrix * vec3(-1.0, 0.0, 0.0));
	vec3 n_right = normalize(normalMatrix * vec3(1.0, 0.0, 0.0));

	for( int i = 0 ; i < 4 ; i++ )
	{
		isAmunt = vec4(1.0);
		if (i == 0) gtexCoord = vec2(1.0,1.0); //cal fer això ja que només són 4 vertexs, ordre importa!!
		else if (i == 1) gtexCoord = vec2(1.0,0.0);
		else if (i == 2) gtexCoord = vec2(0.0, 1.0);
		else gtexCoord = vec2(0.0,0.0);
		gfrontColor = colorFinal * n_amunt.z;
		gl_Position = modelViewProjectionMatrix * cares0[i];
		EmitVertex();
	}
    EndPrimitive();

	for( int i = 0 ; i < 4 ; i++ )
	{
		isAmunt = vec4(0.0);
		gfrontColor = colorFinal * n_abaix.z;
		gl_Position = modelViewProjectionMatrix * cares1[i];
		EmitVertex();
	}
	EndPrimitive();

	for( int i = 0 ; i < 4 ; i++ )
	{
		isAmunt = vec4(0.0);
		gfrontColor = colorFinal * n_front.z;
		gl_Position = modelViewProjectionMatrix * cares2[i];
		EmitVertex();
	}
	EndPrimitive();

	for( int i = 0 ; i < 4 ; i++ )
	{
		isAmunt = vec4(0.0);
		gfrontColor = colorFinal * n_back.z;
		gl_Position = modelViewProjectionMatrix * cares3[i];
		EmitVertex();
	}
	EndPrimitive();

	for( int i = 0 ; i < 4 ; i++ )
	{
		isAmunt = vec4(0.0);
		gfrontColor = colorFinal * n_left.z;
		gl_Position = modelViewProjectionMatrix * cares4[i];
		EmitVertex();
	}
	EndPrimitive();

	for( int i = 0 ; i < 4 ; i++ )
	{
		isAmunt = vec4(0.0);
		gfrontColor = colorFinal * n_right.z;
		gl_Position = modelViewProjectionMatrix * cares5[i];
		EmitVertex();
	}
	EndPrimitive();
}
