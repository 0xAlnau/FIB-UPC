#include <iostream>
#include <list>

using namespace std;

#include "BinTree.hh"
typedef BinTree<int> BT;
// Pre:
// Post: Retorna un arbre d'enters t' amb la mateixa estructura que t.
//       Per a cada posició p, el valor guardat a t' a posició p és igual a la suma
//       dels valors guardats a t a posició p i a posicions ancestres de p.
BinTree<int> treeOfSumsOfAncestors(const BT t){
    BT resultat = t;
    BT aux;
    if (resultat.empty()) {}
    else {
        int value = resultat.value();
        if (not resultat.left().empty() and not resultat.right().empty()) {
            int l_value = resultat.left().value();
            int r_value = resultat.right().value();
            BT left (value + l_value, resultat.left().left(), resultat.left().right());
            BT right (value + r_value, resultat.right().left(), resultat.right().right());
            return resultat = BT (value, treeOfSumsOfAncestors(left), treeOfSumsOfAncestors(right));
        }
        else if (not resultat.left().empty() and resultat.right().empty()) {
            int l_value = resultat.left().value();
            BT left (value + l_value, resultat.left().left(), resultat.left().right());
            return resultat = BT (value, treeOfSumsOfAncestors(left), treeOfSumsOfAncestors(aux));
        }

        else if (resultat.left().empty() and not resultat.right().empty()) {
            int r_value = resultat.right().value();
            BT right (value + r_value, resultat.right().left(), resultat.right().right());
            return resultat = BT (value, treeOfSumsOfAncestors(aux), treeOfSumsOfAncestors(right));
        }
    }
    return resultat;
}
