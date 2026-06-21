#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
out vec2 gtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform int mode = 1;
uniform float cut = -0.25;

void main( void )
{
	float l = 0.08;
	vec4 v0 = gl_in[0].gl_Position;
	vec4 v1 = gl_in[1].gl_Position;
	vec4 v2 = gl_in[2].gl_Position;

	vec2 texCoord[4];
	texCoord[0] = vec2(1.0,1.0); texCoord[1] = vec2(1.0,0.0);
	texCoord[2] = vec2(0.0,1.0); texCoord[3] = vec2(0.0,0.0);

	vec3 C = (vec3(v0) + vec3(v1) + vec3(v2)) / 3.0;

	if (mode == 3) {
		if (C.x < -0.25 || C.y < -0.25 || C.z < -0.25) {
			vec4 cares0[4], cares1[4], cares2[4], cares3[4], cares4[4], cares5[4];
			//amunt
			cares0[0] = vec4(C.x+l, C.y+l, C.z+l, 1.0);
			cares0[1] = vec4(C.x+l, C.y+l, C.z-l, 1.0);
			cares0[2] = vec4(C.x-l, C.y+l, C.z+l, 1.0);
			cares0[3] = vec4(C.x-l, C.y+l, C.z-l, 1.0);
			//abaix
			cares1[0] = vec4(C.x+l, C.y-l, C.z+l, 1.0);
			cares1[1] = vec4(C.x+l, C.y-l, C.z-l, 1.0);
			cares1[2] = vec4(C.x-l, C.y-l, C.z+l, 1.0);
			cares1[3] = vec4(C.x-l, C.y-l, C.z-l, 1.0);
			//front
			cares2[0] = vec4(C.x+l, C.y+l, C.z+l, 1.0);
			cares2[1] = vec4(C.x+l, C.y-l, C.z+l, 1.0);
			cares2[2] = vec4(C.x-l, C.y+l, C.z+l, 1.0);
			cares2[3] = vec4(C.x-l, C.y-l, C.z+l, 1.0);
			//back
			cares3[0] = vec4(C.x+l, C.y+l, C.z-l, 1.0);
			cares3[1] = vec4(C.x+l, C.y-l, C.z-l, 1.0);
			cares3[2] = vec4(C.x-l, C.y+l, C.z-l, 1.0);
			cares3[3] = vec4(C.x-l, C.y-l, C.z-l, 1.0);
			//left
			cares4[0] = vec4(C.x-l, C.y+l, C.z+l, 1.0);
			cares4[1] = vec4(C.x-l, C.y+l, C.z-l, 1.0);
			cares4[2] = vec4(C.x-l, C.y-l, C.z+l, 1.0);
			cares4[3] = vec4(C.x-l, C.y-l, C.z-l, 1.0);
			//right
			cares5[0] = vec4(C.x+l, C.y+l, C.z+l, 1.0);
			cares5[1] = vec4(C.x+l, C.y+l, C.z-l, 1.0);
			cares5[2] = vec4(C.x+l, C.y-l, C.z+l, 1.0);
			cares5[3] = vec4(C.x+l, C.y-l, C.z-l, 1.0);

			vec4 color = vec4((C + 1.0) / 2.0, 1.0);

			for( int i = 0 ; i < 4 ; i++ )
			{
				gtexCoord = texCoord[i];
				gfrontColor = color;
				gl_Position = modelViewProjectionMatrix * cares0[i];
				EmitVertex();
			}
			EndPrimitive();

			for( int i = 0 ; i < 4 ; i++ )
			{
				gtexCoord = texCoord[i];
				gfrontColor = color;
				gl_Position = modelViewProjectionMatrix * cares1[i];
				EmitVertex();
			}
			EndPrimitive();

			for( int i = 0 ; i < 4 ; i++ )
			{
				gtexCoord = texCoord[i];
				gfrontColor = color;
				gl_Position = modelViewProjectionMatrix * cares2[i];
				EmitVertex();
			}
			EndPrimitive();

			for( int i = 0 ; i < 4 ; i++ )
			{
				gtexCoord = texCoord[i];
				gfrontColor = color;
				gl_Position = modelViewProjectionMatrix * cares3[i];
				EmitVertex();
			}
			EndPrimitive();

			for( int i = 0 ; i < 4 ; i++ )
			{
				gtexCoord = texCoord[i];
				gfrontColor = color;
				gl_Position = modelViewProjectionMatrix * cares4[i];
				EmitVertex();
			}
			EndPrimitive();

			for( int i = 0 ; i < 4 ; i++ )
			{
				gtexCoord = texCoord[i];
				gfrontColor = color;
				gl_Position = modelViewProjectionMatrix * cares5[i];
				EmitVertex();
			}
			EndPrimitive();
		}
	}
	else {
		vec4 cares0[4], cares1[4], cares2[4], cares3[4], cares4[4], cares5[4];
		//amunt
		cares0[0] = vec4(C.x+l, C.y+l, C.z+l, 1.0);
		cares0[1] = vec4(C.x+l, C.y+l, C.z-l, 1.0);
		cares0[2] = vec4(C.x-l, C.y+l, C.z+l, 1.0);
		cares0[3] = vec4(C.x-l, C.y+l, C.z-l, 1.0);
		//abaix
		cares1[0] = vec4(C.x+l, C.y-l, C.z+l, 1.0);
		cares1[1] = vec4(C.x+l, C.y-l, C.z-l, 1.0);
		cares1[2] = vec4(C.x-l, C.y-l, C.z+l, 1.0);
		cares1[3] = vec4(C.x-l, C.y-l, C.z-l, 1.0);
		//front
		cares2[0] = vec4(C.x+l, C.y+l, C.z+l, 1.0);
		cares2[1] = vec4(C.x+l, C.y-l, C.z+l, 1.0);
		cares2[2] = vec4(C.x-l, C.y+l, C.z+l, 1.0);
		cares2[3] = vec4(C.x-l, C.y-l, C.z+l, 1.0);
		//back
		cares3[0] = vec4(C.x+l, C.y+l, C.z-l, 1.0);
		cares3[1] = vec4(C.x+l, C.y-l, C.z-l, 1.0);
		cares3[2] = vec4(C.x-l, C.y+l, C.z-l, 1.0);
		cares3[3] = vec4(C.x-l, C.y-l, C.z-l, 1.0);
		//left
		cares4[0] = vec4(C.x-l, C.y+l, C.z+l, 1.0);
		cares4[1] = vec4(C.x-l, C.y+l, C.z-l, 1.0);
		cares4[2] = vec4(C.x-l, C.y-l, C.z+l, 1.0);
		cares4[3] = vec4(C.x-l, C.y-l, C.z-l, 1.0);
		//right
		cares5[0] = vec4(C.x+l, C.y+l, C.z+l, 1.0);
		cares5[1] = vec4(C.x+l, C.y+l, C.z-l, 1.0);
		cares5[2] = vec4(C.x+l, C.y-l, C.z+l, 1.0);
		cares5[3] = vec4(C.x+l, C.y-l, C.z-l, 1.0);

		vec4 color = vec4((C + 1.0) / 2.0, 1.0);

		for( int i = 0 ; i < 4 ; i++ )
		{
			gtexCoord = texCoord[i];
			gfrontColor = color;
			gl_Position = modelViewProjectionMatrix * cares0[i];
			EmitVertex();
		}
		EndPrimitive();

		for( int i = 0 ; i < 4 ; i++ )
		{
			gtexCoord = texCoord[i];
			gfrontColor = color;
			gl_Position = modelViewProjectionMatrix * cares1[i];
			EmitVertex();
		}
		EndPrimitive();

		for( int i = 0 ; i < 4 ; i++ )
		{
			gtexCoord = texCoord[i];
			gfrontColor = color;
			gl_Position = modelViewProjectionMatrix * cares2[i];
			EmitVertex();
		}
		EndPrimitive();

		for( int i = 0 ; i < 4 ; i++ )
		{
			gtexCoord = texCoord[i];
			gfrontColor = color;
			gl_Position = modelViewProjectionMatrix * cares3[i];
			EmitVertex();
		}
		EndPrimitive();

		for( int i = 0 ; i < 4 ; i++ )
		{
			gtexCoord = texCoord[i];
			gfrontColor = color;
			gl_Position = modelViewProjectionMatrix * cares4[i];
			EmitVertex();
		}
		EndPrimitive();

		for( int i = 0 ; i < 4 ; i++ )
		{
			gtexCoord = texCoord[i];
			gfrontColor = color;
			gl_Position = modelViewProjectionMatrix * cares5[i];
			EmitVertex();
		}
		EndPrimitive();
	}
}
