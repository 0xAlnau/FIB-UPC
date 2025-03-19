#version 330 core

in vec3 vertex;
in vec3 color; //nova VBO
out vec3 fcolor;
uniform mat4 TG; //pas 3 enviem matriu
uniform float scl;

void main()  {
    fcolor = color;
    vertex *= scl;
    gl_Position = TG * vec4 (escalat, 1.0);
}
