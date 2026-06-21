#ifndef _EULER_H
#define _EULER_H

#include "plugin.h" 

class Euler: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void onObjectAdd();

  private:
	// add private methods and attributes here
	int num_obj;
	int num_pol = 0;
	int num_ver = 0;
	int num_tri = 0;
};

#endif
