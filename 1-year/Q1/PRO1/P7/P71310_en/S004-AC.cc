#include <iostream>
#include <vector>
using namespace std;
//esta función calculara el producto escalar
//entre dos vectores
//Pre: dos vectores con el mismo tamaño
//Post: un entero siendo este el producto escalar
double scalar_product(const vector<double>& u, const vector<double>& v) {
    int mida = u.size();
    double prod_escalar = 0;
    for (int i = 0; i < mida; ++i) {
        prod_escalar = prod_escalar + u[i] * v[i];
    }
    return prod_escalar;
}
