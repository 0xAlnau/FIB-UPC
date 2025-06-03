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

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {

  case Qt::Key_Up: 
      if (factor > -1.0) factor -= 0.1;
      break;
  case Qt::Key_Down: 
      if (factor < 1.0) factor += 0.1;
      break;
  case Qt::Key_Left: 
      if (posE2.x > -4.5) {
        posE2.x -= 0.5;
        posFE2.x -= 0.5;
        glUniform3fv(posFocusEspe2, 1, &posFE2[0]);
      }
      break;
  case Qt::Key_Right: 
      if (posE2.x < 4.5) {
          posE2.x += 0.5;
          posFE2.x += 0.5;
          glUniform3fv(posFocusEspe2, 1, &posFE2[0]);
      }
      break;
  case Qt::Key_C:
      if (colCam.x == 0.0) colCam = glm::vec3(0.6, 0.6, 0.6);
      else colCam = glm::vec3(0.0, 0.0, 0.0);
      glUniform3fv(colorFocusCam, 1, &colCam[0]);

      break;
  case Qt::Key_E:
      if (colEspe.x == 0.0) colEspe = glm::vec3(0.4, 0.4, 0.0);
      else colEspe = glm::vec3(0.0, 0.0, 0.0);
      glUniform3fv(colorFocusEspe, 1, &colEspe[0]);

      break;

  default: LL4GLWidget::keyPressEvent(event); break;
  }
  update();
  projectTransform();
}

void MyGLWidget::initializeGL ()
{
    // Cal inicialitzar l'ús de les funcions d'OpenGL
    initializeOpenGLFunctions();

    glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    carregaShaders();

    colorFocusCam = glGetUniformLocation(program->programId(), "colorFocusCam");
    glUniform3fv(colorFocusCam, 1, &colCam[0]);

    colorFocusEspe = glGetUniformLocation(program->programId(), "colorFocusEspe");
    glUniform3fv(colorFocusEspe, 1, &colEspe[0]);

    posFocusEspe1 = glGetUniformLocation(program->programId(), "posFocusEspe1");
    glUniform3fv(posFocusEspe1, 1, &posFE1[0]);

    posFocusEspe2 = glGetUniformLocation(program->programId(), "posFocusEspe2");
    glUniform3fv(posFocusEspe2, 1, &posFE2[0]);

    creaBuffersMorty();
    creaBuffersEscenari();
    creaBuffersEspelma();
    creaBuffersTerra();

    iniEscena();
    iniCamera();
}

void MyGLWidget::projectTransform() {
    glm::mat4 Proj;  // Matriu de projecció
    Proj = glm::perspective(float(M_PI/3.0) + factor, ra, radiEsc, 3.0f*radiEsc);

    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::iniMaterialTerra() {
    // Donem valors al material del terra
    amb = glm::vec3(0.1,0.1,0.1);
    diff = glm::vec3(0.7,0.7,0.7); //color gris
    spec = glm::vec3(1,1,1);
    shin = 1000000;
}

void MyGLWidget::paintGL() {
    // En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
    // useu els paràmetres que considereu (els que hi ha són els de per defecte)
    // glViewport (0, 0, ample, alt);

    // Esborrem el frame-buffer i el depth-buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // TERRA
    glBindVertexArray (VAO_Terra);
    modelTransformTerra ();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // MORTY
    glBindVertexArray (VAO_Morty);
    modelTransformMorty ();
    glDrawArrays(GL_TRIANGLES, 0, morty.faces().size()*3);

    // ESCENARI
    glBindVertexArray (VAO_Escenari);
    modelTransformEscenari ();
    glDrawArrays(GL_TRIANGLES, 0, escenari.faces().size()*3);

    // Espelma 1
    glBindVertexArray (VAO_Espelma);
    modelTransformEspelma(glm::vec3(-1.3, 1.85, -2.5), 1.5);
    glDrawArrays(GL_TRIANGLES, 0, espelma.faces().size()*3);

    // Espelma 2
    glBindVertexArray (VAO_Espelma);
    modelTransformEspelma (posE2, 3.5);
    glDrawArrays(GL_TRIANGLES, 0, espelma.faces().size()*3);

    glBindVertexArray(0);
}

void MyGLWidget::modelTransformMorty() {
    glm::mat4 TG(1.0f);

    float diffPos = 2.0 / escalaMorty; // alçada que té / escalaFeta = (maxy - miny)
    float escalaMorty2 = 3.6 /diffPos;

    TG = glm::translate(TG, glm::vec3(2,0,-2));
    TG = glm::rotate(TG, glm::radians(-90.0f), glm::vec3(0.0, 1.0, 0.0));
    TG = glm::scale(TG, glm::vec3(escalaMorty2, escalaMorty2, escalaMorty2));
    TG = glm::translate(TG, -centreBaseMorty);

    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformEscenari() {
    glm::mat4 TG(1.0);

    TG = glm::scale(TG, glm::vec3(escalaEscenari, escalaEscenari, escalaEscenari));
    TG = glm::translate(TG, -centreBaseEscenari);

    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformEspelma(glm::vec3 pos, float alçada) {
    glm::mat4 TG(1.0);

    float diffPos = 1.0 / escalaEspelma; // alçada que té / escalaFeta = (maxy - miny)
    float escalaEspelma2 = alçada/diffPos;

    TG = translate(TG, pos);
    TG = glm::scale(TG, glm::vec3(escalaEspelma2, escalaEspelma2, escalaEspelma2));
    TG = glm::translate(TG, -centreBaseEspelma);

    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformTerra() {
    glm::mat4 TG = glm::mat4(1.f);  // Matriu de transformació

    TG = translate(TG, glm::vec3(0.0, 0.1, 0.0));
    TG = translate(TG, -centreBaseTerra);

    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}
