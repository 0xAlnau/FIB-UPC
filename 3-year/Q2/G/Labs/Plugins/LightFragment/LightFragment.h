#ifndef _LIGHTFRAGMENT_H
#define _LIGHTFRAGMENT_H

#include "plugin.h" 

class LightFragment: public QObject, public Plugin
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
	QOpenGLShaderProgram* program; //encapsula els shaders
	QOpenGLShader *fs, *vs;        //els shaders
};

#endif
