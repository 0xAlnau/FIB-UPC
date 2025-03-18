#include <iostream>
#include <list>

using namespace std;

#include "BinTree.hh"
typedef BinTree<int> BT;
// Pre:
// Post: Retorna un arbre d'enters amb la mateixa estructura que t,
//       i a on cada subarbre té com a arrel la suma dels nodes del corresponent subarbre a t.
BT treeOfSums(BT t){
    BT aux;
    BT resultat;
    if (t.empty()){}
    else{
        bool left_empty = t.left().empty();
        bool right_empty = t.right().empty();
        int value = t.value();

        if (not left_empty and not right_empty) {
            BT left = treeOfSums(t.left());
            BT right = treeOfSums(t.right());

            int sum = value + left.value() + right.value();
            resultat = BT (sum, left, right);
        }

        else if (not left_empty and right_empty) {
            BT left = treeOfSums(t.left());

            int sum = value + left.value();
            resultat = BT (sum, left, aux);
        }

        else if (left_empty and not right_empty) {
            BT right = treeOfSums(t.right());

            int sum = value + right.value();
            resultat = BT (sum, aux, right);
        }

        else {
            resultat = BT (value, aux, aux);
        }
    }

    return resultat;
}
