#include <iostream>
#include <string>

using namespace std;

#include "BinTree.hh"

// Pre:  t és un arbre no buit que representa una expressió booleana correcta
//       sobre els true,false i els operadors and,or,not.
// Post: Retorna l'avaluació de l'expressió representada per t.
bool evaluate(const BinTree<string> t){
    bool boolea = false;
    if (t.empty()) {}
    else {
        string operand = t.value();
        if (operand == "and") {
            boolea = evaluate(t.left()) and evaluate(t.right());
        }

        else if (operand == "or") {
            boolea = evaluate(t.left()) or evaluate(t.right());
        }

        else if (operand == "not") {
            boolea = not evaluate(t.left());
        }

        else if (operand == "true") {
            boolea = true;
        }

        else { // operand == false
            boolea = false;
        }
    }
    return boolea;
}
