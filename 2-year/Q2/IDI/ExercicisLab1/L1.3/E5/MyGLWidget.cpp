//translate, rotar, i escalar finalment!!!!!!!!!!!!!!1
//#include <GL/glew.h>
#include "MyGLWidget.h"

#include <iostream>

void MyGLWidget::keyPressEvent (QKeyEvent *e) { //funcio per canviar la translacio, treure el virtual!!!!!!!!!
  makeCurrent (); // fa actiu el nostre context d’OpenGL
  switch ( e->key() ) {
    case Qt::Key_Left : {
      x -= 0.1;
      z += glm::radians(45.0);
      break;
    }

    case Qt::Key_Right : {
      x += 0.1;
      z += glm::radians(45.0);
      break;
    }

    case Qt::Key_Up : {
      y += 0.1;
      z += glm::radians(45.0);
      break;
    }

    case Qt::Key_Down : {
      y -= 0.1;
      z += glm::radians(45.0);
      break;
    }

    case Qt::Key_S : {
      scl -= 0.1;
      glUniform1f(varLoc, scl);
      break;
    }

    case Qt::Key_D : {
      scl += 0.1;
      glUniform1f(varLoc, scl);
      break;
    }

    default : {
      e->ignore (); // propagar al pare
    }
  }
  update (); // provoca que es torni a pintar l’escena
}


void MyGLWidget::modelTransform () { //EXEMPLE PER MATRIU, en veritat volem Rot i Trans, però ho fem al revés
  glm::mat4 TG (1.0); // Matriu de transformació, inicialment identitat
  TG = glm::translate (TG, glm::vec3 (x, y, 0.0)); //transladem
  TG = glm::rotate (TG, z, glm::vec3 (0.0, 0.0, 1.0)); //rotem sobre z 45 graus
  TG = glm::scale (TG, glm::vec3 (scl, scl, scl));
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();
  
  glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffers();
  x = 0; //Inicialitzem!!!!!!!!!!!!!!!!
  y = 0;
  z = 0;
  z2 = 0;
  scl = 0.5;
}

void MyGLWidget::paintGL ()
{
// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);
  
  glClear (GL_COLOR_BUFFER_BIT); // Esborrem el frame-buffer
  modelTransform (); //acutalitzem rotacions i tot!!!!!!!!!!!! amb el update!!!!!!!!!
  glBindVertexArray (VAO1);
  glDrawArrays (GL_TRIANGLES, 0, 3);
  glBindVertexArray (0);
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
#endif
}

void MyGLWidget::creaBuffers ()
{
  glm::vec3 Vertices[3];  // Tres vèrtexs amb X, Y i Z
  Vertices[0] = glm::vec3(-1.0, -1.0, 0.0);
  Vertices[1] = glm::vec3(1.0, -1.0, 0.0);
  Vertices[2] = glm::vec3(0.0, 1.0, 0.0);
  

  // Creació del Vertex Array Object (VAO) que usarem per pintar
  glGenVertexArrays(1, &VAO1);
  glBindVertexArray(VAO1);

  // Creació del buffer amb les dades dels vèrtexs
  GLuint VBO1;
  glGenBuffers(1, &VBO1);
  glBindBuffer(GL_ARRAY_BUFFER, VBO1);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)	
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);


  //VBO2, el color
  glm::vec3 Vertices2[3];  // Tres vèrtexs amb X, Y i Z
  Vertices2[0] = glm::vec3(1.0, 0.0, 0.0); //vermell
  Vertices2[1] = glm::vec3(0.0, 1.0, 0.0); //greem
  Vertices2[2] = glm::vec3(0.0, 0.0, 1.0); //blue

  GLuint VBO2;
  glGenBuffers(1, &VBO2);
  glBindBuffer(GL_ARRAY_BUFFER, VBO2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices2), Vertices2, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)
  glVertexAttribPointer(vertexCol, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexCol);

  // Desactivem el VAO
  glBindVertexArray(0);
  modelTransform (); //perque surti inicialment !!!!!!!!!!!!!!!!!!!!!!!!!!!!
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

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  vertexCol = glGetAttribLocation (program->programId(), "color"); // !!! cal posar un pel color al.h
  transLoc = glGetUniformLocation (program->programId(), "TG"); //matriu. 2 pas
  varLoc = glGetUniformLocation (program->programId(), "scl"); //escalar uniform
}
