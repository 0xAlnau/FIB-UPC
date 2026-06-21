#version 330 core

in vec4 frontColor;
in vec3 v;
out vec4 fragColor;

uniform float time;
uniform vec2 viewport;
uniform mat4 projectionMatrixInverse;
uniform mat4 viewMatrixInverse;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

uniform int mode = 0;

uniform vec3 lightDir = vec3(0.348, 0.87, -0.348); // en world space
uniform float shininess = 50.0;
uniform sampler2D poolFloor;

vec2 getHeightDerivative(vec2 p)
{
	vec2 ds1 = vec2(cos(time + 10.0 * p.x) * cos(time + 10.0 * p.y) * 10.0,
			        -sin(time + 10.0 * p.x) * sin(time + 10.0 * p.y) * 10.0);
	vec2 ds2 = vec2(cos(-2.4*time + 27.0 * p.x) * cos(2.7 * time + 35.0 * p.y) * 27.0,
					-sin(-2.4*time + 27.0 * p.x) * sin(2.7 * time + 35.0 * p.y) * 35.0);
	vec2 ds3 = vec2(cos(2.2 * time + 66.0 * p.x) * cos(2.0 * time + 60.0 * p.y) * 66.0,
					-sin(2.2 * time + 66.0 * p.x) * cos(2.0 * time + 60.0 * p.y) * 60.0);

	return 0.04 * (ds1 + ds2*0.3 + ds3*0.05);
}

void main()
{
    vec2 p = vec2(v.x, v.z);
    vec2 dxz = getHeightDerivative(p);
    vec3 N = normalize(vec3(-dxz.x, 1.0, -dxz.y));

    vec3 P_wor = v;
    vec3 obs_wor = vec3(inverse(viewMatrix)[3]);
    vec3 V = normalize(obs_wor-P_wor);
    vec3 L = normalize(lightDir-P_wor);
    vec3 R = normalize( 2.0*dot(N,L)*N-L );

    vec3 col = vec3(pow(max(0.0, dot(R,V)), shininess));

    if (mode == 1) {
        vec3 Rprim = refract(-V, N, 0.75);
        vec3 p2 = v - Rprim * ((0.2 + v.y) / (Rprim.y));
        vec4 col2 = texture(poolFloor, p2.xz);
        col = col + col2.xyz;
    }

    fragColor = vec4(col, 1.0);
}
