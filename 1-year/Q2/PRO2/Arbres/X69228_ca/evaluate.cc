#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#include "BinTree.hh"

// Pre:  t és un arbre no buit que representa una expressió correcta
//       sobre strings de lletres minúscules i els operadors Concat, Reverse.
// Post: Retorna l'avaluació de l'expressió representada per t.
string evaluate(BinTree<string> t){
    string resultat = "";
    if (t.empty()) {}
    else {
        string value = t.value();
        if (value == "Reverse") {
            resultat += evaluate(t.left());
            reverse(resultat.begin(), resultat.end());
        }

        else if (value == "Concat") {
            resultat += evaluate(t.left()) + evaluate(t.right());
        }

        else {
            resultat = value;
        }
    }
    return resultat;
}
