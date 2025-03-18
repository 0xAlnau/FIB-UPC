#include <iostream>
#include <list>

using namespace std;

#include "BinTree.hh"
typedef BinTree<int> BT;

list<int> alcada_arbre(BT t) {
    list<int> cami;
    if (t.empty()) {}
    else {
        bool left_empty = t.left().empty();
        bool right_empty = t.right().empty();
        int value = t.value();
        if (not left_empty and not right_empty) {
            list<int> l_left = alcada_arbre(t.left());
            list<int> l_right = alcada_arbre(t.right());
            cami.push_front(value);

            int size_l = l_left.size(), size_r = l_right.size();
            if (size_l >= size_r) cami.splice(cami.end(), l_left);
            else cami.splice(cami.end(), l_right);
        }

        else if (not left_empty and right_empty) {
            list<int> l_left = alcada_arbre(t.left());
            cami.push_front(value);

            cami.splice(cami.end(), l_left);
        }

        else if (left_empty and not right_empty) {
            list<int> l_right = alcada_arbre(t.right());
            cami.push_front(value);

            cami.splice(cami.end(), l_right);
        }

        else { //dos buits
            cami.push_front(value);
        }
    }
    return cami;
}
// Pre:
// Post: Retorna la llista d'elements que es troben a t, baixant des de l'arrel i
//       seguint el camí més llarg. En cas de varis camins màxims,
//       escull el de més a l'esquerra.
list<int> longestLeftmostPath(BinTree<int> t){
    list<int> cami;
    if (t.empty()) {}
    else {
        cami = alcada_arbre(t);
    }
    return cami;
}


