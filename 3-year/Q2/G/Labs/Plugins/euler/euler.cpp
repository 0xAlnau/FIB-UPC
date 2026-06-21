#include "euler.h"
#include "glwidget.h"
#include <set>

void Euler::onPluginLoad()
{
	vector<Object> obj = scene()->objects();
	num_obj = obj.size();

	for (int i = 0; i < num_obj; ++i) {
		num_pol = obj[i].faces().size();
		num_ver = obj[i].vertices().size();

		// Conjunto para almacenar aristas únicas
        set<pair<int, int>> edges;

        // Recorremos todas las caras del objeto actual
        const vector<Face>& faces = obj[i].faces();
        for (int j = 0; j < num_pol; ++j) {
            const Face& face = faces[j];
            int num_v = face.numVertices(); // Número de vértices de esta cara concreta

            // Recorremos los vértices de la cara para formar las aristas
            for (int k = 0; k < num_v; ++k) {
                // Obtenemos el índice del vértice actual y el del siguiente
                // Usamos módulo (%) para que el último vértice se conecte con el primero
                int v1 = face.vertexIndex(k);
                int v2 = face.vertexIndex((k + 1) % num_v);

                // Ordenamos los índices de menor a mayor
                int min_v = min(v1, v2);
                int max_v = max(v1, v2);

                // Insertamos la arista en el conjunto (si ya existe, el set la ignora)
                edges.insert({min_v, max_v});
            }
        }

        // El número total de aristas es simplemente el tamaño del conjunto
        int num_edges = edges.size();

        cout << "F=" << num_pol << endl;
        cout << "V=" << num_ver << endl;
        cout << "E=" << num_edges << endl;
        cout << "X=" << num_pol + num_ver - num_edges << endl; // X = F + V - E
        cout << endl;
	}
}

void Euler::onObjectAdd()
{
	cout << "Carreguem nous models:" << endl;
	cout << "----------------------" << endl;
	onPluginLoad();
}

