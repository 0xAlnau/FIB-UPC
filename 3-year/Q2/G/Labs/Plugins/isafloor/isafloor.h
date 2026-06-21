#ifndef _ISAFLOOR_H
#define _ISAFLOOR_H

#include "plugin.h" 

class Isafloor: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();

  private:
	// add private methods and attributes here
	QOpenGLShaderProgram* program;
    	QOpenGLShader *fs, *vs;
    	float lambda;
};

#endif
