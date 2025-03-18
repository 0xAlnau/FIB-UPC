#include <iostream>

using namespace std;

#include "BinTree.hh"

// Pre:
// Post: Retorna el nombre de nodes de t que no son l'arrel de t i que guarden un valor
//       estríctament major que el valor guardat al seu node pare.
int numIncreasing(BinTree<int> t){
    int resultat = 0;
    if (t.empty()) {}
    else {
        bool left_empty = t.left().empty();
        bool right_empty = t.right().empty();
        int l_value, r_value;
        int t_value = t.value();

        if (not left_empty and not right_empty) {
            l_value = t.left().value();
            r_value = t.right().value();
            if (l_value > t_value) ++resultat;
            if (r_value > t_value) ++resultat;

            resultat += numIncreasing(t.left()) + numIncreasing(t.right());
        }

        else if (not left_empty and right_empty) {
            l_value = t.left().value();
            if (l_value > t_value) ++resultat;

            resultat += numIncreasing(t.left());
        }

        else if (left_empty and not right_empty) {
            r_value = t.right().value();
            if (r_value > t_value) ++resultat;

            resultat += numIncreasing(t.right());
        }

        else {}
    }

    return resultat;
}
