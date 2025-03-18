#include <iostream>
#include <list>

using namespace std;

#include "BinTree.hh"

// Pre:
// Post: Retorna un arbre d'enters amb la mateixa estructura que t,
//       i a on cada subarbre té com a arrel la seva alçada.
BinTree<int> treeOfHeights(BinTree<int> t){
    BinTree<int> resultat;
    BinTree<int> aux;
    if (t.empty()) {
        resultat = BinTree<int> (0, aux, aux);
    }
    else {
        bool left_empty = t.left().empty();
        bool right_empty = t.right().empty();

        if (left_empty and right_empty) {
            resultat = BinTree<int> (1, aux, aux);
        }

        else if (not left_empty and not right_empty) {
            BinTree<int> left = treeOfHeights(t.left());
            BinTree<int> right = treeOfHeights(t.right());

            int value1 = left.value(), value2 = right.value();
            if (value1 >= value2) resultat = BinTree<int> (value1 + 1, left, right);
            else resultat = BinTree<int> (value2 + 1, left, right);
        }

        else if (not left_empty and right_empty) {
            BinTree<int> left = treeOfHeights(t.left());

            int value1 = left.value();
            resultat = BinTree<int> (value1 + 1, left, aux);
        }

        else if (left_empty and not right_empty) {
            BinTree<int> right = treeOfHeights(t.right());

            int value2 = right.value();
            resultat = BinTree<int> (value2 + 1, aux, right);
        }
    }
    return resultat;
}
