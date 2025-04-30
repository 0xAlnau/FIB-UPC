#version 330 core

in vec3 fcolor;

out vec4 FragColor;

uniform vec3 objectColor;

uniform float terra;

uniform float changed;

void main() { 
    if (terra == 1.0f && changed == 1.0f) FragColor = vec4(objectColor, 1);
    else FragColor = vec4(fcolor, 1);
}

