#include "LightFragment.h"
#include "glwidget.h"

void LightFragment::onPluginLoad()
{
	glwidget()->makeCurrent();

    // Vertex shader
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("lighting4.vert"); //carreguem arxiu
    cout << "VS log:" << vs->log().toStdString() << endl;

    // Fragment Shader
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("lighting4.frag"); // <-- Cargamos desde el archivo
    cout << "FS log:" << fs->log().toStdString() << endl;

    // Program
    program = new QOpenGLShaderProgram(this);
    program->addShader(vs); program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;

}

void LightFragment::preFrame()
{
	program->bind();

	//matrius
	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);

	QMatrix4x4 MV = camera()->viewMatrix();
    program->setUniformValue("modelViewMatrix", MV);

	QMatrix3x3 NM = camera()->viewMatrix().normalMatrix(); //qt ens fa el calcul de normalMatrix
    program->setUniformValue("normalMatrix", NM);

	//lum
    QVector4D lightAmbient(0.1f, 0.1f, 0.1f, 1.0f);  // Luz ambiental baja
    QVector4D lightDiffuse(1.0f, 1.0f, 1.0f, 1.0f);  // Luz difusa blanca
    QVector4D lightSpecular(1.0f, 1.0f, 1.0f, 1.0f); // Luz especular blanca

	QVector4D matAmbient(1.0f, 0.1f, 0.1f, 1.0f);  // Luz ambiental baja
    QVector4D matDiffuse(1.0f, 1.0f, 1.0f, 1.0f);  // Luz difusa blanca
    QVector4D matSpecular(1.0f, 1.0f, 1.0f, 1.0f); // Luz especular blanca
	float shi = 0.5;

    QVector4D lightPosition(0.0f, 0.0f, 0.0f, 1.0f);

    // 3. Enviar los uniforms al shader
    program->setUniformValue("lightAmbient", lightAmbient);
    program->setUniformValue("lightDiffuse", lightDiffuse);
    program->setUniformValue("lightSpecular", lightSpecular);
    program->setUniformValue("lightPosition", lightPosition);

	program->setUniformValue("matAmbient", matAmbient);
    program->setUniformValue("matDiffuse", matDiffuse);
    program->setUniformValue("matSpecular", matSpecular);
    program->setUniformValue("matShininess", shi);

}

void LightFragment::postFrame()
{
	program->release();
}
