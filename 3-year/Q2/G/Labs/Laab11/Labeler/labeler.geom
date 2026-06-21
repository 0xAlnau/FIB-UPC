#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
out vec2 gtexCoord;

uniform float size = 0.07;
uniform float depth = -0.01;
uniform mat4 modelViewProjectionMatrix;

void main( void )
{
	vec4 v0 = gl_in[0].gl_Position;
	vec4 v1 = gl_in[1].gl_Position;
	vec4 v2 = gl_in[2].gl_Position;

	vec3 baricentre = (vec3(v0) + vec3(v1) + vec3(v2)) / 3.0;

	vec4 baricentreClip = modelViewProjectionMatrix * vec4(baricentre, 1.0);
	vec3 baricentreNDC = baricentreClip.xyz / baricentreClip.w;
	vec3 C = baricentreNDC;

	vec4 triangle1[3];
	vec4 triangle2[3];

	triangle1[0] = vec4(C.x + size, C.y + size, C.z + depth, 1.0);
	triangle1[1] = vec4(C.x + size, C.y - size, C.z + depth, 1.0);
	triangle1[2] = vec4(C.x - size, C.y + size, C.z + depth, 1.0);

	triangle2[0] = vec4(C.x - size, C.y + size, C.z + depth, 1.0);
	triangle2[1] = vec4(C.x + size, C.y - size, C.z + depth, 1.0);
	triangle2[2] = vec4(C.x - size, C.y - size, C.z + depth, 1.0);

	vec2 tex1[3] = vec2[](vec2(7.0, 7.0), vec2(7.0, 0.0), vec2(0.0, 7.0));
	vec2 tex2[3] = vec2[](vec2(0.0, 7.0), vec2(7.0, 0.0), vec2(0.0, 0.0));

	//plane.obj
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();

	//triangle1
	for( int i = 0 ; i < 3 ; i++ )
	{
		gtexCoord = tex1[i];
		gfrontColor = vec4(1.0, 1.0, 0.0, 1.0);
		gl_Position = triangle1[i];
		EmitVertex();
	}
    EndPrimitive();

	//triangle2
	for( int i = 0 ; i < 3 ; i++ )
	{
		gtexCoord = tex2[i];
		gfrontColor = vec4(1.0, 1.0, 0.0, 1.0);
		gl_Position = triangle2[i];
		EmitVertex();
	}
    EndPrimitive();
}
