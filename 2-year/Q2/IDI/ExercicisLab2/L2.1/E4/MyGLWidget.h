// MyGLWidget.h
#include "BL2GLWidget.h"
#include "model.h"
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

protected: //aqui posar els virtuals
    virtual void carregaShaders(); //Aqui cridarem la resta de Matrius!!!

    virtual void projectTransform(); //PM

    virtual void viewTransform(); // VM

    virtual void creaBuffers(); //volem canviar els VBOs

    virtual void paintGL(); //volem pintar els nous VBOs

  private:
    int printOglError(const char file[], int line, const char func[]);
    GLuint projLoc;
    GLuint viewLoc;
    GLuint VAO_Homer;
    Model m;
};
