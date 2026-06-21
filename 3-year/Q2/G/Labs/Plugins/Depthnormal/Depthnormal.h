#ifndef _DEPTHNORMAL_H
#define _DEPTHNORMAL_H

#include "plugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

class Depthnormal: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();

	 bool paintGL();

  private:
	// add private methods and attributes here
        QOpenGLShaderProgram* program;
        QOpenGLShaderProgram* program2;
    	QOpenGLShader* vsD;
    	QOpenGLShader* fsD;
    	QOpenGLShader* vsN;
    	QOpenGLShader* fsN;    
};

#endif
