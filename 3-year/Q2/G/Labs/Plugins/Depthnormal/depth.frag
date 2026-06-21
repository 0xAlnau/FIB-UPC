#version 330 core

out vec4 fragColor;

void main()
{
    // z en window space
    fragColor = vec4(vec3(gl_FragCoord.z), 1.0);
}
