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

    virtual void keyPressEvent(QKeyEvent* event); //per les tecles

    virtual void mouseMoveEvent(QMouseEvent *e);

    virtual void modelTransformPatricio();

    virtual void modelTransformTerra();

    virtual void modelTransformLego();

    virtual void initializeGL();

    virtual void resizeGL(int w, int h);

  private:
    int printOglError(const char file[], int line, const char func[]);
    void creaBuffersPatricio();
    void creaBuffersLego();
    void creaBuffersTerra();
    void paintPatricio();
    void paintTerra();
    void paintLego();
    void calculCentreRadi(glm::vec3 punt_minim, glm::vec3 punt_maxim);

    GLuint projLoc;
    GLuint viewLoc;
    GLuint VAO_Patricio;
    GLuint VAO_Terra;
    GLuint VAO_Lego;

    Model m;
    Model lego;

    float angle = 0.0;

    glm::vec3 COLOR_TERRA = glm::vec3(48.0/255,58.0/255,158.0/255);
    glm::vec3 COLOR_FONS = glm::vec3(0.5, 0.7, 1.0);

    float percent_alt = 1.0f; //sobre 1
    float percent_ample = 1.0f;

    glm::vec3 centre;
    glm::vec3 p_max = glm::vec3(-99999.0f, -99999.0f, -99999.0f);
    glm::vec3 p_min = glm::vec3(99999.0f, 99999.0f, 99999.0f);
    float radi;
    float d;

    int xClick, yClick;
    float factorAngleY;
    float factorAngleX;

    float orthogonal = 0.0;

    float psi = 0.0f; //trident
    float theta = 0.0f; //zero

    glm::vec3 Pmax = glm::vec3(-99999.0f, -99999.0f, -99999.0f); //Pel patricio
    glm::vec3 Pmin = glm::vec3(99999.0f, 99999.0f, 99999.0f);

    glm::vec3 Lmax = glm::vec3(-99999.0f, -99999.0f, -99999.0f); //Pel lego
    glm::vec3 Lmin = glm::vec3(99999.0f, 99999.0f, 99999.0f);

    int prev_valor = 0;

    bool patricio = true;

    float escala_extra = 0.0f;
    float escala_anterior = 0.0f;

    int psi_anterior = 0;
    int theta_anterior = 0;

  public slots: //canvi del L2.4 per interactuar amb Qt

    void canvia_FOV(int valor);

    void canvia_VAO(bool premut);

    void canvia_perspectiva(bool premut);

    void canvia_escala(int valor);

    void canvia_psi(int valor);

    void canvia_theta(int valor);

    void canvia_color(int v1, int v2, int v3);

    void canvia_alt(int valor);

    void canvia_ample(int valor);

  signals:

    void envia_psi(int valor);

    void envia_theta(int valor);

    void envia_R(int valor);

    void envia_G(int valor);

    void envia_B(int valor);
};
