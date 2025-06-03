#include "ExamGLWidget.h"

class MyGLWidget:public ExamGLWidget
{
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0);
    ~MyGLWidget();

  protected:
    virtual void paintGL ();
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void mouseMoveEvent (QMouseEvent *event);
    virtual void initializeGL ();
    virtual void resizeGL (int w, int h);

    virtual void iniEscena ();
    virtual void iniCamera ();
    virtual void projectTransform ();
    virtual void viewTransform ();
    
    virtual void modelTransformCurrentBrick();

    void calcParEsc();

  public slots:
    void dos_u (bool p);

    void dos_dos (bool p);

    void quatre_dos (bool p);

    void canviaR (int v);

    void canviaG (int v);

    void canviaB (int v);

  signals:
    void emit_dos_u();
    void emit_dos_dos();
    void emit_quatre_dos();

  private:
    int printOglError(const char file[], int line, const char func[]);
    glm::vec3 red = glm::vec3(0.7, 0.0, 0.0);
    glm::vec3 black = glm::vec3(0.0, 0.0, 0.0);

    float d;
    float radi;
    glm::vec3 puntMaxEsc = glm::vec3(10, 9, 10);
    glm::vec3 puntMinEsc = glm::vec3(-10, -1, -10);
    glm::vec3 centreEsc2;

    float girBloc = 0.0f;

    glm::vec3 pos2x2 = glm::vec3(0, 0, 0);
    glm::vec3 pos4x2 = glm::vec3(0, 0, 0);
    glm::vec3 pos1x2 = glm::vec3(0.5, 0, 0);

    bool camera2 = false;
    int bricks_posats = 0;

};
