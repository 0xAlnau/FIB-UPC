#ifndef _ANIMATEVERTICES_H
#define _ANIMATEVERTICES_H

#include "plugin.h" 
#include <QTimer>
#include <QElapsedTimer> //afegit tots dos!!!!

class AnimateVertices: public QObject, public Plugin
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
	QTimer* timer;
	QElapsedTimer elapsedTimer; //el cronòmetre
};

#endif
