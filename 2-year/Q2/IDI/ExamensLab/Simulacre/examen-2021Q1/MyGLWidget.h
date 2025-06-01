#include "ExamGLWidget.h"

class MyGLWidget:public ExamGLWidget
{
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : ExamGLWidget(parent) {}
    ~MyGLWidget();

  protected:
    virtual void paintGL ();
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void modelTransformCub (float escala, float angle);
    virtual void modelTransformPatricio ();
    virtual void projectTransform ();
    virtual void viewTransform ();

  private:
    int printOglError(const char file[], int line, const char func[]);
    glm::vec3 posPat = glm::vec3(5.0, 0.0, 0.0);
    bool cubs = true;
    bool blanc = true;
    float anglePat = 0.0;
    float angleCub1 = 0.0;
    float angleCub2 = 2.0 * M_PI / 3.0;
    float angleCub3 = 4.0 * M_PI / 3.0;
  public slots:
    void canviaCamera();
    void canviaAssociat(int n);
};
