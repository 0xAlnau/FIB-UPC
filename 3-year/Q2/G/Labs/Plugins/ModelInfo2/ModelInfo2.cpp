#include "ModelInfo2.h"
#include "glwidget.h"

void ModelInfo2::onPluginLoad()
{
	vector<Object> obj = scene()->objects();
	num_obj = obj.size();

	for (int i = 0; i < num_obj; ++i) {
		vector<Face> fac = obj[i].faces();
		int m = fac.size();
		for (int j = 0; j < m; ++j) {
			if (fac[j].numVertices() == 3) ++num_tri;
		}

		num_pol += obj[i].faces().size();
		num_ver += obj[i].vertices().size();
	}
}

void ModelInfo2::postFrame()
{
	QFont font;
	font.setPixelSize(16);
	painter.begin(glwidget());
	painter.setFont(font);
	int x = 15;
	int y = 65;
	QString s1 = QString("Hi ha: %1 objectes.").arg(num_obj);
	QString s2 = QString("Hi ha: %1 poligons.").arg(num_pol);
	QString s3 = QString("Hi ha: %1 vertexs.").arg(num_ver);
	float percentatge = (float(num_tri) / num_pol) * 100.0;
	QString s4 = QString("El percentatge de triangles és: %1 %").arg(percentatge);

	painter.drawText(x, y-45, s1);
	painter.drawText(x, y-30, s2);
	painter.drawText(x, y-15, s3);
	painter.drawText(x, y, s4);

	painter.end();
	glwidget()->glBlendFunc(GL_ONE, GL_ZERO); //bug de qt6
}
