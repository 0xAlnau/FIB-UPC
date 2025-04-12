#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

MyGLWidget::MyGLWidget(QWidget *parent=0) : LL2GLWidget(parent) 
{
  connect(&timer, SIGNAL(timeout()), this, SLOT(updatePosition()));
}

void MyGLWidget::initializeGL()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffersModels();
  creaBuffersTerra();
  creaBuffersParet();
  creaBuffersPorta();
  posRick = glm::vec3(-5.0, 0.0, 0.0); //NOVA POSICIO RICK
  //                              min                          max
  calculCentreRadi(glm::vec3(-6.0, 0.0, -4.0), glm::vec3(6.0, 2.5, 4.0)); //important fer-ho abans!
  projectTransform(); // PM
  viewTransform(); //VM
}

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

MyGLWidget::~MyGLWidget()
{
}

void MyGLWidget::resizeGL (int w, int h)
{
  // Aquest codi és necessari únicament per a MACs amb pantalla retina.
  #ifdef __APPLE__
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
  #else
  ample = w;
  alt = h;

  ra = float(ample)/float(alt);

  float rav = float(w)/float(h);

  if (rav != 1.0f) {
    if (rav > 1.0f) { //mes ample que alt mateix fov
      projMatrixFora = glm::perspective(2 * glm::asin(radi / d), rav, d - radi, d + radi);
    }

    else { //mes alt que ample llavors nou fov
        float alphav = glm::asin(radi / d);
        float FOVnou = 2 * glm::atan(glm::tan(alphav) / rav);
        projMatrixFora = glm::perspective(FOVnou, rav, d - radi, d + radi);
    }

    if (rav > 1.0f) { //mes ample que alt mateix fov
      projMatrixCamera = glm::perspective(90.0f, rav, 0.125f, 7.0f);
    }

    else { //mes alt que ample llavors nou fov
      float FOVnou = 2 * glm::atan(glm::tan(45.0f) / rav);
      projMatrixCamera = glm::perspective(FOVnou, rav, 0.125f, 7.0f);
    }
  }

  factorAngleY = M_PI / ample;
  factorAngleX = M_PI / alt;
  update();
  #endif
}

void MyGLWidget::updatePosition()
{
  // mètode que implementa el que ha de fer l'aplicació cada cop que el timer
  // fa timeout.
  makeCurrent();

  if (posRick.x < 5.5 and dir_x_posi) {
    posRick.x += 0.25;
    angleRick = 90.0f;
    if (posRick.x > -2.0f and posRick.x < 2.0f) posPorta.z = 2-abs(posRick.x);
    else posPorta.z = 0.0;

    if (posRick.x == 5.5) dir_x_posi = false;
  }

  else if (posRick.x > -5.5 and not dir_x_posi) {
    posRick.x -= 0.25;
    angleRick = 90.0f + 180.0f;
    if (posRick.x > -2.0f and posRick.x < 2.0f) posPorta.z = 2-abs(posRick.x);
    else posPorta.z = 0.0f;

    if (posRick.x == -5.5) dir_x_posi = true;
  }

  viewTransform();
  projectTransform();
  resizeGL(width(), height());
  update();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_Up: {
      if (posRick.x < 5.5) {
        posRick.x += 0.25;
        angleRick = 90.0f;
      }

      if (posRick.x > -2.0f and posRick.x < 2.0f) posPorta.z = 2-abs(posRick.x);
      else posPorta.z = 0.0;

      break;
    }
    case Qt::Key_Down: { 
      if (posRick.x > -5.5) {
        posRick.x -= 0.25;
        angleRick = 90.0f + 180.0f;
      }

      if (posRick.x > -2.0f and posRick.x < 2.0f) posPorta.z = 2-abs(posRick.x);
      else posPorta.z = 0.0f;

      break;
    }
    case Qt::Key_C: { 
      videoCamera = !videoCamera;
      break;
    }
    case Qt::Key_A: {
      animacio = !animacio;
      if (animacio) timer.start(100);
      else timer.stop();
      break;
    }
    case Qt::Key_R: { 
      animacio = false;
      timer.stop();
      videoCamera = false;
      posRick = glm::vec3(-5.0, 0.0, 0.0);
      angleRick = 90.0f;
      posPorta.z = 0.0;
      second_viewport = false;
      break;
    }
    case Qt::Key_2: {
      second_viewport = !second_viewport;
      break;
    }
    default: event->ignore(); break;
  }
  viewTransform();
  projectTransform();
  resizeGL(width(), height());
  update();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();

  int dx = e->x() - xClick;
  int dy = e->y() - yClick;

  psi -= dx * factorAngleX;
  theta -= dy * factorAngleY;

  xClick = e->x();
  yClick = e->y();

  viewTransform(); //VM, s'ha d'actualitzar!!
  update ();
}

void MyGLWidget::creaBuffersPorta()
{
  // VBO amb la posició dels vèrtexs
  glm::vec3 vertexs[8] = {
    glm::vec3( 0.125, 0.0,  1.0),
    glm::vec3(-0.125, 0.0,  1.0),
    glm::vec3( 0.125, 1.9,  1.0),
    glm::vec3(-0.125, 1.9,  1.0),
    glm::vec3( 0.125, 0.0, -1.0),
    glm::vec3(-0.125, 0.0, -1.0),
    glm::vec3( 0.125, 1.9, -1.0),
    glm::vec3(-0.125, 1.9, -1.0)
  };

  // VBO amb la posició dels vèrtexs
  glm::vec3 posPorta[36] = {  // 12 triangles
    vertexs[0], vertexs[2], vertexs[1],
    vertexs[1], vertexs[2], vertexs[3],
    vertexs[5], vertexs[1], vertexs[7],
    vertexs[1], vertexs[3], vertexs[7],
    vertexs[2], vertexs[6], vertexs[3],
    vertexs[3], vertexs[6], vertexs[7],
    vertexs[0], vertexs[4], vertexs[6],
    vertexs[0], vertexs[6], vertexs[2],
    vertexs[0], vertexs[1], vertexs[4],
    vertexs[1], vertexs[5], vertexs[4],
    vertexs[4], vertexs[5], vertexs[6],
    vertexs[5], vertexs[7], vertexs[6]
  };

  glm::vec3 c(1.0, 0.0, 0.0); //Vermell
  glm::vec3 colPorta[36];
  for (int i=0; i<36; i++)
    colPorta[i] = c;

  // VAO
  glGenVertexArrays(1, &VAO_Porta);
  glBindVertexArray(VAO_Porta);

  GLuint VBO_Porta[2];
  glGenBuffers(2, VBO_Porta);

  // geometria
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Porta[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(posPorta), posPorta, GL_STATIC_DRAW);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // color
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Porta[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colPorta), colPorta, GL_STATIC_DRAW);
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  glBindVertexArray (0);
}

void MyGLWidget::calculCentreRadi(glm::vec3 punt_minim, glm::vec3 punt_maxim)
{
  centreEsferaContenidora.x = (punt_maxim.x + punt_minim.x) / 2.0f;
  centreEsferaContenidora.y = (punt_maxim.y + punt_minim.y) / 2.0f;
  centreEsferaContenidora.z = (punt_maxim.z + punt_minim.z) / 2.0f;

  radi = glm::distance(punt_minim, punt_maxim) / 2.0f;

  d = 2.0f*radi;
}

void MyGLWidget::projectTransform () { //PM
    // glm::perspective(                        FOV,        ra ,   znear, zfar)
    projMatrixFora = glm::perspective (2*glm::asin(radi/d), 1.0f, d-radi, d+radi);

    // glm::perspective(                FOV,   ra ,  znear, zfar)
    projMatrixCamera = glm::perspective (90.0f, 1.0f, 0.125f, 7.0f);
}

void MyGLWidget::viewTransform() { //VM amb euler o camera
  glm::mat4 View(1.0);

  View = glm::translate(View, glm::vec3(0.0, 0.0, -d));
  View = glm::rotate(View, glm::radians(theta), glm::vec3(1.0, 0.0, 0.0)); //0 (signes al reves)
  View = glm::rotate(View, glm::radians(psi), glm::vec3(0.0, 1.0, 0.0)); //trident (signes al reves)
  View = glm::translate(View, -centreEsferaContenidora);

  viewMatrixFora = View;

  //glm::lookAt(                              OBS,              VRP,                   UP
  viewMatrixCamera = glm::lookAt(glm::vec3(0.0f, 2.25f, -1.0f), posRick, glm::vec3(0.0f, 1.0f, 0.0f));
}

void MyGLWidget::creaBuffersModels ()
{
  // Càrrega dels models
  rick.load("./models/Rick.obj");
  videoCam.load("./models/VideoCamera.obj");

  // Creació de VAOs i VBOs pel Ricky
  glGenVertexArrays(1, &VAO_Rick);

  // Calculem la capsa contenidora del model
  calculaCapsaModel(rick, escalaRick, 1.5, centreBaseRick); //NOVA ESCALA
  glBindVertexArray(VAO_Rick);

  GLuint VBO_Rick[2];
  glGenBuffers(2, VBO_Rick);

  // geometria
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Rick[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*rick.faces().size()*3*3,
               rick.VBO_vertices(), GL_STATIC_DRAW);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // color
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Rick[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*rick.faces().size()*3*3,
               rick.VBO_matdiff(), GL_STATIC_DRAW);
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  // Creació de VAOs i VBOs per la càmera
  glGenVertexArrays(1, &VAO_VideoCam);

  // Calculem la capsa contenidora del model
  calculaCapsaModel(videoCam, escalaVideoCam, 0.4, centreBaseVideoCam); //NOVA ESCALA
  glBindVertexArray(VAO_VideoCam);

  GLuint VBO_VideoCam[2];
  glGenBuffers(2, VBO_VideoCam);

  // geometria
  glBindBuffer(GL_ARRAY_BUFFER, VBO_VideoCam[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*videoCam.faces().size()*3*3,
	   videoCam.VBO_vertices(), GL_STATIC_DRAW);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // color
  glBindBuffer(GL_ARRAY_BUFFER, VBO_VideoCam[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*videoCam.faces().size()*3*3,
	   videoCam.VBO_matdiff(), GL_STATIC_DRAW);
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  glBindVertexArray (0);
}

void MyGLWidget::creaBuffersParet()
{
  // VBO amb la posició dels vèrtexs
  glm::vec3 vertexs[8] = {
        glm::vec3( 0.25, 0.0,  1.5),
        glm::vec3(-0.25, 0.0,  1.5),
        glm::vec3( 0.25, 2.0,  1.5),
        glm::vec3(-0.25, 2.0,  1.5),
        glm::vec3( 0.25, 0.0, -1.5),
        glm::vec3(-0.25, 0.0, -1.5),
        glm::vec3( 0.25, 2.0, -1.5),
        glm::vec3(-0.25, 2.0, -1.5)
  };

  // VBO amb la posició dels vèrtexs
  glm::vec3 posParet[36] = {  // 12 triangles
    vertexs[0], vertexs[2], vertexs[1],
    vertexs[1], vertexs[2], vertexs[3],
    vertexs[5], vertexs[1], vertexs[7],
    vertexs[1], vertexs[3], vertexs[7],
    vertexs[2], vertexs[6], vertexs[3],
    vertexs[3], vertexs[6], vertexs[7],
    vertexs[0], vertexs[4], vertexs[6],
    vertexs[0], vertexs[6], vertexs[2],
    vertexs[0], vertexs[1], vertexs[4],
    vertexs[1], vertexs[5], vertexs[4],
    vertexs[4], vertexs[5], vertexs[6],
    vertexs[5], vertexs[7], vertexs[6]
  };

  glm::vec3 c(0.2, 0.2, 0.8);
  glm::vec3 colParet[36];
  for (int i=0; i<36; i++)
    colParet[i] = c;

  // VAO
  glGenVertexArrays(1, &VAO_Paret);
  glBindVertexArray(VAO_Paret);

  GLuint VBO_Paret[2];
  glGenBuffers(2, VBO_Paret);

  // geometria
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Paret[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(posParet), posParet, GL_STATIC_DRAW);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // color
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Paret[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colParet), colParet, GL_STATIC_DRAW);
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  glBindVertexArray (0);
}

void MyGLWidget::paintGL2(bool camera, int view)
{
  if (view == 0 and camera) {
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &viewMatrixCamera[0][0]);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projMatrixCamera[0][0]);
  }
  else if (view == 0 and not camera) {
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &viewMatrixFora[0][0]);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projMatrixFora[0][0]);
  }

  else if (view == 1 and camera) {
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &viewMatrixCamera[0][0]);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projMatrixCamera[0][0]);
  }

  else {
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &viewMatrixFora[0][0]);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projMatrixFora[0][0]);
  }

  bool aux = videoCamera;
  videoCamera = camera;
  // Rick
  float valAbs = abs(posRick.x);
  if (3.5 <= valAbs and valAbs <= 5.5) {
    if (posRick.x < 0) angleCameraY = -80.0f;
    else angleCameraY = 80.0f;
  }
  else if (2.5 <= valAbs and valAbs < 3.5) {
    if (posRick.x < 0) angleCameraY = -70.0f;
    else angleCameraY = 70.0f;
  }
  else if (1.5 <= valAbs and valAbs < 2.5) {
    if (posRick.x < 0) angleCameraY = -60.0f;
    else angleCameraY = 60.0f;
  }
  else if (0.5 <= valAbs and valAbs < 1.5) {
    if (posRick.x < 0) angleCameraY = -40.0f;
    else angleCameraY = 40.0f;
  }
  else if (valAbs < 0.5) {
    if (posRick.x < 0) angleCameraY = 0.0f;
    else angleCameraY = 0.0f;
  }

  glBindVertexArray (VAO_Rick);
  modelTransformRick (posRick);
  glDrawArrays(GL_TRIANGLES, 0, rick.faces().size()*3);

  // Video Camera
  if (not videoCamera) {
    glBindVertexArray (VAO_VideoCam);
    modelTransformVideoCam ();
    glDrawArrays(GL_TRIANGLES, 0, videoCam.faces().size()*3);
  }

  // Terra
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  // Paret1
  glBindVertexArray(VAO_Paret);
  modelTransformParet(glm::vec3(0.0, 0.0, -2.5));
  glDrawArrays(GL_TRIANGLES, 0, 36);

  // Paret2
  glBindVertexArray(VAO_Paret);
  modelTransformParet(glm::vec3(0.0, 0.0, 2.5));
  glDrawArrays(GL_TRIANGLES, 0, 36);

  // Porta
  //glUniform1i(porta, 1.0); //porta activa
  glBindVertexArray(VAO_Porta);
  modelTransformPorta();
  glDrawArrays(GL_TRIANGLES, 0, 36);
  //glUniform1i(porta, 0.0); //porta no activa

  glBindVertexArray (0);

  videoCamera = aux;
}

void MyGLWidget::paintGL()
{
  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // descomentar per canviar paràmetres
  if (second_viewport) {
    // Viewport principal
    glViewport(0, 0, ample*0.7, alt);
    paintGL2(videoCamera, 0);

    // Viewport secundari (30% dret, esquina superior)
    glViewport(ample*0.7, alt*0.7, ample*0.3, alt*0.3);
    paintGL2(!videoCamera, 1);
  }

  else {
    glViewport (0, 0, ample, alt);
    paintGL2(videoCamera, 1);
  }
}

void MyGLWidget::modelTransformRick(glm::vec3 pos)
{
  glm::mat4 TG(1.0f);

  TG = glm::translate(TG, pos);
  TG = glm::rotate(TG, glm::radians(angleRick), glm::vec3(0.0, 1.0, 0.0)); //MIRA CAP A X+
  TG = glm::scale(TG, glm::vec3(escalaRick, escalaRick, escalaRick));
  TG = glm::translate(TG, -centreBaseRick);

  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformVideoCam()
{
  glm::mat4 TG(1.0f);

  TG = glm::translate(TG, glm::vec3(0.0, 2.0, -1.0)); //NOVA POSICIO
  TG = glm::rotate(TG, glm::radians(angleCameraY), glm::vec3(0.0, 1.0, 0.0)); // Segon -80 en Y
  TG = glm::rotate(TG, glm::radians(30.0f), glm::vec3(1.0, 0.0, 0.0)); // Primer +30 en X
  TG = glm::scale(TG, glm::vec3(escalaVideoCam));
  TG = glm::translate(TG, -centreBaseVideoCam);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformTerra()
{
  glm::mat4 TG(1.0f);
  float escala_x = 12.0 / 8.0;
  float escala_z = 8.0 / 8.0;

  TG = glm::translate(TG, glm::vec3(0,0,0));
  TG = glm::scale(TG, glm::vec3(escala_x, 1.0, escala_z));
  TG = glm::translate(TG, -centreBaseTerr);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformParet(glm::vec3 pos)
{
  glm::mat4 TG(1.0f);

  TG = glm::translate(TG, pos);
  TG = glm::translate(TG, -centreBaseParet);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformPorta()
{
  glm::mat4 TG(1.0f);

  TG = glm::translate(TG, posPorta);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::calculaCapsaModel (Model &p, float &escala, float alcadaDesitjada, glm::vec3 &centreBase)
{
  // Càlcul capsa contenidora i valors transformacions inicials
  float minx, miny, minz, maxx, maxy, maxz;
  minx = maxx = p.vertices()[0];
  miny = maxy = p.vertices()[1];
  minz = maxz = p.vertices()[2];
  for (unsigned int i = 3; i < p.vertices().size(); i+=3)
  {
    if (p.vertices()[i+0] < minx)
      minx = p.vertices()[i+0];
    if (p.vertices()[i+0] > maxx)
      maxx = p.vertices()[i+0];
    if (p.vertices()[i+1] < miny)
      miny = p.vertices()[i+1];
    if (p.vertices()[i+1] > maxy)
      maxy = p.vertices()[i+1];
    if (p.vertices()[i+2] < minz)
      minz = p.vertices()[i+2];
    if (p.vertices()[i+2] > maxz)
      maxz = p.vertices()[i+2];
  }

  escala = alcadaDesitjada/(maxy-miny);
  centreBase[0] = (minx+maxx)/2.0; centreBase[1] = miny; centreBase[2] = (minz+maxz)/2.0;
}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/basicShader.frag");
  vs.compileSourceFile("shaders/basicShader.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Identificador per als  atributs
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  colorLoc = glGetAttribLocation (program->programId(), "color");

  // Identificadors dels uniform locations
  transLoc = glGetUniformLocation(program->programId(), "TG");
  projLoc  = glGetUniformLocation (program->programId(), "Proj");
  viewLoc  = glGetUniformLocation (program->programId(), "View");
  porta = glGetUniformLocation(program->programId(), "porta");
}
