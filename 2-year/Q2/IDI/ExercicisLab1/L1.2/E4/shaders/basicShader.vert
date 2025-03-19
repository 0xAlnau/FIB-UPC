#version 330 core

in vec3 vertex;
in vec3 color; //nova VBO
out vec3 fcolor;

void main()  {
    fcolor = color; //passem el color al fragment
    gl_Position = vec4 (vertex * 0.5, 1.0); //multipliquem tot per 0.5 :)
}
