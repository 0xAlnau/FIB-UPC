#include <iostream>
#include <string>
#include <map>

using namespace std;

#include "BinTree.hh"

// Pre:  t és un arbre no buit que representa una expressió correcta
//       sobre naturals i variables enteres, i els operadors +,-,*.
//       Totes les variables que apareixen a t estan definides a variable2value.
//       Les operacions no produeixen errors d'overflow.
// Post: Retorna l'avaluació de l'expressió representada per t.
int evaluate(map<string,int> &variable2value, BinTree<string> t){
    int suma = 0;
    if (t.empty()) {}
    else{
        string value = t.value();
        if (value == "+" or value == "-" or value == "*") {
            if (value == "+") {
                return suma = evaluate(variable2value, t.left()) + evaluate(variable2value, t.right());
            }
            else if (value == "-") {
                return suma = evaluate(variable2value, t.left()) - evaluate(variable2value, t.right());
            }
            else if (value == "*") {
                return suma = evaluate(variable2value, t.left()) * evaluate(variable2value, t.right());
            }
        }

        else if (value >= "a" and value <= "z") {
            return suma = variable2value[value];
        }
        else {
            int num = atoi(t.value().c_str());
            return num;
        }
    }
    return suma;
}
