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

void MyGLWidget::resizeGL (int w, int h)
{
  #ifdef __APPLE__
  // Aquest codi és necessari únicament per a MACs amb pantalla retina.
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
  #else
  ample = w;
  alt = h;
  #endif

  ra = float(ample)/float(alt);

  if (ra != 1.0f) {
    glm::mat4 Proj;  // Matriu de projecció
    if (ra > 1.0f) {
      if (!camera2) { //perspective
        Proj = glm::perspective(2 * glm::asin(radi/d), ra, d-radi, d+radi);
      }
      else { // ortho
        Proj = glm::ortho(-radi*ra, radi*ra, -radi, radi, d-radi, d+radi);
      }
    }
    else {
      if (!camera2) {//perspective
        float alphav = glm::asin(radi/d);
        float FOVnou = 2 * glm::atan(glm::tan(alphav)/ra);
        Proj = glm::perspective(FOVnou, ra, d-radi, d+radi);

      }
      else { //ortho
        Proj = glm::ortho(-radi, radi, -radi/ra, radi/ra, d-radi, d+radi);
      }
    }
    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
  }
}

MyGLWidget::MyGLWidget(QWidget *parent) : ExamGLWidget(parent) {

		
}

MyGLWidget::~MyGLWidget() {
}

void MyGLWidget::calcParEsc() {
  centreEsc2.x = (puntMaxEsc.x + puntMinEsc.x) / 2;
  centreEsc2.y = (puntMaxEsc.y + puntMinEsc.y) / 2;
  centreEsc2.z = (puntMaxEsc.z + puntMinEsc.z) / 2;

  radi = glm::distance(puntMaxEsc, puntMinEsc) / 2;
  d = 2 * radi;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();

  calcParEsc();

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  carregaShaders();
  iniEscena ();
  iniCamera ();
}

void MyGLWidget::iniEscena ()
{
  creaBuffersModels();

  // inicialitzem tots els possibles objectes (blocs de Lego) com a "buits" --> no es pinten ni tenen valors guardats més que els per defecte
  for (int i = 0; i < NUM_BRICKS; i++)
  {
    pintarBricks[i] = false;
    brickModelIndex[i] = 1;
    brickTGs[i] = glm::mat4(1);
    brickColors[i] = glm::vec3(1,1,1);
  }

  // inicialitzem l'objecte actual (el bloc de Lego) a editar
  currentBrickObjectIndex = 0;
  currentBrickModelIndex = 1;

  // inicialitzem el color actual
  currentColor = white;

  // Inicialitzem els paràmetres de l'escena amb valors arbitraris
  centreEsc = glm::vec3 (0, 2.0, 0);
  radiEsc = 10;

}

void MyGLWidget::iniCamera ()
{
  // Inicialitzem els paràmetres de càmera amb valors arbitraris
  angleY = glm::radians(15.f);
  angleX = glm::radians(15.f);
  ra = float(width())/height();
  //fov = float(M_PI/3.0);
  //zn = 15;
  //zf = 65;

  projectTransform ();
  viewTransform ();
}

void MyGLWidget::paintGL ()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Pintem el terra = GROUND_BRICKS
  glUniform3fv(colorLoc,1,&red[0]);
  glBindVertexArray (VAO_models[GROUND_BRICKS]);
  modelTransformGround();
  glDrawArrays(GL_TRIANGLES, 0, models[GROUND_BRICKS].faces().size()*3);

  // Pintem el bloc de Lego actual (currentBrick) del color actual
  glUniform3fv(colorLoc,1,&currentColor[0]);
  glBindVertexArray (VAO_models[currentBrickModelIndex]);
  modelTransformCurrentBrick();
  glDrawArrays(GL_TRIANGLES, 0, models[currentBrickModelIndex].faces().size()*3);
  glUniform3fv(colorLoc,1,&black[0]); //canviem a negre
  glDrawArrays(GL_LINES, 0, models[currentBrickModelIndex].faces().size()*3);
  glUniform3fv(colorLoc,1,&currentColor[0]); //posem l'original

  for (int i = 0; i < bricks_posats; ++i) {
    glUniform3fv(colorLoc,1,&brickColors[i][0]);
    glBindVertexArray (VAO_models[brickModelIndex[i]]);
    glm::mat4 TG = brickTGs[i];
    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, models[GROUND_BRICKS].faces().size()*3);
    glUniform3fv(colorLoc,1,&black[0]); //canviem a negre
    glDrawArrays(GL_LINES, 0, models[currentBrickModelIndex].faces().size()*3);
    glUniform3fv(colorLoc,1,&currentColor[0]); //posem l'original
  }

  glBindVertexArray(0);
}

void MyGLWidget::modelTransformCurrentBrick()
{
  glm::mat4 TG(1.f);
  if (currentBrickModelIndex == 2) { //2x2
    TG = glm::translate(TG, pos2x2);
    TG = glm::rotate(TG, glm::radians(girBloc), glm::vec3(0, 1, 0));
    TG = glm::rotate(TG, glm::radians(90.f), glm::vec3(1, 0, 0));
    TG = glm::scale(TG, glm::vec3 (escalaModels[currentBrickModelIndex], escalaModels[currentBrickModelIndex], escalaModels[currentBrickModelIndex]));
    TG = glm::translate(TG, -centreCapsaModels[currentBrickModelIndex]);
  }
  else if (currentBrickModelIndex == 3) { //4x2
    TG = glm::translate(TG, pos4x2);
    TG = glm::rotate(TG, glm::radians(girBloc), glm::vec3(0, 1, 0));
    TG = glm::rotate(TG, glm::radians(90.f), glm::vec3(1, 0, 0));
    TG = glm::scale(TG, glm::vec3 (escalaModels[currentBrickModelIndex], escalaModels[currentBrickModelIndex], escalaModels[currentBrickModelIndex]));
    TG = glm::translate(TG, -centreCapsaModels[currentBrickModelIndex]);
  }
  else { //1x2
    TG = glm::translate(TG, pos1x2);
    TG = glm::rotate(TG, glm::radians(girBloc), glm::vec3(0, 1, 0));
    TG = glm::rotate(TG, glm::radians(90.f), glm::vec3(1, 0, 0));
    TG = glm::scale(TG, glm::vec3 (escalaModels[currentBrickModelIndex], escalaModels[currentBrickModelIndex], escalaModels[currentBrickModelIndex]));
    TG = glm::translate(TG, -centreCapsaModels[currentBrickModelIndex]);
  }
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::viewTransform ()
{
  View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -d));
  View = glm::rotate(View, angleX, glm::vec3(1, 0, 0));
  View = glm::rotate(View, -angleY, glm::vec3(0, 1, 0));
  View = glm::translate(View, -centreEsc2);

  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::projectTransform ()
{
  if (!camera2) {
    glm::mat4 Proj;  // Matriu de projecció
    Proj = glm::perspective(2 * glm::asin(radi/d), 1.f, d-radi, d+radi);
    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
  }
  else {
    glm::mat4 Proj;  // Matriu de projecció
    Proj = glm::ortho(-radi, radi, -radi, radi, d-radi, d+radi);
    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
  }
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_A: {
    if (currentBrickModelIndex == 2) { //2x2
      if (pos2x2.x >= -9.0f) pos2x2.x -= 1.0f;
    }
    else if (currentBrickModelIndex == 3) { //4x2
      if (pos4x2.x >= -9.0f) pos4x2.x -= 1.0f;
    }
    else { //1x2
      if (pos1x2.x >= -9.0f) pos1x2.x -= 1.0f;
    }
    break;
	}
  case Qt::Key_D: {
    if (currentBrickModelIndex == 2) { //2x2
      if (pos2x2.x <= 9.0f) pos2x2.x += 1.0f;
    }
    else if (currentBrickModelIndex == 3) { //4x2
      if (pos4x2.x <= 9.0f) pos4x2.x += 1.0f;
    }
    else { //1x2
      if (pos1x2.x <= 9.0f) pos1x2.x += 1.0f;
    }
    break;
    }
  case Qt::Key_W: {
    if (currentBrickModelIndex == 2) { //2x2
      if (pos2x2.z <= 9.0f) pos2x2.z += 1.0f;
    }
    else if (currentBrickModelIndex == 3) { //4x2
      if (pos4x2.z <= 9.0f) pos4x2.z += 1.0f;
    }
    else { //1x2
      if (pos1x2.z <= 9.0f) pos1x2.z += 1.0f;
    }
    break;
	}
  case Qt::Key_S: {
    if (currentBrickModelIndex == 2) { //2x2
      if (pos2x2.z >= -9.0f) pos2x2.z -= 1.0f;
    }
    else if (currentBrickModelIndex == 3) { //4x2
      if (pos4x2.z >= -9.0f) pos4x2.z -= 1.0f;
    }
    else { //1x2
      if (pos1x2.z >= -9.0f) pos1x2.z -= 1.0f;
    }
    break;  
	}
  case Qt::Key_Up: {
    if (currentBrickModelIndex == 2) { //2x2
      if (pos2x2.y <= 9.0f) pos2x2.y += 1.0f;
    }
    else if (currentBrickModelIndex == 3) { //4x2
      if (pos4x2.y <= 9.0f) pos4x2.y += 1.0f;
    }
    else { //1x2
      if (pos1x2.y <= 9.0f) pos1x2.y += 1.0f;
    }
    break;
	}
  case Qt::Key_Down: {
    if (currentBrickModelIndex == 2) { //2x2
      if (pos2x2.y >= 1.0f) pos2x2.y -= 1.0f;
    }
    else if (currentBrickModelIndex == 3) { //4x2
      if (pos4x2.y >= 1.0f) pos4x2.y -= 1.0f;
    }
    else { //1x2
      if (pos1x2.y >= 1.0f) pos1x2.y -= 1.0f;
    }
    break;  
	}		
  case Qt::Key_Q: {
    girBloc += 90.f;
    break;
	}
  case Qt::Key_C: {
    camera2 = !camera2;
    projectTransform();
    viewTransform();
    break;
	}
  case Qt::Key_Space: {
    if (bricks_posats < NUM_BRICKS) {
      brickModelIndex[bricks_posats] = currentBrickModelIndex;
      glm::mat4 TG(1.f);
      if (currentBrickModelIndex == 2) { //2x2
        TG = glm::translate(TG, pos2x2);
        TG = glm::rotate(TG, glm::radians(girBloc), glm::vec3(0, 1, 0));
        TG = glm::rotate(TG, glm::radians(90.f), glm::vec3(1, 0, 0));
        TG = glm::scale(TG, glm::vec3 (escalaModels[currentBrickModelIndex], escalaModels[currentBrickModelIndex], escalaModels[currentBrickModelIndex]));
        TG = glm::translate(TG, -centreCapsaModels[currentBrickModelIndex]);
      }
      else if (currentBrickModelIndex == 3) { //4x2
        TG = glm::translate(TG, pos4x2);
        TG = glm::rotate(TG, glm::radians(girBloc), glm::vec3(0, 1, 0));
        TG = glm::rotate(TG, glm::radians(90.f), glm::vec3(1, 0, 0));
        TG = glm::scale(TG, glm::vec3 (escalaModels[currentBrickModelIndex], escalaModels[currentBrickModelIndex], escalaModels[currentBrickModelIndex]));
        TG = glm::translate(TG, -centreCapsaModels[currentBrickModelIndex]);
      }
      else { //1x2
        TG = glm::translate(TG, pos1x2);
        TG = glm::rotate(TG, glm::radians(girBloc), glm::vec3(0, 1, 0));
        TG = glm::rotate(TG, glm::radians(90.f), glm::vec3(1, 0, 0));
        TG = glm::scale(TG, glm::vec3 (escalaModels[currentBrickModelIndex], escalaModels[currentBrickModelIndex], escalaModels[currentBrickModelIndex]));
        TG = glm::translate(TG, -centreCapsaModels[currentBrickModelIndex]);
      }
      brickTGs[bricks_posats] = TG;
      brickColors[bricks_posats] = currentColor;
      ++bricks_posats;
    }
    break;
    }
  case Qt::Key_R: {
    pos2x2 = glm::vec3(0.0, 0.0, 0.0);
    pos4x2 = glm::vec3(0.0, 0.0, 0.0);
    pos1x2 = glm::vec3(0.5, 0.0, 0.0);
    angleY = glm::radians(15.f);
    angleX = glm::radians(15.f);
    currentColor = white;
    currentBrickModelIndex = 1;
    camera2 = false;
    bricks_posats = 0;
    ra = float(width())/height();

    projectTransform();
    viewTransform();
    break;
	}
  case Qt::Key_M: { // al prèmer la tecla M canviem el model del bloc que estem editant
    currentBrickModelIndex++;
    if (currentBrickModelIndex == NUM_MODELS) {
      currentBrickModelIndex = 1;
    }
    if(currentBrickModelIndex == 1) emit emit_dos_u();
    else if (currentBrickModelIndex == 2) emit emit_dos_dos();
    else emit emit_quatre_dos();
    break;
  }
  case Qt::Key_B: { // al prèmer la tecla B canviem el color del bloc que estem editant
    break;
  }
  default: ExamGLWidget::keyPressEvent(event); break;
  }
  
  update();
}


void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació (només en Y)
    angleY += (e->x() - xClick) * M_PI / ample;
    angleX += (yClick - e->y()) * M_PI / alt;
    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}

void MyGLWidget::dos_u (bool p) {
  makeCurrent();
  if (p) {
    currentBrickModelIndex = 1;
  }
  update();
}

void MyGLWidget::dos_dos (bool p) {
  makeCurrent();
  if (p) {
    currentBrickModelIndex = 2;
  }
  update();
}

void MyGLWidget::quatre_dos (bool p) {
  makeCurrent();
  if (p) {
    currentBrickModelIndex = 3;
  }
  update();
}

void MyGLWidget::canviaR (int v) {
  makeCurrent();
  currentColor = glm::vec3(v/255.f, currentColor.y, currentColor.z);
  update();
}

void MyGLWidget::canviaG (int v) {
  makeCurrent();
  currentColor = glm::vec3(currentColor.x, v/255.f, currentColor.z);
  update();
}

void MyGLWidget::canviaB (int v) {
  makeCurrent();
  currentColor = glm::vec3(currentColor.x, currentColor.y, v/255.f);
  update();
}
