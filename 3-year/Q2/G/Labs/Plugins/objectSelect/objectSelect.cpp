#include "objectSelect.h"
#include <QCoreApplication>

void ObjectSelect::encodeID(const unsigned int i, GLubyte * color) {
    // Extraiem els bits corresponents utilitzant màscares (AND lògic) i desplaçaments
    GLubyte R = i & 0xFF;         // Agafem els 8 bits menys significatius
    GLubyte G = (i >> 8) & 0xFF;  // Desplacem 8 bits a la dreta i n'agafem 8
    GLubyte B = (i >> 16) & 0xFF; // Desplacem 16 bits a la dreta i n'agafem 8

    color[0] = R;
    color[1] = G;
    color[2] = B;
    color[3] = 255; // El canal alfa sempre opac per evitar barreges
}

void ObjectSelect::decodeID(const GLubyte *color, unsigned int &i) {
    unsigned int R = (unsigned int) color[0];
    unsigned int G = (unsigned int) color[1];
    unsigned int B = (unsigned int) color[2];

    // Reconstruïm l'índex original unint els bits en les seves posicions
    i = R | (G << 8) | (B << 16);
}

void ObjectSelect::onPluginLoad() {
    std::cout << "[ObjectSelect plugin] Ctrl + Right Click - Select object" << std::endl;

    GLWidget &g = *glwidget();
    g.makeCurrent();

    // Carregar shader, compile & link
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile(g.getPluginPath() + "/../objectSelect/objectSelect.vert");

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile(g.getPluginPath() + "/../objectSelect/objectSelect.frag");

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    if (!program->isLinked())
        std::cout << "Shader link error" << std::endl;
}

void ObjectSelect::selectDraw(GLWidget & g) {
    // (b) Neteja dels buffers
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // (c) Activar el shader program
    program->bind();

    // (d) Enviar uniforms de matriu
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);

    // (e) Pintar amb l'ID com a color
    for (unsigned int i=0; i<scene()->objects().size(); ++i){
        GLubyte color[4];
        encodeID(i,color);
        program->setUniformValue("color", QVector4D(color[0]/255.0f, color[1]/255.0f, color[2]/255.0f, 1.0f));
        drawPlugin()->drawObject(i);
    }
}

void ObjectSelect::mouseReleaseEvent(QMouseEvent* e) {
    // (a) Comprovar els modificadors: Ctrl + RightButton
    if (!(e->button() & Qt::RightButton)) return;
    if (e->modifiers() & (Qt::ShiftModifier)) return;
    if (!(e->modifiers() & Qt::ControlModifier)) return;

    GLWidget &g = *glwidget();
    g.makeCurrent();

    // (b) through (e) - Dibuixem l'escena amb colors codificats al backbuffer
    selectDraw(g);

    // (f) Llegim el color del píxel on es troba el cursor
    int x = e->x();
    int y = g.height() - e->y();
    GLubyte read[4];
    glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, read);

    // (g) Obtenir l'objecte seleccionat
    if(read[3] == 255){
        // No és fons (que sol tenir Alpha diferent o color de neteja clar)
        unsigned int tmp;
        decodeID(read, tmp);
        scene()->setSelectedObject((int) tmp);
        std::cout << "Objecte seleccionat: " << tmp << std::endl;
    } else {
        scene()->setSelectedObject(-1);
        std::cout << "Cap objecte seleccionat: -1" << std::endl;
    }

    // (h) Demanem una actualització de l'escena normal
    g.update();
}

void ObjectSelect::postDraw() {
    // Obtenim l'objecte seleccionat. Si no n'hi ha cap (-1), sortim.
    int sel = scene()->selectedObject();
    if (sel < 0) return;

    GLWidget &g = *glwidget();
    g.makeCurrent();

    // Utilitzem el shader que ja tenim compilat
    program->bind();

    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);

    // Pintem la capsa de color vermell
    program->setUniformValue("color", QVector4D(1.0f, 0.0f, 0.0f, 1.0f));

    // Obtenim els límits de la capsa englobant de l'objecte
    Box b = scene()->objects()[sel].boundingBox();
    QVector3D min = b.min();
    QVector3D max = b.max();

    // Construïm els 8 vèrtexs
    QVector3D vertices[8] = {
        QVector3D(min.x(), min.y(), min.z()),
        QVector3D(max.x(), min.y(), min.z()),
        QVector3D(min.x(), max.y(), min.z()),
        QVector3D(max.x(), max.y(), min.z()),
        QVector3D(min.x(), min.y(), max.z()),
        QVector3D(max.x(), min.y(), max.z()),
        QVector3D(min.x(), max.y(), max.z()),
        QVector3D(max.x(), max.y(), max.z())
    };

    // Índexs de les 12 arestes per GL_LINES
    GLuint indices[24] = {
        0,1, 1,3, 3,2, 2,0, // Base inferior
        4,5, 5,7, 7,6, 6,4, // Base superior
        0,4, 1,5, 2,6, 3,7  // Línies verticals
    };

    // Enviem a pintar de forma directa (manera ràpida i compatible amb el Core Profile si creem un VAO temporal)
    // Creem VAO i VBO temporals per a aquest frame (a l'entorn de producció es farien a l'onPluginLoad)
    GLuint VAO, VBO, EBO;
    g.glGenVertexArrays(1, &VAO);
    g.glGenBuffers(1, &VBO);
    g.glGenBuffers(1, &EBO);

    g.glBindVertexArray(VAO);

    g.glBindBuffer(GL_ARRAY_BUFFER, VBO);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    g.glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // L'atribut 'vertex' del nostre vert shader està a la location 0
    g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    g.glEnableVertexAttribArray(0);

    // Dibuixem els filferros
    g.glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    g.glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
    g.glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Restaurem l'estat per defecte

    // Alliberem els recursos temporals
    g.glBindVertexArray(0);
    g.glDeleteVertexArrays(1, &VAO);
    g.glDeleteBuffers(1, &VBO);
    g.glDeleteBuffers(1, &EBO);
}
