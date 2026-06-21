#version 330 core

in vec4 gfrontColor;
in float noise;
out vec4 fragColor;

void main()
{
    vec2 uv = gl_PointCoord;
    uv = (uv * 2.0) - 1.0;
    uv = uv / 2.0;

    float dist = distance(gl_FragCoord.xy, vec2(0.0));

    if (dist > 0.5) discard;

    float z = sqrt(0.25 - dist*dist);
    vec3 N = normalize(vec3(uv.x, uv.y, z));

    vec3 col1 = vec3(0.80, 0.60, 0.40);
    vec3 col2 = vec3(0.95, 0.85, 0.70);
    vec3 col = mix(col1, col2, noise);

    fragColor = vec4(col * N.z, 1.0);
}
