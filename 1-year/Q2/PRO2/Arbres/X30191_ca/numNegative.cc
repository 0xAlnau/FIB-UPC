#include <iostream>
#include <string>

using namespace std;

#include "BinTree.hh"
typedef BinTree<string> BT;
int comptador = 0;

int numNegative2(BT t){
    int resultat = 0;
    if (t.empty()) {}
    else {
        string value = t.value();
        string l_value = "";
        string r_value = "";
        if (not t.left().empty()) l_value = t.left().value();
        if (not t.right().empty()) r_value = t.right().value();

        if (value == "+") { // "+"
            if ((l_value == "+" or l_value == "-" or l_value == "*") and
                (r_value == "+" or r_value == "-" or r_value == "*")) {
                    int enter1 = numNegative2(t.left());
                    int enter2 = numNegative2(t.right());
                    resultat = enter1 + enter2;
                    if (resultat < 0) ++comptador;

                }
            else if ((l_value == "+" or l_value == "-" or l_value == "*") and
                      not (r_value == "+" or r_value == "-" or r_value == "*")) {
                    int enter1 = numNegative2(t.left());
                    int enter2 = atoi(r_value.c_str());
                    resultat = enter1 + enter2;
                    if (resultat < 0) ++comptador;

                }
            else if (not (l_value == "+" or l_value == "-" or l_value == "*") and
                      (r_value == "+" or r_value == "-" or r_value == "*")) {
                    int enter1 = atoi(l_value.c_str());
                    int enter2 = numNegative2(t.right());
                    resultat = enter1 + enter2;
                    if (resultat < 0) ++comptador;

                }
            else if (not (l_value == "+" or l_value == "-" or l_value == "*") and
                      not (r_value == "+" or r_value == "-" or r_value == "*")) {
                    int enter1 = atoi(l_value.c_str());
                    int enter2 = atoi(r_value.c_str());
                    resultat = enter1 + enter2;
                    if (resultat < 0) ++comptador;

                }
        }

        else if (value == "-") { // "-"
            if ((l_value == "+" or l_value == "-" or l_value == "*") and
                (r_value == "+" or r_value == "-" or r_value == "*")) {
                    int enter1 = numNegative2(t.left());
                    int enter2 = numNegative2(t.right());
                    resultat = enter1 - enter2;
                    if (resultat < 0) ++comptador;

                }
            else if ((l_value == "+" or l_value == "-" or l_value == "*") and
                      not (r_value == "+" or r_value == "-" or r_value == "*")) {
                    int enter1 = numNegative2(t.left());
                    int enter2 = atoi(r_value.c_str());
                    resultat = enter1 - enter2;
                    if (resultat < 0) ++comptador;

                }
            else if (not (l_value == "+" or l_value == "-" or l_value == "*") and
                      (r_value == "+" or r_value == "-" or r_value == "*")) {
                    int enter1 = atoi(l_value.c_str());
                    int enter2 = numNegative2(t.right());
                    resultat = enter1 - enter2;
                    if (resultat < 0) ++comptador;

                }
            else if (not (l_value == "+" or l_value == "-" or l_value == "*") and
                      not (r_value == "+" or r_value == "-" or r_value == "*")) {
                    int enter1 = atoi(l_value.c_str());
                    int enter2 = atoi(r_value.c_str());
                    resultat = enter1 - enter2;
                    if (resultat < 0) ++comptador;

                }
        }

        else { // "*"
            if ((l_value == "+" or l_value == "-" or l_value == "*") and
                (r_value == "+" or r_value == "-" or r_value == "*")) {
                    int enter1 = numNegative2(t.left());
                    int enter2 = numNegative2(t.right());
                    resultat = enter1 * enter2;
                    if (resultat < 0) ++comptador;

                }
            else if ((l_value == "+" or l_value == "-" or l_value == "*") and
                      not (r_value == "+" or r_value == "-" or r_value == "*")) {
                    int enter1 = numNegative2(t.left());
                    int enter2 = atoi(r_value.c_str());
                    resultat = enter1 * enter2;
                    if (resultat < 0) ++comptador;

                }
            else if (not (l_value == "+" or l_value == "-" or l_value == "*") and
                      (r_value == "+" or r_value == "-" or r_value == "*")) {
                    int enter1 = atoi(l_value.c_str());
                    int enter2 = numNegative2(t.right());
                    resultat = enter1 * enter2;
                    if (resultat < 0) ++comptador;


                }
            else if (not (l_value == "+" or l_value == "-" or l_value == "*") and
                      not (r_value == "+" or r_value == "-" or r_value == "*")) {
                    int enter1 = atoi(l_value.c_str());
                    int enter2 = atoi(r_value.c_str());
                    resultat = enter1 * enter2;
                    if (resultat < 0) ++comptador;

                }
        }
    }
    return resultat;
}



// Pre:  t és un arbre no buit que representa una expressió correcta
//       sobre els naturals i els operadors +,-,*.
//       Les operacions no produeixen errors d'overflow.
// Post: Retorna el nombre de subexpressions de l'expressió representada per t
//       amb avaluació estrictament menor que 0.
int numNegative(BT t){
    int resultat = 0;
    if (t.empty()) {}
    else {
        string value = t.value();
        string l_value = "";
        string r_value = "";
        if (not t.left().empty()) l_value = t.left().value();
        if (not t.right().empty()) r_value = t.right().value();

        if (value == "+") { // "+"
            if ((l_value == "+" or l_value == "-" or l_value == "*") and
                (r_value == "+" or r_value == "-" or r_value == "*")) {
                    int enter1 = numNegative2(t.left());
                    int enter2 = numNegative2(t.right());
                    resultat = enter1 + enter2;
                    if (resultat < 0) ++comptador;
                }
            else if ((l_value == "+" or l_value == "-" or l_value == "*") and
                      not (r_value == "+" or r_value == "-" or r_value == "*")) {
                    int enter1 = numNegative2(t.left());
                    int enter2 = atoi(r_value.c_str());
                    resultat = enter1 + enter2;
                    if (resultat < 0) ++comptador;
                }
            else if (not (l_value == "+" or l_value == "-" or l_value == "*") and
                      (r_value == "+" or r_value == "-" or r_value == "*")) {
                    int enter1 = atoi(l_value.c_str());
                    int enter2 = numNegative2(t.right());
                    resultat = enter1 + enter2;
                    if (resultat < 0) ++comptador;
                }
            else if (not (l_value == "+" or l_value == "-" or l_value == "*") and
                      not (r_value == "+" or r_value == "-" or r_value == "*")) {
                    int enter1 = atoi(l_value.c_str());
                    int enter2 = atoi(r_value.c_str());
                    resultat = enter1 + enter2;
                    if (resultat < 0) ++comptador;
                }
        }

        else if (value == "-") { // "-"
            if ((l_value == "+" or l_value == "-" or l_value == "*") and
                (r_value == "+" or r_value == "-" or r_value == "*")) {
                    int enter1 = numNegative2(t.left());
                    int enter2 = numNegative2(t.right());
                    resultat = enter1 - enter2;
                    if (resultat < 0) ++comptador;
                }
            else if ((l_value == "+" or l_value == "-" or l_value == "*") and
                      not (r_value == "+" or r_value == "-" or r_value == "*")) {
                    int enter1 = numNegative2(t.left());
                    int enter2 = atoi(r_value.c_str());
                    resultat = enter1 - enter2;
                    if (resultat < 0) ++comptador;
                }
            else if (not (l_value == "+" or l_value == "-" or l_value == "*") and
                      (r_value == "+" or r_value == "-" or r_value == "*")) {
                    int enter1 = atoi(l_value.c_str());
                    int enter2 = numNegative2(t.right());
                    resultat = enter1 - enter2;
                    if (resultat < 0) ++comptador;
                }
            else if (not (l_value == "+" or l_value == "-" or l_value == "*") and
                      not (r_value == "+" or r_value == "-" or r_value == "*")) {
                    int enter1 = atoi(l_value.c_str());
                    int enter2 = atoi(r_value.c_str());
                    resultat = enter1 - enter2;
                    if (resultat < 0) ++comptador;
                }
        }

        else { // "*"
            if ((l_value == "+" or l_value == "-" or l_value == "*") and
                (r_value == "+" or r_value == "-" or r_value == "*")) {
                    int enter1 = numNegative2(t.left());
                    int enter2 = numNegative2(t.right());
                    resultat = enter1 * enter2;
                    if (resultat < 0) ++comptador;
                }
            else if ((l_value == "+" or l_value == "-" or l_value == "*") and
                      not (r_value == "+" or r_value == "-" or r_value == "*")) {
                    int enter1 = numNegative2(t.left());
                    int enter2 = atoi(r_value.c_str());
                    resultat = enter1 * enter2;
                    if (resultat < 0) ++comptador;
                }
            else if (not (l_value == "+" or l_value == "-" or l_value == "*") and
                      (r_value == "+" or r_value == "-" or r_value == "*")) {
                    int enter1 = atoi(l_value.c_str());
                    int enter2 = numNegative2(t.right());
                    resultat = enter1 * enter2;
                    if (resultat < 0) ++comptador;

                }
            else if (not (l_value == "+" or l_value == "-" or l_value == "*") and
                      not (r_value == "+" or r_value == "-" or r_value == "*")) {
                    int enter1 = atoi(l_value.c_str());
                    int enter2 = atoi(r_value.c_str());
                    resultat = enter1 * enter2;
                    if (resultat < 0) ++comptador;
                }
        }
    }
    resultat = comptador;
    comptador = 0;
    return resultat;
}
