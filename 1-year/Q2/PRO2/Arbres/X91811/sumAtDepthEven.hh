#include <iostream>

using namespace std;

#include "BinTree.hh"
typedef BinTree<int> BT;
int sumAtDepthEven(BT t);

int nofares(BT t) {
    int suma = 0;
    if (not t.left().empty()) {
        suma += sumAtDepthEven(t.left());
    }

    if (not t.right().empty()) {
        suma += sumAtDepthEven(t.right());
    }

    return suma;
}


// Pre:
// Post: Retorna la suma dels valors de t a profunditat parell
int sumAtDepthEven(BT t){
    int suma = 0;
    if (t.empty()) {}
    else {
        suma += t.value();
        if (not t.left().empty()) {
            suma += nofares(t.left());
        }

        if (not t.right().empty()) {
            suma += nofares(t.right());
        }
    }
    return suma;
}

