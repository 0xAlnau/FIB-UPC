#ifndef _MODELINFO2_H
#define _MODELINFO2_H

#include "plugin.h" 
#include <QPainter> //per al text

class ModelInfo2: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void postFrame();
  private:
	// add private methods and attributes here
	int num_obj;
	int num_pol = 0;
	int num_ver = 0;
	int num_tri = 0;
	QPainter painter; //per a text
};

#endif
