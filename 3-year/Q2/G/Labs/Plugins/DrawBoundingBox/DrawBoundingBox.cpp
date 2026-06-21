#include "DrawBoundingBox.h"
#include "glwidget.h"
#include <QVector3D>

DrawBoundingBox::~DrawBoundingBox() {
    if (program) delete program;
    GLWidget &g = *glwidget();
    g.glDeleteBuffers(1, &VBO_coords);
    g.glDeleteBuffers(1, &EBO);
    g.glDeleteVertexArrays(1, &VAO);
}

void DrawBoundingBox::onPluginLoad()
{
    GLWidget &g = *glwidget();

    // 1. Solo 8 vèrtexs únics (els cantons del cub unitari)
    float vertices[] = {
        0,0,0,  1,0,0,  0,0,1,  1,0,1, // Base (z=0) - Índexs 0, 1, 2, 3
        0,1,0,  1,1,0,  0,1,1,  1,1,1  // Top  (z=1) - Índexs 4, 5, 6, 7
    };

    // 2. Índexs per formar els 12 triangles (2 per cara)
    unsigned int indices[] = {
        0, 4, 5,  0, 1, 5, // Cara darrera
        2, 3, 7,  2, 6, 7, // Cara davant
        0, 2, 6,  0, 4, 6, // Cara esquerra
        1, 5, 7,  1, 3, 7, // Cara dreta
        5, 7, 6,  5, 4, 6, // Cara dalt
        1, 0, 2,  1, 3, 2  // Cara baix
    };

    g.glGenVertexArrays(1, &VAO);
    g.glBindVertexArray(VAO);

    // Buffer de coordenades
    g.glGenBuffers(1, &VBO_coords);
    g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    g.glEnableVertexAttribArray(0);

    // 3. Crear i configurar l'Element Buffer Object (EBO)
    g.glGenBuffers(1, &EBO);
    g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    g.glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    g.glBindVertexArray(0);

    // Shaders (els mateixos de l'exemple anterior)
    QString vs_src = "#version 330 core\n" 
                     "layout (location = 0) in vec3 vertex;\n"
                     "uniform mat4 proj; uniform mat4 view; uniform vec3 boxMin; uniform vec3 boxMax;\n"
                     "void main() {" 
                     "vec3 pos = boxMin + vertex * (boxMax - boxMin);\n"
                     "gl_Position = proj * view * vec4(pos, 1.0); }";
    QString fs_src = "#version 330 core\n out vec4 FragColor;\n void main() { FragColor = vec4(1,0,0,1); }";

    program = new QOpenGLShaderProgram();
    program->addShaderFromSourceCode(QOpenGLShader::Vertex, vs_src);
    program->addShaderFromSourceCode(QOpenGLShader::Fragment, fs_src);
    program->link();
}

void DrawBoundingBox::postFrame()
{
    GLWidget &g = *glwidget();
    program->bind();
    g.glBindVertexArray(VAO);
    g.glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    program->setUniformValue("proj", camera()->projectionMatrix());
    program->setUniformValue("view", camera()->viewMatrix());

    for (const Object& obj : scene()->objects()) {
        Box box = obj.boundingBox(); // [cite: 209]
        Point min = box.min();       // [cite: 33]
        Point max = box.max();       // [cite: 31]

        program->setUniformValue("boxMin", QVector3D(min.x(), min.y(), min.z()));
        program->setUniformValue("boxMax", QVector3D(max.x(), max.y(), max.z()));

        // 4. Important: ara fem servir glDrawElements en lloc de glDrawArrays
        // Indiquem que volem dibuixar 36 índexs de tipus unsigned int
        g.glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    g.glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    g.glBindVertexArray(0);
    program->release();
}
