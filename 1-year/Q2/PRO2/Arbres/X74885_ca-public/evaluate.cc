#include <iostream>
#include <string>

using namespace std;

#include "BinTree.hh"

// Pre:  t és un arbre no buit que representa una expressió correcta
//       sobre els naturals i els operadors +,-,*.
//       Les operacions no produeixen errors d'overflow.
// Post: Retorna l'avaluació de l'expressió representada per t.
int evaluate(BinTree<string> t){
    int sum = 0;
    if (t.empty()) {}
    else {
        string value = t.value();
        if (value == "+" or value == "-" or value == "*") {
            if (value == "+") {
                return sum = evaluate(t.left()) + evaluate(t.right());
            }

            else if (value == "-") {
                return sum = evaluate(t.left()) - evaluate(t.right());
            }

            else if (value == "*") {
                return sum = evaluate(t.left()) * evaluate(t.right());
            }
        }
        else{
            int num = atoi(t.value().c_str());
            return num;
        }
    }
    return sum;
}
