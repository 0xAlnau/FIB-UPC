#include "LL4GLWidget.h"

#include <iostream>

LL4GLWidget::LL4GLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
  xClick = yClick = 0;
  DoingInteractive = NONE;
}

LL4GLWidget::~LL4GLWidget ()
{
  if (program != NULL)
    delete program;
}

void LL4GLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();  

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  
  carregaShaders();
  
  creaBuffersMorty();
  creaBuffersEscenari();
  creaBuffersEspelma();
  creaBuffersTerra();

  iniEscena();
  iniCamera();
}

void LL4GLWidget::iniMaterialTerra ()
{
  // Donem valors al material del terra
  amb = glm::vec3(0.1,0.1,0.2);
  diff = glm::vec3(0.2,0.2,0.8);
  spec = glm::vec3(0,0,0);
  shin = 100;
}

void LL4GLWidget::iniEscena ()
{
  centreEsc = glm::vec3(0,2,0);
  radiEsc = 9;  
}

void LL4GLWidget::iniCamera ()
{
  angleY = 0.0;
  angleX = 0.0;

  viewTransform ();
}

void LL4GLWidget::paintGL () 
{
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

  // DISCO BALL
  glBindVertexArray (VAO_Espelma);
  modelTransformEspelma ();
  glDrawArrays(GL_TRIANGLES, 0, espelma.faces().size()*3);
  
  glBindVertexArray(0);
}

void LL4GLWidget::resizeGL (int w, int h) 
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
  projectTransform();
}

void LL4GLWidget::modelTransformMorty ()
{
  glm::mat4 TG;
  TG = glm::translate(glm::mat4(1.f), glm::vec3(5,0,5));
  TG = glm::scale(TG, glm::vec3(escalaMorty, escalaMorty, escalaMorty));
  TG = glm::translate(TG, -centreBaseMorty);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void LL4GLWidget::modelTransformEscenari ()
{
  glm::mat4 TG(1.0);
  TG = glm::scale(TG, glm::vec3(escalaEscenari, escalaEscenari, escalaEscenari));
  TG = glm::translate(TG, -centreBaseEscenari);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void LL4GLWidget::modelTransformEspelma ()
{
  glm::mat4 TG(1.0);
  TG = glm::scale(TG, glm::vec3(escalaEspelma, escalaEspelma, escalaEspelma));
  TG = glm::translate(TG, -centreBaseEspelma);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void LL4GLWidget::modelTransformTerra ()
{
  glm::mat4 TG = glm::mat4(1.f);  // Matriu de transformació
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void LL4GLWidget::projectTransform ()
{
  glm::mat4 Proj;  // Matriu de projecció
  Proj = glm::perspective(float(M_PI/3.0), ra, radiEsc, 3.0f*radiEsc);

  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void LL4GLWidget::viewTransform ()
{
  View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2*radiEsc));
  View = glm::rotate(View, angleX, glm::vec3(1, 0, 0));
  View = glm::rotate(View, -angleY, glm::vec3(0, 1, 0));
  View = glm::translate(View, -centreEsc);

  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void LL4GLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
    default: event->ignore(); break;
  }
  update();
}

void LL4GLWidget::mousePressEvent (QMouseEvent *e)
{
  xClick = e->x();
  yClick = e->y();

  if (e->button() & Qt::LeftButton &&
      ! (e->modifiers() & (Qt::ShiftModifier|Qt::AltModifier|Qt::ControlModifier)))
  {
    DoingInteractive = ROTATE;
  }
}

void LL4GLWidget::mouseReleaseEvent( QMouseEvent *)
{
  DoingInteractive = NONE;
}

void LL4GLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació
    angleY += (e->x() - xClick) * M_PI / ample;
    angleX += (yClick - e->y()) * M_PI / alt;
    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}

void LL4GLWidget::calculaCapsaModelMorty ()
{
  // Càlcul capsa contenidora i valors transformacions inicials
  float minx, miny, minz, maxx, maxy, maxz;
  minx = maxx = morty.vertices()[0];
  miny = maxy = morty.vertices()[1];
  minz = maxz = morty.vertices()[2];
  for (unsigned int i = 3; i < morty.vertices().size(); i+=3)
  {
    if (morty.vertices()[i+0] < minx)
      minx = morty.vertices()[i+0];
    if (morty.vertices()[i+0] > maxx)
      maxx = morty.vertices()[i+0];
    if (morty.vertices()[i+1] < miny)
      miny = morty.vertices()[i+1];
    if (morty.vertices()[i+1] > maxy)
      maxy = morty.vertices()[i+1];
    if (morty.vertices()[i+2] < minz)
      minz = morty.vertices()[i+2];
    if (morty.vertices()[i+2] > maxz)
      maxz = morty.vertices()[i+2];
  }
  escalaMorty = 2.0/(maxy-miny);
  
  centreBaseMorty[0] = (minx+maxx)/2.0; 
  centreBaseMorty[1] = miny; 
  centreBaseMorty[2] = (minz+maxz)/2.0;
}

void LL4GLWidget::creaBuffersMorty ()
{
  // Carreguem el model de l'OBJ - Atenció! Abans de crear els buffers!
  morty.load("./models/Morty.obj");

  // Calculem la capsa contenidora del model
  calculaCapsaModelMorty ();
  
  // Creació del Vertex Array Object del Morty
  glGenVertexArrays(1, &VAO_Morty);
  glBindVertexArray(VAO_Morty);

  // Creació dels buffers del model
  GLuint VBO_Morty[6];
  // Buffer de posicions
  glGenBuffers(6, VBO_Morty);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Morty[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*morty.faces().size()*3*3, morty.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Buffer de normals
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Morty[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*morty.faces().size()*3*3, morty.VBO_normals(), GL_STATIC_DRAW);

  glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(normalLoc);

  // En lloc del color, ara passem tots els paràmetres dels materials
  // Buffer de component ambient
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Morty[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*morty.faces().size()*3*3, morty.VBO_matamb(), GL_STATIC_DRAW);

  glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matambLoc);

  // Buffer de component difusa
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Morty[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*morty.faces().size()*3*3, morty.VBO_matdiff(), GL_STATIC_DRAW);

  glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matdiffLoc);

  // Buffer de component especular
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Morty[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*morty.faces().size()*3*3, morty.VBO_matspec(), GL_STATIC_DRAW);

  glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matspecLoc);

  // Buffer de component shininness
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Morty[5]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*morty.faces().size()*3, morty.VBO_matshin(), GL_STATIC_DRAW);

  glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matshinLoc);

  glBindVertexArray(0);
}

void LL4GLWidget::calculaCapsaModelEscenari ()
{
  // Càlcul capsa contenidora i valors transformacions inicials
  float minx, miny, minz, maxx, maxy, maxz;
  minx = maxx = escenari.vertices()[0];
  miny = maxy = escenari.vertices()[1];
  minz = maxz = escenari.vertices()[2];
  for (unsigned int i = 3; i < escenari.vertices().size(); i+=3)
  {
    if (escenari.vertices()[i+0] < minx)
      minx = escenari.vertices()[i+0];
    if (escenari.vertices()[i+0] > maxx)
      maxx = escenari.vertices()[i+0];
    if (escenari.vertices()[i+1] < miny)
      miny = escenari.vertices()[i+1];
    if (escenari.vertices()[i+1] > maxy)
      maxy = escenari.vertices()[i+1];
    if (escenari.vertices()[i+2] < minz)
      minz = escenari.vertices()[i+2];
    if (escenari.vertices()[i+2] > maxz)
      maxz = escenari.vertices()[i+2];
  }
  escalaEscenari = 4.0/(maxy-miny);
  
  centreBaseEscenari[0] = (minx+maxx)/2.0; 
  centreBaseEscenari[1] = miny; 
  centreBaseEscenari[2] = (minz+maxz)/2.0;
}

void LL4GLWidget::creaBuffersEscenari ()
{
  // Carreguem el model de l'OBJ - Atenció! Abans de crear els buffers!
  escenari.load("./models/escenari.obj");

  // Calculem la capsa contenidora del model
  calculaCapsaModelEscenari ();
  
  // Creació del Vertex Array Object del Escenari
  glGenVertexArrays(1, &VAO_Escenari);
  glBindVertexArray(VAO_Escenari);

  // Creació dels buffers del model escena
  GLuint VBO_Escenari[6];
  // Buffer de posicions
  glGenBuffers(6, VBO_Escenari);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Escenari[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*escenari.faces().size()*3*3, escenari.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Buffer de normals
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Escenari[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*escenari.faces().size()*3*3, escenari.VBO_normals(), GL_STATIC_DRAW);

  glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(normalLoc);

  // En lloc del color, ara passem tots els paràmetres dels materials
  // Buffer de component ambient
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Escenari[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*escenari.faces().size()*3*3, escenari.VBO_matamb(), GL_STATIC_DRAW);

  glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matambLoc);

  // Buffer de component difusa
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Escenari[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*escenari.faces().size()*3*3, escenari.VBO_matdiff(), GL_STATIC_DRAW);

  glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matdiffLoc);

  // Buffer de component especular
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Escenari[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*escenari.faces().size()*3*3, escenari.VBO_matspec(), GL_STATIC_DRAW);

  glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matspecLoc);

  // Buffer de component shininness
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Escenari[5]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*escenari.faces().size()*3, escenari.VBO_matshin(), GL_STATIC_DRAW);

  glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matshinLoc);

  glBindVertexArray(0);
}

void LL4GLWidget::calculaCapsaModelEspelma ()
{
  // Càlcul capsa contenidora i valors transformacions inicials
  float minx, miny, minz, maxx, maxy, maxz;
  minx = maxx = espelma.vertices()[0];
  miny = maxy = espelma.vertices()[1];
  minz = maxz = espelma.vertices()[2];
  for (unsigned int i = 3; i < espelma.vertices().size(); i+=3)
  {
    if (espelma.vertices()[i+0] < minx)
      minx = espelma.vertices()[i+0];
    if (espelma.vertices()[i+0] > maxx)
      maxx = espelma.vertices()[i+0];
    if (espelma.vertices()[i+1] < miny)
      miny = espelma.vertices()[i+1];
    if (espelma.vertices()[i+1] > maxy)
      maxy = espelma.vertices()[i+1];
    if (espelma.vertices()[i+2] < minz)
      minz = espelma.vertices()[i+2];
    if (espelma.vertices()[i+2] > maxz)
      maxz = espelma.vertices()[i+2];
  }
  escalaEspelma = 1.0/(maxy-miny);
  
  centreBaseEspelma[0] = (minx+maxx)/2.0; 
  centreBaseEspelma[1] = miny; 
  centreBaseEspelma[2] = (minz+maxz)/2.0;
}

void LL4GLWidget::creaBuffersEspelma ()
{
  // Carreguem el model de l'OBJ - Atenció! Abans de crear els buffers!
  espelma.load("./models/espelma.obj");

  // Calculem la capsa contenidora del model
  calculaCapsaModelEspelma ();
  
  // Creació del Vertex Array Object de la bola disco
  glGenVertexArrays(1, &VAO_Espelma);
  glBindVertexArray(VAO_Espelma);

  // Creació dels buffers del model espelma
  GLuint VBO_Espelma[6];
  // Buffer de posicions
  glGenBuffers(6, VBO_Espelma);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Espelma[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*espelma.faces().size()*3*3, espelma.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Buffer de normals
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Espelma[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*espelma.faces().size()*3*3, espelma.VBO_normals(), GL_STATIC_DRAW);

  glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(normalLoc);

  // En lloc del color, ara passem tots els paràmetres dels materials
  // Buffer de component ambient
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Espelma[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*espelma.faces().size()*3*3, espelma.VBO_matamb(), GL_STATIC_DRAW);

  glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matambLoc);

  // Buffer de component difusa
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Espelma[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*espelma.faces().size()*3*3, espelma.VBO_matdiff(), GL_STATIC_DRAW);

  glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matdiffLoc);

  // Buffer de component especular
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Espelma[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*espelma.faces().size()*3*3, espelma.VBO_matspec(), GL_STATIC_DRAW);

  glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matspecLoc);

  // Buffer de component shininness
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Espelma[5]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*espelma.faces().size()*3, espelma.VBO_matshin(), GL_STATIC_DRAW);

  glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matshinLoc);

  glBindVertexArray(0);
}


void LL4GLWidget::creaBuffersTerra ()
{
  // VBO amb la posició dels vèrtexs
  glm::vec3 posterra[6] = {
	glm::vec3(0.0, 0.0, 10.0),
	glm::vec3(10.0, 0.0, 10.0),
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(0.0, 0.0, 0.0),
	glm::vec3(10.0, 0.0, 10.0),
	glm::vec3(10.0, 0.0, 0.0),
  }; 

  // VBO amb la normal de cada vèrtex
  glm::vec3 norm (0,1,0);
  glm::vec3 normterra[6] = {
	norm, norm, norm, norm, norm, norm
  };
  
  iniMaterialTerra();

  // Fem que el material del terra afecti a tots els vèrtexs per igual
  glm::vec3 matambterra[6] = {
	amb, amb, amb, amb, amb, amb
  };
  glm::vec3 matdiffterra[6] = {
	diff, diff, diff, diff, diff, diff
  };
  glm::vec3 matspecterra[6] = {
	spec, spec, spec, spec, spec, spec
  };
  float matshinterra[6] = {
	shin, shin, shin, shin, shin, shin
  };

// Creació del Vertex Array Object del terra
  glGenVertexArrays(1, &VAO_Terra);
  glBindVertexArray(VAO_Terra);

  GLuint VBO_Terra[6];
  glGenBuffers(6, VBO_Terra);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(posterra), posterra, GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(normterra), normterra, GL_STATIC_DRAW);

  // Activem l'atribut normalLoc
  glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(normalLoc);

  // En lloc del color, ara passem tots els paràmetres dels materials
  // Buffer de component ambient
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(matambterra), matambterra, GL_STATIC_DRAW);

  glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matambLoc);

  // Buffer de component difusa
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(matdiffterra), matdiffterra, GL_STATIC_DRAW);

  glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matdiffLoc);

  // Buffer de component especular
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(matspecterra), matspecterra, GL_STATIC_DRAW);

  glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matspecLoc);

  // Buffer de component shininness
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[5]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(matshinterra), matshinterra, GL_STATIC_DRAW);

  glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matshinLoc);

  glBindVertexArray(0);
}

void LL4GLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/basicLlumShader.frag");
  vs.compileSourceFile("shaders/basicLlumShader.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  // Obtenim identificador per a l'atribut “normal” del vertex shader
  normalLoc = glGetAttribLocation (program->programId(), "normal");
  // Obtenim identificador per a l'atribut “matamb” del vertex shader
  matambLoc = glGetAttribLocation (program->programId(), "matamb");
  // Obtenim identificador per a l'atribut “matdiff” del vertex shader
  matdiffLoc = glGetAttribLocation (program->programId(), "matdiff");
  // Obtenim identificador per a l'atribut “matspec” del vertex shader
  matspecLoc = glGetAttribLocation (program->programId(), "matspec");
  // Obtenim identificador per a l'atribut “matshin” del vertex shader
  matshinLoc = glGetAttribLocation (program->programId(), "matshin");

  // Demanem identificadors per als uniforms del vertex shader
  transLoc = glGetUniformLocation (program->programId(), "TG");
  projLoc = glGetUniformLocation (program->programId(), "Proj");
  viewLoc = glGetUniformLocation (program->programId(), "View");
}


