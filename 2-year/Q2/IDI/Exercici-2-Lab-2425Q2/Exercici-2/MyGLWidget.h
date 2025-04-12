#include "LL2GLWidget.h"

#include <vector>

#include <QTimer>

class MyGLWidget : public LL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent);
    ~MyGLWidget();

  protected:
  
    virtual void keyPressEvent (QKeyEvent *event);

    virtual void modelTransformRick(glm::vec3 pos);

    virtual void modelTransformVideoCam();

    virtual void modelTransformTerra();

    virtual void calculaCapsaModel (Model &p, float &escala, float alcadaDesitjada, glm::vec3 &centreBase);

    virtual void creaBuffersModels();

    virtual void initializeGL();

    virtual void paintGL();

    virtual void carregaShaders();

    virtual void projectTransform();

    virtual void viewTransform();

    virtual void mouseMoveEvent(QMouseEvent *e);

    virtual void resizeGL(int w, int h);

    void creaBuffersParet();

    void creaBuffersPorta();

    void modelTransformParet(glm::vec3 pos);

    void modelTransformPorta();

    void calculCentreRadi(glm::vec3 punt_minim, glm::vec3 punt_maxim);

    void paintGL2(bool camera, int view);

    // per al moviment automàtic
    QTimer timer;
    
  public slots:
    void updatePosition();

  private:
  
    int printOglError(const char file[], int line, const char func[]);
   
  // Aquí tots els atributs privats que necessitis
  glm::vec3 centreBaseTerr = glm::vec3(0.0, 0.0, 0.0); //(4 +(-4) / 2) (0.0) (4 +(-4) / 2)
  glm::vec3 centreBaseParet = glm::vec3(0.0, 0.0, 0.0); //(0.25 +(-0.25) / 2) (ymin = 0.0) (1.5 +(-1.5) / 2)

  GLuint VAO_Paret;
  GLuint VAO_Porta;
  GLuint porta;

  glm::vec3 centreEsferaContenidora;
  glm::vec3 posPorta = glm::vec3(0.0, 0.0, 0.0);

  glm::mat4 viewMatrixCamera;  //vista des de dins de la camera
  glm::mat4 viewMatrixFora;  //vista des de fora
  glm::mat4 projMatrixCamera;  //vista des de dins de la camera
  glm::mat4 projMatrixFora;  //vista des de fora

  float radi;
  float d;
  float psi = -45.0f; //trident
  float theta = 45.0f; //zero
  float angleRick = 90.0f;
  float angleCameraY = -80.0f;
  bool videoCamera = false;
  bool animacio = false;
  bool second_viewport = false;
  bool dir_x_posi = true;
};
