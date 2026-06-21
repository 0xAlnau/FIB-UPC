#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 projectionMatrix;

const float areamax = 0.0005;

void main( void )
{
	//demanen vector del triangle, no les seves coordenades del vertex!!!
	vec3 u = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
	vec3 v = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;

	vec3 vecArea = cross(u, v);
	float areaGran = length(vecArea);
	float area = areaGran / 2.0;
	area = area / areamax;

	vec4 color = mix(vec4(1.0,0.0,0.0,1.0), vec4(1.0,1.0,0.0,1.0), area);

	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = color;
		gl_Position = projectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
}
