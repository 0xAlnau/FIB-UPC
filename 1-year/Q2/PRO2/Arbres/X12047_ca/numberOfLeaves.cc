#include <iostream>

using namespace std;

#include "BinTree.hh"
// Pre:
// Post: Retorna el nombre de fulles de t
int numberOfLeaves(BinTree<int> t){
    int comptador = 0;
    if (t.empty()) {}
    else {
        if (not t.left().empty() and not t.right().empty()) {
            comptador += numberOfLeaves(t.left()) + numberOfLeaves(t.right());
        }

        else if (not t.left().empty() and t.right().empty()) {
            comptador += numberOfLeaves(t.left());
        }

        else if (t.left().empty() and not t.right().empty()) {
            comptador += numberOfLeaves(t.right());
        }

        else if (t.left().empty() and t.right().empty()){
            comptador += 1;
        }

    }
    return comptador;
}
