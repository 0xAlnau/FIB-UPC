#include <iostream>
#include <string>

using namespace std;

#include "BinTree.hh"

// Pre:  t és un arbre no buit que representa una expressió booleana correcta
//       sobre els valors true,false i els operadors and,or,not.
// Post: Retorna un arbre binari de booleans
//       que té el mateix conjunt de posicions que t.
//       A més a més, per a cada posició p, el subarbre a posició p de t
//       representa una expressió que s'avalua a true si i només si
//       hi ha el valor true a la posició p de l'arbre retornat.
BinTree<bool> treeOfEvaluations(BinTree<string> t){
    BinTree<bool> resultat;
    BinTree<bool> aux; //empty
    if (t.empty()) {}
    else {
        string operand = t.value();
        if (operand == "and") {
            BinTree<bool> left = treeOfEvaluations(t.left());
            BinTree<bool> right = treeOfEvaluations(t.right());
            bool value = left.value() and right.value();
            resultat = BinTree<bool> (value, left, right);
        }

        else if (operand == "or") {
            BinTree<bool> left = treeOfEvaluations(t.left());
            BinTree<bool> right = treeOfEvaluations(t.right());
            bool value = left.value() or right.value();
            resultat = BinTree<bool> (value, left, right);
        }

        else if (operand == "not") {
            BinTree<bool> left = treeOfEvaluations(t.left());
            bool value = not left.value();
            resultat = BinTree<bool> (value, left, aux);
        }

        else if (operand == "true") {
            bool value = true;
            resultat = BinTree<bool> (value, aux, aux);
        }

        else { // operand == false
            bool value = false;
            resultat = BinTree<bool> (value, aux, aux);
        }
    }
    return resultat;
}
