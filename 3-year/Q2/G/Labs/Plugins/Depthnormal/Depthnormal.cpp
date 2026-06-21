#include "Depthnormal.h"
#include "glwidget.h"

void Depthnormal::onPluginLoad()
{
    GLWidget & g = *glwidget();
    g.makeCurrent();
    
    // Vertex shader
    vsD = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vsD->compileSourceFile("depth.vert"); //carreguem arxiu
    cout << "VS log:" << vsD->log().toStdString() << endl;
    // Fragment Shader
    fsD = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fsD->compileSourceFile("depth.frag"); // <-- Cargamos desde el archivo
    cout << "FS log:" << fsD->log().toStdString() << endl;
    
    // Vertex shader
    vsN = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vsN->compileSourceFile("normal.vert"); //carreguem arxiu
    cout << "VS log:" << vsN->log().toStdString() << endl;
    // Fragment Shader
    fsN = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fsN->compileSourceFile("normal.frag"); // <-- Cargamos desde el archivo
    cout << "FS log:" << fsN->log().toStdString() << endl;

    program = new QOpenGLShaderProgram(this);
    program2 = new QOpenGLShaderProgram(this);
    program->addShader(vsD);
    program->addShader(fsD);
    program2->addShader(vsN);
    program2->addShader(fsN);
    program->link();
    program2->link();	
}

bool Depthnormal::paintGL()
{
    GLWidget & g = *glwidget();
    g.glClearColor(0,0,0,0);
    g.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    float width = g.width();
    
    float height = g.height();
    float ar = (float)width / (float)height;
    camera()->setAspectRatio(ar / 2.0);
    
    //depth en esquerra
    g.glViewport(0, 0, width / 2.0, height);
    program->bind();
    
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    
    if (drawPlugin()) drawPlugin()->drawScene();
    
    //normal en dreta
    g.glViewport(width / 2.0, 0, width / 2.0, height);
    program2->bind();
    
    program2->setUniformValue("modelViewProjectionMatrix", MVP);
    
    if (drawPlugin()) drawPlugin()->drawScene();
    
    return true; // return true only if implemented
}

