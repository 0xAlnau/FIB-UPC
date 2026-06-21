#include "ShowDegree.h"
#include "glwidget.h"

void ShowDegree::onPluginLoad()
{
	vector<Object> obj = scene()->objects();
	for (int i = 0; i < 1; ++i) {
		int n = obj[i].vertices().size();
		vector<int> numVert = vector<int>(n, 0);
		vector<Face> fac = obj[i].faces();
		int m = fac.size();

		for (int j = 0; j < m; ++j) {
			numVert[fac[j].vertexIndex(0)]++;
			numVert[fac[j].vertexIndex(1)]++;
			numVert[fac[j].vertexIndex(2)]++;
		}

		int suma = 0;
		for (int x : numVert) suma += x;
		grauMig = suma / float(n);
	}

}

void ShowDegree::postFrame()
{
	QFont font;
	font.setPixelSize(16);
	painter.begin(glwidget());
	painter.setFont(font);
	int x = 15;
	int y = 50;
	QString s = QString("Grau mig és: %1").arg(grauMig);
	painter.drawText(x, y, s);

	painter.end();
	glwidget()->glBlendFunc(GL_ONE, GL_ZERO); //bug de qt6
}


