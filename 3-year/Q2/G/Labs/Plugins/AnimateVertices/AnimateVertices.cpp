#include "AnimateVertices.h"
#include "glwidget.h"

void AnimateVertices::onPluginLoad()
{
	glwidget()->makeCurrent();
	// Vertex shader
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceFile("animate-vertices1.vert"); //carreguem arxiu
	cout << "VS log:" << vs->log().toStdString() << endl;
	// Fragment Shader
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("animate-vertices1.frag"); // <-- Cargamos desde el archivo
    cout << "FS log:" << fs->log().toStdString() << endl;
	// Program
	program = new QOpenGLShaderProgram(this);
	program->addShader(vs); program->addShader(fs);
	program->link();
	cout << "Link log:" << program->log().toStdString() << endl;

	// Timer
	elapsedTimer.start(); //comença crono

	timer = new QTimer(this);
	//          envia timeour quan 0   receptor    la acció a fer
	connect(timer, SIGNAL(timeout()), glwidget(), SLOT(update()));
	timer->start(1000);
}

//uniforms i tal
void AnimateVertices::preFrame()
{
	program->bind(); //activem

	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
	program->setUniformValue("modelViewProjectionMatrix", MVP);

	program->setUniformValue("amplitude", 0.1f); //f per no donar error ambiguetat

	program->setUniformValue("freq", 1);

	QMatrix3x3 NM = camera()->viewMatrix().normalMatrix(); //qt ens fa el calcul de normalMatrix
	program->setUniformValue("normalMatrix", NM);

	program->setUniformValue("time", float(elapsedTimer.elapsed()) / 1000.0f); //en segons

}

void AnimateVertices::postFrame()
{
	program->release(); //desactivem
}

