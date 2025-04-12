// MyGLWidget.h
#include "BL2GLWidget.h"
#include "model.h"
#include <QTimer>
/*
 REPAS SISTEMA DE COORDENADES!!!
 -Volem veure més escena i no només [-1,1], llavors definim nou sistema de coordenades, el SCO (sistema coordenades observador), i hi ha una matriu que ens permet pasar del [-1,1] al SCO. Aquesta és la transformació de vista!!!!!

 -Però encara tenim un quadrat limitat, entre [-1,1], llavors entra la matriu de projecció!!!! Amplia el rang, passem de [-1,1] al que volguem, llavors podrem tindre perspectiva o ortogonal.

 -SC Local ens on modelem el model, amb la TG passem al SC d'Aplicació on pot haver varios objectes i una càmara, i amb la VM passem al SCO (on veiem de [-1,1] però tenem punt de vista), llavors la PM converteix de SCO al SC del clipping i on es pinta lo que hi ha a la perspectiva

 -TG -> VM -> PM

 -FOV veure més angle o menys

 -Znear, a partir d'aquest punt de la càmare comencem a veure coses

 -Zfar, a partir d'aquest punt no ho veurem

 -PM té el Znear, Zfar, FOV ...

 -OBS: observador
 -VRP: referencia
 -Up: on roto

 -VM = lookAt(OBS, VRP,up);

 */
class MyGLWidget : public BL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL2GLWidget(parent) {}
    ~MyGLWidget();

  public slots: //animacio!!!
    void animar();

protected: //aqui posar els virtuals
    virtual void carregaShaders(); //Aqui cridarem la resta de Matrius!!!

    virtual void projectTransform(); //PM

    virtual void viewTransform(); // VM

    virtual void creaBuffers(); //volem canviar els VBOs

    virtual void paintGL(); //volem pintar els nous VBOs

    virtual void keyPressEvent(QKeyEvent* event); //per les tecles

    virtual void mouseMoveEvent(QMouseEvent* event); //per mouse

    virtual void modelTransformPatricio(float altura, glm::vec3 pos, float angle);

    virtual void modelTransformTerra();

    virtual void initializeGL();

    virtual void resizeGL(int w, int h);

  private:
    int printOglError(const char file[], int line, const char func[]);
    void creaBuffersPatricio();
    void creaBuffersTerra();
    void paintPatricio(float altura, glm::vec3 pos, float angle);
    void paintTerra();
    void calculCentreRadi(glm::vec3 punt_minim, glm::vec3 punt_maxim);

    GLuint projLoc;
    GLuint viewLoc;
    GLuint VAO_Patricio;
    GLuint VAO_Terra;
    Model m;
    float angle = 0.0;
    glm::vec3 COLOR_BLAU=glm::vec3(48.0/255,58.0/255,158.0/255);
    glm::vec3 centre;
    glm::vec3 p_max = glm::vec3(-99999.0f, -99999.0f, -99999.0f);
    glm::vec3 p_min = glm::vec3(99999.0f, 99999.0f, 99999.0f);
    float radi;
    float d;
    float orthogonal = 0.0;
    glm::vec3 Pmax = glm::vec3(-99999.0f, -99999.0f, -99999.0f);
    glm::vec3 Pmin = glm::vec3(99999.0f, 99999.0f, 99999.0f);
    glm::vec3 Tmax = glm::vec3(-99999.0f, -99999.0f, -99999.0f);
    glm::vec3 Tmin = glm::vec3(99999.0f, 99999.0f, 99999.0f);

    float angle_trident = 0.0f;
    float angle_0 = 0.0f;
    float anglePatGir = 0.0f;
    float nPat = 0.0;
    QTimer timer;

    QPoint lastMousePos;

    float FOV = 0.0;
};
