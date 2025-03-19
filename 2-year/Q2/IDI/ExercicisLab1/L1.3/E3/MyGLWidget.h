#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include "glm/glm.hpp"
#include <QKeyEvent> //per usar les keys!!!!!!!!!!
#include "glm/gtc/matrix_transform.hpp" //per usar Translate!!!!!!!!!!1

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();
    
  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ();

    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ();
 
    // resize - Es cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);  

    virtual void keyPressEvent (QKeyEvent *e); //aqui dintre en el private
  private:
    void creaBuffers ();
    void carregaShaders ();

    void modelTransform ();
    // attribute locations
    GLuint vertexLoc;
    GLuint vertexCol;
    GLuint vertexTranslocation;
    GLuint transLoc; //per la matriu de translacio, 1 pas
    // Program
    QOpenGLShaderProgram *program;

    GLuint VAO1;
    GLint ample, alt;
    float x, y, z, scl, z2;
};
