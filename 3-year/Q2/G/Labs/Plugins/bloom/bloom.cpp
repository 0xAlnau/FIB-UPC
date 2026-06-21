// GLarena, a plugin based platform to teach OpenGL programming
// © Copyright 2012-2018, ViRVIG Research Group, UPC, https://www.virvig.eu
// 
// This file is part of GLarena
//
// GLarena is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "bloom.h"
#include <QCoreApplication>

const int IMAGE_WIDTH = 1024;
const int IMAGE_HEIGHT = IMAGE_WIDTH;

void Bloom::onPluginLoad()
{
    GLWidget & g = *glwidget();
    g.makeCurrent();
    configurarEscena(); // Carreguem els objectes de l'escena
    
    // Carreguem el shader per l'efecte de bloom
    vs1 = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs1->compileSourceFile(g.getPluginPath()+"/../bloom/bloom.vert");

    fs1 = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs1->compileSourceFile(g.getPluginPath()+"/../bloom/bloom.frag");

    programBloom = new QOpenGLShaderProgram(this);
    programBloom->addShader(vs1);
    programBloom->addShader(fs1);
    programBloom->link();
    
    // Carreguem el shader pels colors dels objectes
    vs2 = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs2->compileSourceFile(g.getPluginPath()+"/../bloom/shading.vert");

    fs2 = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs2->compileSourceFile(g.getPluginPath()+"/../bloom/shading.frag");

    programShading = new QOpenGLShaderProgram(this);
    programShading->addShader(vs2);
    programShading->addShader(fs2);
    programShading->link();
    
    // Carreguem la textura de color
    QImage img1(g.getPluginPath()+"/../bloom/textureGrafics.png");	
	QImage im1 = img1.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
	g.makeCurrent(); 
	g.glActiveTexture(GL_TEXTURE0);
	g.glGenTextures( 1, &textureShadingId);
	g.glBindTexture(GL_TEXTURE_2D, textureShadingId);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im1.width(), im1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im1.bits());
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glBindTexture(GL_TEXTURE_2D, 0);

    // Carreguem la textura per fer l'efecte de bloom
    g.glGenTextures( 1, &textureBloomId);
    g.glBindTexture(GL_TEXTURE_2D, textureBloomId);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		      GL_LINEAR_MIPMAP_LINEAR );
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_WIDTH, IMAGE_HEIGHT,
		   0, GL_RGB, GL_FLOAT, NULL);
    g.glBindTexture(GL_TEXTURE_2D, 0);
    // Fem resize del viewport
    g.resize(IMAGE_WIDTH,IMAGE_HEIGHT);
}


void drawRect(GLWidget &g)
{
    static bool created = false;
    static GLuint VAO_rect;

    // 1. Create VBO Buffers
    if (!created)
    {
        created = true;
        

        // Create & bind empty VAO
        g.glGenVertexArrays(1, &VAO_rect);
        g.glBindVertexArray(VAO_rect);

        // Create VBO with (x,y,z) coordinates
        float coords[] = { -1, -1, 0, 
                            1, -1, 0, 
                           -1,  1, 0, 
                            1,  1, 0};

        GLuint VBO_coords;
        g.glGenBuffers(1, &VBO_coords);
        g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
        g.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
        g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        g.glEnableVertexAttribArray(0);
        g.glBindVertexArray(0);
    }

    // 2. Draw
    g.glBindVertexArray (VAO_rect);
    g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    g.glBindVertexArray(0);
}

void Bloom::setupShadingShader()
{
	GLWidget & g = *glwidget();
	// Configurar uniforms del shader de shading
	programShading->bind();
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    programShading->setUniformValue("modelViewProjectionMatrix", MVP);
    QMatrix3x3 normalMatrix = camera()->viewMatrix().normalMatrix();
    programShading->setUniformValue("normalMatrix", normalMatrix);
	g.glActiveTexture(GL_TEXTURE0);
	g.glBindTexture(GL_TEXTURE_2D, textureShadingId);
    programShading->setUniformValue("colorTexture", 0);
}

void Bloom::drawNormalObjects()
{
	setupShadingShader();
    programShading->setUniformValue("useLight", true);
    // Dibuixar l'objecte 0
    if (drawPlugin()) drawPlugin()->drawObject(0);
}

void Bloom::drawBloomObjects()
{
	setupShadingShader();
    programShading->setUniformValue("useLight", false);
    
    // Dibuixar l'objecte 1
    if (drawPlugin()) drawPlugin()->drawObject(1);
}

bool Bloom::paintGL()
{
    GLWidget & g = *glwidget();
    g.glClearColor(0,0,0,0);
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    // Pas 1. Dibuixar nomes la part on volem aplicar bloom
    // TODO: Fer que nomes es vegin les parts dels objectes on volem aplicar bloom 
    //       que no estan ocloses per cap objecte de l'escena.
    g.glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    drawNormalObjects();

    g.glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    drawBloomObjects();
    
    // Guardem la renderitzacio del pas 1 a la textura
    g.glBindTexture(GL_TEXTURE_2D, textureBloomId);
    g.glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0,
                          IMAGE_WIDTH, IMAGE_HEIGHT);
    g.glGenerateMipmap(GL_TEXTURE_2D);
    
    // Descomenteu aquesta linia per veure el resultat del pas 1
    // IMPORTANT: recordeu comentar-la abans d'entregar
    //return true;

    // Pas 2. Dibuixar l'escena final combinant els objectes normals amb els objectes amb bloom
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  	
    drawNormalObjects();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    // TODO: dibuixeu la imatge renderitzada en el pas 1 aplicant el shader de bloom que ja us donem
    glDisable(GL_DEPTH_TEST);
    drawRect(g);
    glEnable(GL_DEPTH_TEST);

	programBloom->bind();

    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    programBloom->setUniformValue("modelViewProjectionMatrix", MVP);
    programBloom->setUniformValue("colorMap", textureBloomId);
    programBloom->setUniformValue("SIZE", 1.0);
   
    glDisable(GL_BLEND);
    g.defaultProgram()->bind();
    g.glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}


void Bloom::configurarEscena()
{
	GLWidget & g = *glwidget();
	g.clearScene();
	g.addObjectFromFile(g.getPluginPath()+"/../bloom/Objecte1.obj");
	g.addObjectFromFile(g.getPluginPath()+"/../bloom/Objecte2.obj");
}


