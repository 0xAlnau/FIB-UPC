#include <iostream>

using namespace std;

#include "BinTree.hh"

// Pre: Rep dos arbres binaris d'enters positius a1 i a2.
// Post: Retorna una arbre, on a la seva arrel hi ha el màxim de les arrels de a1,a2, després,
// en l'arrel del fill esquerra, el màxim de les arrels dels fills esquerra de a1,a2,
// i així successivament.
// Quan un dels arbres no té valors definits en alguna posició, l'arbre resultant hi té
// el valor de l'altre arbre en aquella posició.

BinTree<int> maximumTree(BinTree<int> a1, BinTree<int> a2){
    BinTree<int> resultat;
    if (a1.empty() and a2.empty()) {}

    else {
        int max;
        if (a1.empty()) max = a2.value();
        else if (a2.empty()) max = a1.value();
        else {
            int value1 = a1.value();
            int value2 = a2.value();
            if (value1 >= value2) max = value1;
            else max = value2;
        }

        BinTree<int> aux;

        if (a2.left().empty() and a2.right().empty() and
            a1.left().empty() and a1.right().empty()) {}

        else if (a2.left().empty() and a2.right().empty() and not a1.left().empty() and not a1.right().empty()) {
            return resultat = BinTree<int> (max, a1.left(), a1.right());
        }

        else if (a2.left().empty() and a2.right().empty() and a1.left().empty() and not a1.right().empty()) {
            return resultat = BinTree<int> (max, aux, a1.right());
        }

        else if (a2.left().empty() and a2.right().empty() and not a1.left().empty() and a1.right().empty()) {
            return resultat = BinTree<int> (max, a1.left(), aux);
        }

        else if (a2.left().empty() and not a1.left().empty() and not a1.right().empty() and not a2.right().empty()) {
            return resultat = BinTree<int> (max, a1.left(), maximumTree(a1.right(), a2.right()));
        }

        else if (a2.right().empty() and not a1.left().empty() and not a1.right().empty() and not a2.left().empty()) {
            return resultat = BinTree<int> (max, maximumTree(a1.left(), a2.left()), a1.right());
        }

        else if (a1.left().empty() and a1.right().empty() and not a2.left().empty() and not a2.right().empty()) {
            return resultat = BinTree<int> (max, a2.left(), a2.right());
        }

        else if (a1.left().empty() and a1.right().empty() and a2.left().empty() and not a2.right().empty()) {
            return resultat = BinTree<int> (max, aux, a2.right());
        }

        else if (a1.left().empty() and a1.right().empty() and not a2.left().empty() and a2.right().empty()) {
            return resultat = BinTree<int> (max, a2.left(), aux);
        }

        else if (a1.left().empty() and not a2.left().empty() and not a2.right().empty() and not a1.right().empty()) {
            return resultat = BinTree<int> (max, a2.left(), maximumTree(a1.right(), a2.right()));
        }

        else if (a1.right().empty() and not a2.left().empty() and not a2.right().empty() and not a1.left().empty()) {
            return resultat = BinTree<int> (max, maximumTree(a1.left(), a2.left()), a2.right());
        }

        else if (not a2.left().empty() and not a2.right().empty() and not a1.left().empty() and not a1.right().empty()){
            return resultat = BinTree<int> (max, maximumTree(a1.left(), a2.left()), maximumTree(a1.right(), a2.right()));
        }

    }
    return resultat;
}

