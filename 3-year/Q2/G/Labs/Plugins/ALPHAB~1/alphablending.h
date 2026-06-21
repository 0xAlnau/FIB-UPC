#ifndef _ALPHABLENDING_H
#define _ALPHABLENDING_H

#include "plugin.h" 

class Alphablending: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void preFrame();
	 void postFrame();
  private:
	// add private methods and attributes here
};

#endif
