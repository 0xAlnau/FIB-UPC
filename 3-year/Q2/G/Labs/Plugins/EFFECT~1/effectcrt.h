#ifndef _EFFECTCRT_H
#define _EFFECTCRT_H

#include "plugin.h" 

class Effectcrt: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();

  private:
	// add private methods and attributes here
	//per fer shaders!!!
	QOpenGLShaderProgram* program; //encapsula els shaders
	QOpenGLShader *fs, *vs;        //els shaders
};

#endif
