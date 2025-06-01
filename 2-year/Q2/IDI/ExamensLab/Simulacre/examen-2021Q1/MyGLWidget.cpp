// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[]) 
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    const char * error = 0;
    switch (glErr)
    {
        case 0x0500:
            error = "GL_INVALID_ENUM";
            break;
        case 0x501:
            error = "GL_INVALID_VALUE";
            break;
        case 0x502: 
            error = "GL_INVALID_OPERATION";
            break;
        case 0x503:
            error = "GL_STACK_OVERFLOW";
            break;
        case 0x504:
            error = "GL_STACK_UNDERFLOW";
            break;
        case 0x505:
            error = "GL_OUT_OF_MEMORY";
            break;
        default:
            error = "unknown error!";
    }
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s function: %s\n",
                             file, line, error, func);
        retCode = 1;
    }
    return retCode;
}

MyGLWidget::~MyGLWidget() {
}

void MyGLWidget::paintGL ()   // Mètode que has de modificar
{
  // Esborrem el frame-buffer i el depth-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Pintem el terra
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  if (cubs) {
    // Pintem el cub 1
    glBindVertexArray(VAO_Cub);
    modelTransformCub (2.0, angleCub1);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Pintem el cub 2
    glBindVertexArray(VAO_Cub);
    modelTransformCub (2.5, angleCub2);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Pintem el cub 3
    glBindVertexArray(VAO_Cub);
    modelTransformCub (3.0, angleCub3);
    glDrawArrays(GL_TRIANGLES, 0, 36);
  }

  // Pintem el Patricio
  else {
    glBindVertexArray (VAO_Patr);
    modelTransformPatricio ();
    glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);
  }


  glBindVertexArray(0);
}

void MyGLWidget::modelTransformCub (float escala, float angle)
{
  // En aquest mètode has de substituir aquest codi per construir la 
  // transformació geomètrica (TG) del cub usant els paràmetres adientment
  TG = glm::mat4(1.f);
  escala = escala / 0.5;
  TG = rotate(TG, angle, glm::vec3(0.0, 1.0, 0.0));
  TG = translate(TG, glm::vec3(5.0, 0.0, 0.0));
  TG = scale(TG, glm::vec3(escala, escala, escala));

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformPatricio ()    // Mètode que has de modificar
{
  TG = glm::mat4(1.f);

  float diffPunts = 1.0 / escala;
  float escala2 = 2.0f / diffPunts;

  TG = glm::rotate(TG, anglePat, glm::vec3(0.0, 1.0, 0.0));
  TG = glm::translate(TG, posPat);
  TG = glm::rotate(TG, glm::radians(-90.f), glm::vec3(0.0, 1.0, 0.0));
  TG = glm::scale(TG, glm::vec3 (escala2, escala2, escala2));
  TG = glm::translate(TG, -centreBasePat);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::viewTransform ()    // Mètode que has de modificar
{
  if (!camPlanta)
    ExamGLWidget::viewTransform();
  else
  {
    // Codi per a la viewMatrix de la Càmera-2
    View = glm::lookAt(glm::vec3(0.0, 2*radiEsc, 0.0), glm::vec3(0.0,0.0,0.0), glm::vec3(1.0,0.0,0.0));
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
  }
}

void MyGLWidget::projectTransform ()
{
  if (!camPlanta)
    ExamGLWidget::projectTransform();
  else
  {
    // Codi per a la projectMatrix de la Càmera-2
    glm::mat4 Proj;  // Matriu de projecció
    Proj = glm::ortho(-radiEsc, radiEsc, -radiEsc, radiEsc, zn, zf);

    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
  }
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_V: {
      cubs = !cubs;
    break;
	}
  case Qt::Key_1: {
      anglePat = 0.0;
    break;
	}
  case Qt::Key_2: {
      anglePat = 2.0 * M_PI / 3.0;
    break;
	}
  case Qt::Key_3: {
      anglePat = 4.0 * M_PI / 3.0;
    break;
	}
  case Qt::Key_F: {
      blanc = !blanc;
      if (blanc) colFoc = glm::vec3(1.0, 1.0, 1.0);
      else colFoc = glm::vec3(1.0, 1.0, 0.0);
      glUniform3fv (colfocusLoc, 1, &colFoc[0]);
    break;
	}
  case Qt::Key_C: {
      camPlanta = !camPlanta;
    break;
	}
  case Qt::Key_Right: {
      angleCub1 -= 2.0 * M_PI / 3.0;
      angleCub2 -= 2.0 * M_PI / 3.0;
      angleCub3 -= 2.0 * M_PI / 3.0;
      anglePat -= 2.0 * M_PI / 3.0;
    break;
	}
  case Qt::Key_Left: {
      angleCub1 += 2.0 * M_PI / 3.0;
      angleCub2 += 2.0 * M_PI / 3.0;
      angleCub3 += 2.0 * M_PI / 3.0;
      anglePat += 2.0 * M_PI / 3.0;
    break;
	}
  case Qt::Key_R: {
      posPat = glm::vec3(5.0, 0.0, 0.0);
      colFoc = glm::vec3(1.0, 1.0, 1.0);
      glUniform3fv (colfocusLoc, 1, &colFoc[0]);
      blanc = true;
      cubs = true;
      camPlanta = false;
    break;
	}
  default: ExamGLWidget::keyPressEvent(event); break;
  }
  update();
  projectTransform();
  viewTransform();
}

void MyGLWidget::canviaCamera() {
    camPlanta = !camPlanta;
    makeCurrent();
    update();
    viewTransform();
    projectTransform();
}

void MyGLWidget::canviaAssociat(int n) {
    makeCurrent();
    if (n == 1) anglePat = 0.0;
    else if (n == 2) anglePat = 2.0 * M_PI / 3.0;
    else anglePat = 4.0 * M_PI / 3.0;
    update();
}
