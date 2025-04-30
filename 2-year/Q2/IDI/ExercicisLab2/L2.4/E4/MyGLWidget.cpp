// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;
/*
 REPAS SISTEMA DE COORDENADES!!!
 -Volem veure més escena i no només [-1,1], llavors definim nou sistema de coordenades, el SCO (sistema coordenades observador), i hi ha una matriu que ens permet pasar del [-1,1] al SCO. Aquesta és la transformació de vista!!!!!

 -Però encara tenim un quadrat limitat, entre [-1,1], llavors entra la matriu de projecció!!!! Amplia el rang, passem de [-1,1] al que volguem, llavors podrem tindre perspectiva o ortogonal.

 -SC Local ens on modelem el model, amb la TG passem al SC d'Aplicació on pot haver varios objectes i una càmara, i amb la VM passem al SCO (on veiem de [-1,1] però tenem punt de vista), llavors la PM converteix de SCO al SC del clipping i on es pinta lo que hi ha a la perspectiva

 -TG -> VM -> PM

 -FOV veure més angle o menys

 -Znear, a partir d'aquest punt de la càmare comencem a veure coses

 -Zfar, a partir d'aquest punt no ho veurem

 */
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

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffers();
  escala = 1.0f;
  //                         min                      max,          preguntar com fer-ho amb variables p_min i p_max???????????
  calculCentreRadi(glm::vec3(-2.5, 0.0, -2.5), glm::vec3(2.5, 4.0, 2.5)); //important fer-ho abans!
  projectTransform(); // HEM de fer el canvi!!! PM
  viewTransform(); //VM
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

  // nou rati d'aspecte
  float rav = float(w) / float(h);

  if (rav != 1.0f) {
    if (not orthogonal) { //perspectiva
        glm::mat4 Proj;
        if (rav > 1.0f) { //mes ample que alt mateix fov
            Proj = glm::perspective(2 * glm::asin(radi / d), rav, d - radi, d + radi);
        }

        else { //mes alt que ample llavors nou fov
            float alphav = glm::asin(radi / d);
            float FOVnou = 2 * glm::atan(glm::tan(alphav) / rav);
            Proj = glm::perspective(FOVnou, rav, d - radi, d + radi);
        }

        glUseProgram(program->programId());
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
    }

    else { //ortogonal
        glm::mat4 Proj;

        if (rav > 1.0f) { //mes ample que alt mateix fov
            Proj = glm::ortho(-radi*rav, radi*rav, -radi, radi, d-radi, d+radi);
        }

        else { //mes alt que ample llavors nou fov
            Proj = glm::ortho(-radi, radi, -radi/rav, radi/rav, d-radi, d+radi);
        }

        glUseProgram(program->programId());
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
    }
  }
    update();
#endif
}

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_D: { // escalar a més gran
      if (escala_extra < 10.0f) escala_extra += 0.1f;
      break;
    }
    case Qt::Key_S: {
      if (escala_extra > -10.0f) escala_extra -= 0.1f;
      break;
    }
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::calculCentreRadi(glm::vec3 punt_minim, glm::vec3 punt_maxim) {
    centre.x = (punt_maxim.x + punt_minim.x) / 2;
    centre.y = (punt_maxim.y + punt_minim.y) / 2;
    centre.z = (punt_maxim.z + punt_minim.z) / 2;

    radi = glm::distance(punt_minim, punt_maxim) / 2;

    d = 2*radi;
}

void MyGLWidget::paintGL ()
{
// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //esborrem els buffer profunditats, a cada paint

  paintTerra();
  if (patricio) paintPatricio();
  else paintLego();

  projectTransform();
  resizeGL(width(), height()); //MOLT IMPORTANT PER FER EL RESIZE BE

  glBindVertexArray (0);
}

void MyGLWidget::paintPatricio() {
    modelTransformPatricio();

    // Activem el VAO per a pintar el Patricio
    glBindVertexArray(VAO_Patricio);

    // pintem
    glDrawArrays (GL_TRIANGLES, 0, m.faces ().size () * 3);
}

void MyGLWidget::paintLego() {
    modelTransformLego();

    // Activem el VAO per a pintar el Patricio
    glBindVertexArray(VAO_Lego);

    // pintem
    glDrawArrays (GL_TRIANGLES, 0, lego.faces ().size () * 3);
}

void MyGLWidget::paintTerra() {
    modelTransformTerra();

    // Activem el VAO per a pintar el Terra
    glBindVertexArray(VAO_Terra);

    // pintem
    glDrawArrays (GL_TRIANGLES, 0, 6);
}

void MyGLWidget::creaBuffers() {
    glEnable(GL_DEPTH_TEST); //activem Z-buffer, al creaBuffers, 1 sol cop

    creaBuffersTerra();
    creaBuffersPatricio();
    creaBuffersLego();
}

void MyGLWidget::creaBuffersPatricio() {
    m.load("../Patricio.obj"); //carreguem Patricio

    glGenVertexArrays(1, &VAO_Patricio);
    glBindVertexArray(VAO_Patricio);

    GLuint VBO_Patricio[2];
    glGenBuffers(2, VBO_Patricio);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Patricio[0]); //localitzacio
    glBufferData (GL_ARRAY_BUFFER, //enviem VBOs a la GPU
                  sizeof(GLfloat) * m.faces ().size () * 3 * 3,
                  m.VBO_vertices (), GL_STATIC_DRAW);

    // Activem l'atribut vertexLoc
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //iterem sobre vertex patricio!!!!!!!!11
    for (unsigned int i = 0; i < m.vertices().size(); i += 3) {
        p_max = glm::max(p_max, glm::vec3(m.vertices()[i], m.vertices()[i+1], m.vertices()[i+2]));
        p_min = glm::min(p_min, glm::vec3(m.vertices()[i], m.vertices()[i+1], m.vertices()[i+2]));

        Pmax = glm::max(Pmax, glm::vec3(m.vertices()[i], m.vertices()[i+1], m.vertices()[i+2]));
        Pmin = glm::min(Pmin, glm::vec3(m.vertices()[i], m.vertices()[i+1], m.vertices()[i+2]));
    }


    glEnableVertexAttribArray(vertexLoc);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Patricio[1]); //colors
    glBufferData (GL_ARRAY_BUFFER, //enviem VBOs a la GPU
                  sizeof(GLfloat) * m.faces ().size () * 3 * 3,
                  m.VBO_matdiff (), GL_STATIC_DRAW);

    // Activem l'atribut colorLoc
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);

    glBindVertexArray (0);

}

void MyGLWidget::creaBuffersLego() {
    lego.load("../legoman.obj"); //carreguem Lego

    glGenVertexArrays(1, &VAO_Lego);
    glBindVertexArray(VAO_Lego);

    GLuint VBO_Lego[2];
    glGenBuffers(2, VBO_Lego);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Lego[0]); //localitzacio
    glBufferData (GL_ARRAY_BUFFER, //enviem VBOs a la GPU
                  sizeof(GLfloat) * lego.faces ().size () * 3 * 3,
                  lego.VBO_vertices (), GL_STATIC_DRAW);

    // Activem l'atribut vertexLoc
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

    for (unsigned int i = 0; i < lego.vertices().size(); i += 3) {
        p_max = glm::max(p_max, glm::vec3(lego.vertices()[i], lego.vertices()[i+1], lego.vertices()[i+2]));
        p_min = glm::min(p_min, glm::vec3(lego.vertices()[i], lego.vertices()[i+1], lego.vertices()[i+2]));

        Lmax = glm::max(Lmax, glm::vec3(lego.vertices()[i], lego.vertices()[i+1], lego.vertices()[i+2]));
        Lmin = glm::min(Lmin, glm::vec3(lego.vertices()[i], lego.vertices()[i+1], lego.vertices()[i+2]));
    }

    glEnableVertexAttribArray(vertexLoc);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Lego[1]); //colors
    glBufferData (GL_ARRAY_BUFFER, //enviem VBOs a la GPU
                  sizeof(GLfloat) * lego.faces ().size () * 3 * 3,
                  lego.VBO_matdiff (), GL_STATIC_DRAW);

    // Activem l'atribut colorLoc
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);

    glBindVertexArray (0);

}


void MyGLWidget::creaBuffersTerra() {
    glm::vec3 Colors[6];
    glm::vec3 Vertices[6];
    //terra 5x5 centrat a l'origen
    Vertices[0] = glm::vec3(-2.5f, 0.0f, -2.5f);
    Vertices[1] = glm::vec3(-2.5f,0.0f, 2.5f);
    Vertices[2] = glm::vec3(2.5f, 0.0f, 2.5f);
    Vertices[3] = glm::vec3(-2.5f, 0.0f, -2.5f);
    Vertices[4] = glm::vec3(2.5f,0.0f, 2.5f);
    Vertices[5] = glm::vec3(2.5f, 0.0f, -2.5f);

    Colors[0] = COLOR_BLAU;
    Colors[1] = COLOR_BLAU;
    Colors[2] = COLOR_BLAU;
    Colors[3] = COLOR_BLAU;
    Colors[4] = COLOR_BLAU;
    Colors[5] = COLOR_BLAU;

    glGenVertexArrays(1, &VAO_Terra);
    glBindVertexArray(VAO_Terra);

    GLuint VBO_Terra[2];
    glGenBuffers(2, VBO_Terra);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[0]); //localitzacio
    glBufferData (GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW); //enviem VBOs a la GPU

    // Activem l'atribut vertexLoc
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

    for (unsigned int i = 0; i < 6; ++i) {
        p_max = glm::max(p_max, Vertices[i]);
        p_min = glm::min(p_min, Vertices[i]);
    }

    glEnableVertexAttribArray(vertexLoc);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[1]); //colors
    glBufferData (GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW); //enviem VBOs a la GPU

    // Activem l'atribut colorLoc
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);

    glBindVertexArray (0);

}

void MyGLWidget::carregaShaders() { // declarem-lo també en MyGLWidget.h
    BL2GLWidget::carregaShaders(); // cridem primer al mètode de BL2GLWidget
    projLoc = glGetUniformLocation (program->programId(), "proj");
    viewLoc = glGetUniformLocation (program->programId(), "view");
}

void MyGLWidget::projectTransform () { //PM
    if (orthogonal) {
        glm::mat4 Proj = glm::ortho(-radi, radi, -radi, radi, d-radi, d+radi);
        glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
    }

    else {
        // glm::perspective(                     FOV,            rav,  znear, zfar)
        glm::mat4 Proj = glm::perspective (2*glm::asin(radi/d), 1.0f, d-radi, d+radi);
        glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
    }
}

void MyGLWidget::viewTransform() { //VM amb euler, CORRECTE
    glm::mat4 View(1.0);

    View = glm::translate(View, glm::vec3(0.0, 0.0, -d));
    View = glm::rotate(View, glm::radians(angle_0), glm::vec3(1.0, 0.0, 0.0)); //0
    View = glm::rotate(View, glm::radians(angle_trident), glm::vec3(1.0, 0.0, 0.0)); //tridente
    View = glm::translate(View, -centre);

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::modelTransformPatricio() {
    float escala = 4 / (Pmax.x - Pmin.y);
    escala += escala_extra;

    glm::vec3 cbase = glm::vec3((Pmax.x+Pmin.x)/2, Pmin.y, (Pmax.z+Pmin.z)/2);
    glm::mat4 TG (1.0);

    TG = glm::rotate(TG, glm::radians(180.0f), glm::vec3(1.0, 0.0, 0.0));
    TG = glm::scale(TG, glm::vec3(escala,escala,escala));
    TG = glm::translate(TG, -cbase);

    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformLego() {
    float escala = 2 / (Lmax.x - Lmin.y);
    escala += escala_extra / 100.0f; //la seva escala es diferent a la del patri

    glm::vec3 cbase = glm::vec3((Lmax.x+Lmin.x)/2, Lmin.y, (Lmax.z+Lmin.z)/2);
    glm::mat4 TG (1.0);

    TG = glm::scale(TG, glm::vec3(escala,escala,escala));
    TG = glm::translate(TG, -cbase);

    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformTerra() {
    glm::mat4 TG(1.0);
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

MyGLWidget::~MyGLWidget() {}

//SLOTS:

void MyGLWidget::canvia_FOV(int valor) { //canvia el radi sempre!!!!
    if (valor > prev_valor) { //zoom in
        radi += (float(valor) - float(prev_valor)) / 10.0f;
    }
    else { //zoom out
        radi -= (float(prev_valor) - float(valor)) / 10.0f;
    }

    prev_valor = valor;
    update();
}

void MyGLWidget::canvia_VAO(bool premut) {
    if (premut) {
        patricio = !patricio;
        update();
    }
}

void MyGLWidget::canvia_perspectiva(bool premut) {
    if (premut) {
        orthogonal = !orthogonal;
        update();
    }
}

void MyGLWidget::canvia_escala(int valor) {
    if (valor > escala_anterior) { //zoom in
        escala_extra += (float(valor) - float(escala_anterior)) / 10.0f;
    }
    else { //zoom out
        escala_extra -= (float(escala_anterior) - float(valor)) / 10.0f;
    }

    escala_anterior = valor;
    update();
}


