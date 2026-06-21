#include "TextureSplatting.h"
#include "glwidget.h"

void TextureSplatting::onPluginLoad()
{
    GLWidget &g = *glwidget();
    g.makeCurrent();
    // Vertex shader
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("splatting.vert"); //carreguem arxiu
    cout << "VS log:" << vs->log().toStdString() << endl;
    // Fragment Shader
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("splatting.frag");
    cout << "FS log:" << fs->log().toStdString() << endl;
    // Program
    program = new QOpenGLShaderProgram(this);
    program->addShader(vs); program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;

    // Load Texture 1
    QString filename = QFileDialog::getOpenFileName(0, "Open Image", "/assig/grau-g/Textures", "rock.png");	
    QImage img0(filename);	
	
    QImage im0 = img0.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();

    g.makeCurrent();
    g.glActiveTexture(GL_TEXTURE0);
    g.glGenTextures( 1, &textureId0);
    g.glBindTexture(GL_TEXTURE_2D, textureId0);
    g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, im0.width(), im0.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im0.bits());
    g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    g.glBindTexture(GL_TEXTURE_2D, 0);
    
    // Load Texture 2
    QString filename1 = QFileDialog::getOpenFileName(0, "Open Image", "/assig/grau-g/Textures", "grass.png");	
    QImage img1(filename1);	
	
    QImage im1 = img1.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();

    g.makeCurrent();
    g.glActiveTexture(GL_TEXTURE1);
    g.glGenTextures( 1, &textureId1);
    g.glBindTexture(GL_TEXTURE_2D, textureId1);
    g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, im1.width(), im1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im1.bits());
    g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    g.glBindTexture(GL_TEXTURE_2D, 0);
    
    // Load Texture 3
    QString filename2 = QFileDialog::getOpenFileName(0, "Open Image", "/assig/grau-g/Textures", "noise.png");	
    QImage img2(filename2);	
	
    QImage im2 = img2.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();

    g.makeCurrent();
    g.glActiveTexture(GL_TEXTURE2);
    g.glGenTextures( 1, &textureId2);
    g.glBindTexture(GL_TEXTURE_2D, textureId2);
    g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, im2.width(), im2.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im2.bits());
    g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    g.glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureSplatting::preFrame()
{
    GLWidget &g = *glwidget();
    g.makeCurrent();

    // bind shader and define uniforms
    program->bind();
    program->setUniformValue("rock1", 0);  // texture unit del primer sampler 
    program->setUniformValue("grass2", 1);  // texture unit del segon  sampler
    program->setUniformValue("noise0", 2);  // texture unit del tercer  sampler 
    program->setUniformValue("modelViewProjectionMatrix", g.camera()->projectionMatrix() * g.camera()->viewMatrix());
    // bind textures
    g.glActiveTexture(GL_TEXTURE0);
    g.glBindTexture(GL_TEXTURE_2D, textureId0);
    g.glActiveTexture(GL_TEXTURE1);
    g.glBindTexture(GL_TEXTURE_2D, textureId1);
    g.glActiveTexture(GL_TEXTURE2);
    g.glBindTexture(GL_TEXTURE_2D, textureId2);
}

void TextureSplatting::postFrame()
{
    GLWidget &g = *glwidget();
    g.makeCurrent();

    // bind default shaders
    g.defaultProgram()->bind();
    // unbind textures
    g.glActiveTexture(GL_TEXTURE0);
    g.glBindTexture(GL_TEXTURE_2D, 0);
    g.glActiveTexture(GL_TEXTURE1);
    g.glBindTexture(GL_TEXTURE_2D, 0);
    g.glActiveTexture(GL_TEXTURE2);
    g.glBindTexture(GL_TEXTURE_2D, 0);	
}

