#include <iostream>
#include <list>

using namespace std;

#include "BinTree.hh"
typedef BinTree<int> BT;
// Pre:
// Post: Retorna un arbre d'enters amb la mateixa estructura que t,
//       i a on cada subarbre té com a valor a l'arrel el nombre de nodes
//       del corresponent subarbre a t.
BT treeOfSizes(BT t){
    BT aux;
    BT resultat;
    if (t.empty()) {}
    else {
        bool left_empty = t.left().empty();
        bool right_empty = t.right().empty();

        if (not left_empty and not right_empty) {
            BT left = treeOfSizes(t.left());
            BT right = treeOfSizes(t.right());
            int sum = left.value() + right.value() + 1;
            resultat = BT (sum, left, right);
        }

        else if (not left_empty and right_empty) {
            BT left = treeOfSizes(t.left());
            int sum = left.value() + 1;
            resultat = BT (sum, left, aux);
        }

        else if (left_empty and not right_empty) {
            BT right = treeOfSizes(t.right());
            int sum = right.value() + 1;
            resultat = BT (sum, aux, right);
        }

        else {
            resultat = BT (1, aux, aux);
        }
    }
    return resultat;
}
