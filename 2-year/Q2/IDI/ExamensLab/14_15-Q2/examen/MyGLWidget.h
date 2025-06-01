#define GLM_FORCE_RADIANS
#include <QGLWidget>
#include <QGLShader>
#include <QGLShaderProgram>
#include <QKeyEvent>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "model.h"

class MyGLWidget : public QGLWidget 
{
  Q_OBJECT

  public:
    MyGLWidget (QGLFormat &f, QWidget *parent=0);
  
  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ();

    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ();
 
    // resizeGL - Es cridat quan canvi la mida del widget
    virtual void resizeGL (int width, int height);  

    // keyPressEvent - Es cridat quan es prem una tecla
    virtual void keyPressEvent (QKeyEvent *event); 
    // mouse{Press/Release/Move}Event - Són cridades quan es realitza l'event 
    // corresponent de ratolí
    virtual void mousePressEvent (QMouseEvent *event);
    virtual void mouseReleaseEvent (QMouseEvent *event);
    virtual void mouseMoveEvent (QMouseEvent *event);

  private:
    void createBuffers ();
    void loadShaders ();
    void projectTransform ();
    void viewTransform ();
    void modelTransformTerra ();
    void modelTransformPatricio ();
    void modelTransformLego ();
    void calculaCapsaModelPat ();
    void calculaCapsaModelLego ();
    void calculaParamEsc();

    // VAO i VBO names
    GLuint VAO_Patr, VBO_PatrPos, VBO_PatrNorm, VBO_PatrMatamb, VBO_PatrMatdiff, VBO_PatrMatspec, VBO_PatrMatshin;
    GLuint VAO_Terra, VBO_TerraPos, VBO_TerraNorm, VBO_TerraMatamb, VBO_TerraMatdiff, VBO_TerraMatspec, VBO_TerraMatshin;
    GLuint VAO_Lego, VBO_LegoPos, VBO_LegoNorm, VBO_LegoMatamb, VBO_LegoMatdiff, VBO_LegoMatspec, VBO_LegoMatshin;
    QGLShaderProgram *program;

    GLuint transLoc, projLoc, viewLoc, varBlau, varFocus;
    GLuint vertexLoc, normalLoc, matambLoc, matdiffLoc, matspecLoc, matshinLoc;
    Model patr;
    Model lego;
    // paràmetres calculats a partir de la capsa contenidora del model
    glm::vec3 centreBasePatr;
    float PatMaxy, PatMiny;

    glm::vec3 centreBaseLego;
    float LegoMaxy, LegoMiny;

    glm::vec3 EscMax = glm::vec3(10.0, 3.0, 10.0);
    glm::vec3 EscMin = glm::vec3(-10.0, 0.0, -10.0);
    float radi;
    float d;
    glm::vec3 centreEsc;

    float blau = 0.0;

    float angle = 0.0;

    glm::vec3 posFocus = glm::vec3(0.0, 0.0, 0.0);

    typedef  enum {NONE, ROTATE} InteractiveAction;
    InteractiveAction DoingInteractive;
    int xClick, yClick;
    float angleX, angleY;
};
