#include "alphablending.h"
#include "glwidget.h"

void Alphablending::preFrame()
{
	glDisable(GL_DEPTH_TEST);
	
	glBlendEquation(GL_FUNC_ADD); //quina operació
	glBlendFunc(GL_SRC_ALPHA, GL_ONE); //quins sumem
	glEnable(GL_CULL_FACE); //eliminar les cares que no apunten cap a nosaltres
	glEnable(GL_BLEND);
}

void Alphablending::postFrame()
{
	glEnable(GL_DEPTH_TEST); //deixem tot tal i com estava
	glDisable(GL_BLEND);
}
