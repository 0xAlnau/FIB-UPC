// MyGLWidget.h
#include "LL4GLWidget.h"

class MyGLWidget : public LL4GLWidget {
  Q_OBJECT
  
  public:
    MyGLWidget(QWidget *parent=0) : LL4GLWidget(parent) {}
    ~MyGLWidget();
    
  protected:
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void modelTransformMorty();
    virtual void modelTransformEscenari();
    virtual void modelTransformEspelma(glm::vec3 pos, float alçada);
    virtual void modelTransformTerra();
    virtual void paintGL();
    virtual void initializeGL();
    virtual void iniMaterialTerra();
    virtual void projectTransform();

  private:
    int printOglError(const char file[], int line, const char func[]);
    glm::vec3 centreBaseTerra = glm::vec3((10.0f + 0.0f)/2, (0.0f + 0.0f)/2, (10.0f + 0.0f)/2);

    GLuint colorFocusCam;
    glm::vec3 colCam = glm::vec3(0.6, 0.6, 0.6);

    GLuint colorFocusEspe;
    glm::vec3 colEspe = glm::vec3(0.4, 0.4, 0.0);

    GLuint posFocusEspe1;
    glm::vec3 posFE1 = glm::vec3(-1.3, 3.37, -2.5);

    GLuint posFocusEspe2;
    glm::vec3 posFE2 = glm::vec3(-4.5, 3.7, 4.5);

    glm::vec3 posE2 = glm::vec3(-4.5, 0.1, 4.5);

    float factor = 0.0;
};
