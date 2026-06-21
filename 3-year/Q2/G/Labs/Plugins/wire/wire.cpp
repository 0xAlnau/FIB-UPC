#include "wire.h"
#include "glwidget.h"

void Wire::onPluginLoad()
{
    // Carregar shader, compile & link
    QString vs_src =
      "#version 330 core\n"
      "uniform mat4 modelViewProjectionMatrix;"
      "uniform mat3 normalMatrix;"
      "in vec3 vertex;"
      "in vec3 color;"
      "in vec3 normal;"
      "out vec4 col;"
      "void main() {"
      "  vec3 N = normalize(normalMatrix * normal);"
      "  gl_Position = modelViewProjectionMatrix * vec4(vertex,1.0);"
      "  col=vec4(vec3(N.z),1.0);"
      "}";
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceCode(vs_src);
    cout << "VS log:" << vs->log().toStdString() << endl;

    QString fs_src =
      "#version 330 core\n"
      "out vec4 fragColor;"
      "in vec4 col;"
      "uniform int fase;"
      "void main() {"
      "  if (fase == 1) fragColor=col;"
      "  else fragColor = vec4(vec3(0.0), 1.0);"
      "}";
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceCode(fs_src);
    cout << "FS log:" << fs->log().toStdString() << endl;

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;
}

bool Wire::paintGL()
{
	glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
	program->bind();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(1.0f, 1.0f);
	
	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
	program->setUniformValue("modelViewProjectionMatrix", MVP);
	
	QMatrix3x3 NM = camera()->viewMatrix().normalMatrix(); //qt ens fa el calcul de normalMatrix
	program->setUniformValue("normalMatrix", NM);
	
	program->setUniformValue("fase", int(1));
	
	if (drawPlugin()) 
        	drawPlugin()->drawScene();
        
        glDisable(GL_POLYGON_OFFSET_FILL);
        
        //segona pasada
        program->bind();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        program->setUniformValue("fase", int(2));
        
        if (drawPlugin()) 
        	drawPlugin()->drawScene();
	
	return true; // return true only if implemented
}
