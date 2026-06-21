#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 vnormals[];
out vec4 gfrontColor;
out vec2 gtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform float time;

void main( void )
{

	if (gl_PrimitiveIDIn < 8) {
		float angle = radians(time);
		mat4 rotZ = mat4(vec4(cos(angle), sin(angle), 0.0, 0.0), vec4(-sin(angle), cos(angle), 0.0, 0.0), vec4(0.0,0.0,1.0,0.0), vec4(0.0,0.0,0.0,1.0));

		vec2 coordTex[4];
		coordTex[0] = vec2(1.0,1.0);
		coordTex[1] = vec2(1.0,0.0);
		coordTex[2] = vec2(0.0,1.0);
		coordTex[3] = vec2(0.0,0.0);

		int id = gl_PrimitiveIDIn;
		vec3 p[8];
		p[0] = vec3(-1.0); p[1] = vec3(1.0,-1.0,-1.0); p[2] = vec3(-1.0,1.0,-1.0); p[3] = vec3(1.0,1.0,-1.0);
		p[4] = vec3(-1.0,-1.0,1.0); p[5] = vec3(1.0,-1.0,1.0); p[6] = vec3(-1.0,1.0,1.0); p[7] = vec3(1.0);

		vec4 cares0[4];
		vec4 cares1[4];
		vec4 cares2[4];
		vec4 cares3[4];
		vec4 cares4[4];
		vec4 cares5[4];
		float l = 1.0;

		//amunt
		cares0[0] = vec4(p[id].x+l, p[id].y+l, p[id].z+l, 1.0);
		cares0[1] = vec4(p[id].x+l, p[id].y+l, p[id].z-l, 1.0);
		cares0[2] = vec4(p[id].x-l, p[id].y+l, p[id].z+l, 1.0);
		cares0[3] = vec4(p[id].x-l, p[id].y+l, p[id].z-l, 1.0);
		//sota
		cares1[0] = vec4(p[id].x+l, p[id].y-l, p[id].z+l, 1.0);
		cares1[1] = vec4(p[id].x+l, p[id].y-l, p[id].z-l, 1.0);
		cares1[2] = vec4(p[id].x-l, p[id].y-l, p[id].z+l, 1.0);
		cares1[3] = vec4(p[id].x-l, p[id].y-l, p[id].z-l, 1.0);
		//davant
		cares2[0] = vec4(p[id].x+l, p[id].y+l, p[id].z+l, 1.0);
		cares2[1] = vec4(p[id].x+l, p[id].y-l, p[id].z+l, 1.0);
		cares2[2] = vec4(p[id].x-l, p[id].y+l, p[id].z+l, 1.0);
		cares2[3] = vec4(p[id].x-l, p[id].y-l, p[id].z+l, 1.0);
		//darrere
		cares3[0] = vec4(p[id].x+l, p[id].y+l, p[id].z-l, 1.0);
		cares3[1] = vec4(p[id].x+l, p[id].y-l, p[id].z-l, 1.0);
		cares3[2] = vec4(p[id].x-l, p[id].y+l, p[id].z-l, 1.0);
		cares3[3] = vec4(p[id].x-l, p[id].y-l, p[id].z-l, 1.0);
		//left
		cares4[0] = vec4(p[id].x-l, p[id].y+l, p[id].z+l, 1.0);
		cares4[1] = vec4(p[id].x-l, p[id].y+l, p[id].z-l, 1.0);
		cares4[2] = vec4(p[id].x-l, p[id].y-l, p[id].z+l, 1.0);
		cares4[3] = vec4(p[id].x-l, p[id].y-l, p[id].z-l, 1.0);
		//right
		cares5[0] = vec4(p[id].x+l, p[id].y+l, p[id].z+l, 1.0);
		cares5[1] = vec4(p[id].x+l, p[id].y+l, p[id].z-l, 1.0);
		cares5[2] = vec4(p[id].x+l, p[id].y-l, p[id].z+l, 1.0);
		cares5[3] = vec4(p[id].x+l, p[id].y-l, p[id].z-l, 1.0);


		for( int i = 0 ; i < 4 ; i++ )
		{
			gtexCoord = coordTex[i];
			gfrontColor = vec4(1.0, 0.0, 0.0, 1.0);
			if (id < 4) gl_Position = modelViewProjectionMatrix * rotZ * cares0[i];
			else gl_Position = modelViewProjectionMatrix * cares0[i];
			EmitVertex();
		}
		EndPrimitive();

		for( int i = 0 ; i < 4 ; i++ )
		{
			gtexCoord = coordTex[i];
			gfrontColor = vec4(1.0, 0.6, 0.0, 1.0);
			if (id < 4) gl_Position = modelViewProjectionMatrix * rotZ * cares1[i];
			else gl_Position = modelViewProjectionMatrix * cares1[i];
			EmitVertex();
		}
		EndPrimitive();

		for( int i = 0 ; i < 4 ; i++ )
		{
			gtexCoord = coordTex[i];
			gfrontColor = vec4(1.0, 1.0, 0.0, 1.0);
			if (id < 4) gl_Position = modelViewProjectionMatrix * rotZ * cares2[i];
			else gl_Position = modelViewProjectionMatrix * cares2[i];
			EmitVertex();
		}
		EndPrimitive();

		for( int i = 0 ; i < 4 ; i++ )
		{
			gtexCoord = coordTex[i];
			gfrontColor = vec4(1.0);
			if (id < 4) gl_Position = modelViewProjectionMatrix * rotZ * cares3[i];
			else gl_Position = modelViewProjectionMatrix * cares3[i];
			EmitVertex();
		}
		EndPrimitive();

		for( int i = 0 ; i < 4 ; i++ )
		{
			gtexCoord = coordTex[i];
			gfrontColor = vec4(0.0, 1.0, 0.0, 1.0);
			if (id < 4) gl_Position = modelViewProjectionMatrix * rotZ * cares4[i];
			else gl_Position = modelViewProjectionMatrix * cares4[i];
			EmitVertex();
		}
		EndPrimitive();

		for( int i = 0 ; i < 4 ; i++ )
		{
			gtexCoord = coordTex[i];
			gfrontColor = vec4(0.0, 0.0, 1.0, 1.0);
			if (id < 4) gl_Position = modelViewProjectionMatrix * rotZ * cares5[i];
			else gl_Position = modelViewProjectionMatrix * cares5[i];
			EmitVertex();
		}
		EndPrimitive();
	}

}
