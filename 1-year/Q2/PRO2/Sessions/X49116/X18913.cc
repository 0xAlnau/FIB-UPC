#include<vector>
using namespace std;

/* Pre: cierto */
/* Post: si el resultado es v.size(), x no esta en v;
en caso contrario, indica la posicion de la primera aparicion de x en v */
int busqueda_lin(const vector<int>& v, int x) {
    int size = v.size();
    bool found = false;
    int numfound = size;
    for (int i = 0; not found and i < size; ++i) {
        if (v[i] == x) {
            found = true;
            numfound = i;
        }
    }
    return numfound;
}
