#ifndef _DRAWBOUNDINGBOX_H
#define _DRAWBOUNDINGBOX_H

#include "plugin.h" 
#include <QOpenGLShaderProgram>

class DrawBoundingBox: public QObject, public Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Plugin") 
    Q_INTERFACES(Plugin)

  public:
     void onPluginLoad();
     void postFrame();
     ~DrawBoundingBox();
     
  private:
    GLuint VAO;
    GLuint VBO_coords;
    GLuint EBO; // Buffer de Índices
    QOpenGLShaderProgram* program;
};

#endif
