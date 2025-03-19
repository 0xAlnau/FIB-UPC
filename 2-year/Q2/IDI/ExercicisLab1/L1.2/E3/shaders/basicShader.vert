#version 330 core

in vec3 vertex;

void main()  {
    gl_Position = vec4 (vertex * 0.5, 1.0); //multipliquem tot per 0.5 :)
}
