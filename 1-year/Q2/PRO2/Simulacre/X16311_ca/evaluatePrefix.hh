#include <iostream>
#include <string>

using namespace std;

#include "BinTree.hh"



string aux_evaluatePrefix(BinTree<string> t, int& n){
    string resultat = "";
    if (t.empty() or n <= 0) {}
    else {
        string operand = t.value();

        if (operand == "Reverse") {
            int n_l = n;
            string left = aux_evaluatePrefix(t.left(), n_l);
            if (left.length() >= n) {
                left = string(left.rbegin(), left.rend());
                left = left.substr(0, n);
                resultat = left;
                n = 0;
            }

            else {
                left = string(left.rbegin(), left.rend());
                resultat = left;
                n = n - resultat.length();
            }

        }

        else if (operand == "Concat") {
            int n_l = n, n_r = n;
            string left = "", right = "";
            left = aux_evaluatePrefix(t.left(), n_l);
            if (left.length() >= n) {
                left = left.substr(0, n);
                n = 0;
            }

            else n = n - left.length();

            if (n > 0) {
                right = aux_evaluatePrefix(t.right(), n_r);
                if (right.length() >= n) {
                    right = right.substr(0, n);
                    n = 0;
                }
                else n = n - right.length();
            }
            resultat = left + right;
        }

        else {
            resultat = operand;
        }
    }
    return resultat;
}

// Pre:  t és un arbre no buit que representa una expressió correcta
//       sobre strings de lletres minúscules i els operadors Concat, Reverse.
//       n>=0
// Post: Retorna el prefix de longitut n de l'avaluació de l'expressió representada per t.
//       En cas que n sigui més gran que la longitut d'aquesta avaluació,
//       llavors retorna només l'avaluació, cap caràcter més.
string evaluatePrefix(BinTree<string> t, int n){
    string resultat = "";
    if (t.empty() or n <= 0) {}
    else {
        string operand = t.value();

        if (operand == "Reverse") {
            int n_l = n;
            string left = aux_evaluatePrefix(t.left(), n_l);
            if (left.length() >= n) {
                left = string(left.rbegin(), left.rend());
                left = left.substr(0, n);
                resultat = left;
                n = 0;
            }

            else {
                left = string(left.rbegin(), left.rend());
                resultat = left;
                n = n - resultat.length();
            }

        }

        else if (operand == "Concat") {
            int n_l = n, n_r = n;
            string left = "", right = "";
            left = aux_evaluatePrefix(t.left(), n_l);
            if (left.length() >= n) {
                left = left.substr(0, n);
                n = 0;
            }

            else n = n - left.length();

            if (n > 0) {
                right = aux_evaluatePrefix(t.right(), n_r);
                if (right.length() >= n) {
                    right = right.substr(0, n);
                    n = 0;
                }
                else n = n - right.length();
            }
            resultat = left + right;
        }

        else {
            resultat = operand;
        }
    }
    return resultat;
}
