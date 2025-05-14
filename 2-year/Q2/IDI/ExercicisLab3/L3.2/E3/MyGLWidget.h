// MyGLWidget.h
#include "BL3GLWidget.h"

class MyGLWidget : public BL3GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL3GLWidget(parent) {}
    ~MyGLWidget();

  protected:
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void iniMaterialTerra();
    virtual void carregaShaders();
    virtual void initializeGL();

  private:
    int printOglError(const char file[], int line, const char func[]);

    //uniforms
    GLuint posFocus, colorFocus, focus_escena;

    //variables
    glm::vec3 col = glm::vec3(0.8, 0.8, 0.8);
    glm::vec3 pos = glm::vec3(1, 1, 1);  // en SCA

    float focus_escena2 = 1.0f;
};
