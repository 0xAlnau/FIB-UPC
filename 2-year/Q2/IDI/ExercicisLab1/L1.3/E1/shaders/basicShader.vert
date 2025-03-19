#version 330 core

in vec3 vertex;
uniform mat4 TG; //pas 3 enviem matriu
void main()  {
    gl_Position = TG * vec4 (vertex, 1.0);
}
