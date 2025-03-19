#version 330 core

in vec3 vertex;
in vec3 color; //nova VBO
out vec3 fcolor;
uniform mat4 TG; //pas 3 enviem matriu
void main()  {
    fcolor = color;
    gl_Position = TG * vec4 (vertex, 1.0);
}
