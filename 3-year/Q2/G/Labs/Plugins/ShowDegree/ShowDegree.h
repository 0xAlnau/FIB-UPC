#ifndef _SHOWDEGREE_H
#define _SHOWDEGREE_H

#include "plugin.h"
#include <QPainter> //per al text

class ShowDegree: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void postFrame();
  private:
	// add private methods and attributes here
	  QPainter painter; //per a text
	  float grauMig;
};

#endif
