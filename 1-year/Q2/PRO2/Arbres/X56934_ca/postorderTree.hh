#include <iostream>

using namespace std;

#include "BinTree.hh"
typedef BinTree<int> BT;

BT ordre(BT t, int& orde) {
    BT resultat;
    BT aux;
    if (t.empty()) {}
    else {
        bool left_empty = t.left().empty();
        bool right_empty = t.right().empty();

        if (not left_empty and not right_empty) {
            BT left = ordre(t.left(), orde);
            ++orde;
            BT right = ordre(t.right(), orde);
            ++orde;

            resultat = BT (orde, left, right);
        }

        else if (not left_empty and right_empty) {
            BT left = ordre(t.left(), orde);
            ++orde;

            resultat = BT (orde, left, aux);
        }

        else if (left_empty and not right_empty) {
            BT right = ordre(t.right(), orde);
            ++orde;

            resultat = BT (orde, aux, right);
        }

        else {
            resultat = BT (orde, aux, aux);
        }
    }
    return resultat;
}


// Pre:  Sigui T el valor inicial de l'arbre t que es rep com a paràmetre.
// Post: Sigui T' l'arbre retornat. T i T' tenen exactament la mateixa estructura.
//       Sigui n1,n2,...,nk els nodes de T' en el recorregut en postordre de T'.
//       Llavors, n1 guarda el valor 1, n2 guarda el valor 2, ..., nk guarda el valor k.
BT postorderTree(BT t){
    BT resultat;
    if (t.empty()) {}
    else {
        int num = 1;
        resultat = ordre(t, num);
    }
    return resultat;
}
