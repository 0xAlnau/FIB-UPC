#include "ModelInfo.h"
#include "glwidget.h"

void ModelInfo::onPluginLoad()
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

void ModelInfo::preFrame()
{
	cout << "Hi ha " << num_obj << " objectes." << endl;
	cout << "Hi ha " << num_pol << " poligons." << endl;
	cout << "Hi ha " << num_ver << " vertexs." << endl;
	cout << "El percentatge de triangles és: " << (float(num_tri) / num_pol) * 100.0 << "%" << endl;
}

