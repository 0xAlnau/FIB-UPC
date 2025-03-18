#include <iostream>
#include <string>
#include <map>

using namespace std;

#include "BinTree.hh"

// Pre:  t és un arbre no buit d'strings que representa una expressió correcta
//       sobre dígits i variables que guarden dígits, i els operadors +,* mòdul 10.
//       En particular, l'arrel de t és o bé +, o bé *, o bé un dígit, o bé una variable.
//       var2val és un mapeig de variables a dígits.
// Post: Retorna l'avaluació de l'expressió representada per t reemplaçant les variables
//       pels seus corresponents valors definits a var2val, o per 0 si no estan definides.
int evaluate(map<string,int> &var2val, BinTree<string> t){
    int resultat = 0;
    if (t.value() >= "0" and t.value() <= "9") {
        string s = t.value();
        resultat = atoi(s.c_str());
    }

    else {
        string v_esquerra = "^";
        string v_dreta = "^";
        if (not t.left().empty()) v_esquerra = t.left().value();
        if (not t.right().empty()) v_dreta = t.right().value();

        //mira si abans cal fer una altra avaluacio
        if ((v_esquerra == "*" or v_esquerra == "+" or v_esquerra == "-") and (v_dreta == "*" or v_dreta == "+" or v_dreta == "-")) {
            v_esquerra = to_string(evaluate(var2val, t.left()));
            v_dreta = to_string(evaluate(var2val, t.right()));
        }

        else if (v_esquerra == "*" or v_esquerra == "+" or v_esquerra == "-") {
            v_esquerra = to_string(evaluate(var2val, t.left()));
        }

        else if (v_dreta == "*" or v_dreta == "+" or v_dreta == "-") {
            v_dreta = to_string(evaluate(var2val, t.right()));
        }

        //avalua la expressio
        if (t.value() == "*") {
            if (v_esquerra >= "0" and v_esquerra <= "9" and v_dreta >= "0" and v_dreta <= "9") {
                int enter1 = atoi(v_esquerra.c_str());
                int enter2 = atoi(v_dreta.c_str());
                resultat = (enter1 * enter2) % 10;
            }

            else if (v_esquerra >= "0" and v_esquerra <= "9" and not (v_dreta >= "0" and v_dreta <= "9")) {
                int enter1 = atoi(v_esquerra.c_str());
                int enter2 = var2val[v_dreta];
                resultat = (enter1 * enter2) % 10;
            }

            else if (not (v_esquerra >= "0" and v_esquerra <= "9") and v_dreta >= "0" and v_dreta <= "9") {
                int enter1 = var2val[v_esquerra];
                int enter2 = atoi(v_dreta.c_str());
                resultat = (enter1 * enter2) % 10;
            }

            else if (not (v_esquerra >= "0" and v_esquerra <= "9") and not (v_dreta >= "0" and v_dreta <= "9")) {
                int enter1 = var2val[v_esquerra];
                int enter2 = var2val[v_dreta];
                resultat = (enter1 * enter2) % 10;
            }
        }

        else if (t.value() == "+") {
            if (v_esquerra >= "0" and v_esquerra <= "9" and v_dreta >= "0" and v_dreta <= "9") {
                int enter1 = atoi(v_esquerra.c_str());
                int enter2 = atoi(v_dreta.c_str());
                resultat = (enter1 + enter2) % 10;
            }

            else if (v_esquerra >= "0" and v_esquerra <= "9" and not (v_dreta >= "0" and v_dreta <= "9")) {
                int enter1 = atoi(v_esquerra.c_str());
                int enter2 = var2val[v_dreta];
                resultat = (enter1 + enter2) % 10;
            }

            else if (not (v_esquerra >= "0" and v_esquerra <= "9") and v_dreta >= "0" and v_dreta <= "9") {
                int enter1 = var2val[v_esquerra];
                int enter2 = atoi(v_dreta.c_str());
                resultat = (enter1 + enter2) % 10;
            }

            else if (not (v_esquerra >= "0" and v_esquerra <= "9") and not (v_dreta >= "0" and v_dreta <= "9")) {
                int enter1 = var2val[v_esquerra];
                int enter2 = var2val[v_dreta];
                resultat = (enter1 + enter2) % 10;
            }
        }

        else if (t.value() == "-") {
            if (v_esquerra >= "0" and v_esquerra <= "9" and v_dreta >= "0" and v_dreta <= "9") {
                int enter1 = atoi(v_esquerra.c_str());
                int enter2 = atoi(v_dreta.c_str());
                resultat = (enter1 - enter2) % 10;
            }

            else if (v_esquerra >= "0" and v_esquerra <= "9" and not (v_dreta >= "0" and v_dreta <= "9")) {
                int enter1 = atoi(v_esquerra.c_str());
                int enter2 = var2val[v_dreta];
                resultat = (enter1 - enter2) % 10;
            }

            else if (not (v_esquerra >= "0" and v_esquerra <= "9") and v_dreta >= "0" and v_dreta <= "9") {
                int enter1 = var2val[v_esquerra];
                int enter2 = atoi(v_dreta.c_str());
                resultat = (enter1 - enter2) % 10;
            }

            else if (not (v_esquerra >= "0" and v_esquerra <= "9") and not (v_dreta >= "0" and v_dreta <= "9")) {
                int enter1 = var2val[v_esquerra];
                int enter2 = var2val[v_dreta];
                resultat = (enter1 - enter2) % 10;
            }
        }

        //treiem el valor de la variable indicada
        else {
            resultat = var2val[t.value()];
        }
    }
    return resultat;
}

// Pre:  t és un arbre no buit d'strings que representa una instrucció correcta
//       del llenguatge de programació descrit a l'enunciat.
//       En particular, o bé és l'arbre buit,
//       o bé la seva arrel és, o bé =, o bé print, o bé if, o bé while,
//       o bé list, cas en el cual, representa una subllista d'instruccions.
// Post: S'ha simulat l'execució d'aquesta instrucció, modificant var2val
//       i escrivint el que calgui per la sortida estandar,
//       d'acord a aquesta simulació.
void execute(map<string,int> &var2val, BinTree<string> t){
    if (t.empty()) {}
    else {
        string operand = t.value();

        if (operand == "=") {
            if (t.right().empty()) var2val[t.left().value()] = 0;
            else var2val[t.left().value()] = evaluate(var2val, t.right());
        }

        else if (operand == "print") {
            cout << evaluate(var2val, t.left()) << endl;
        }

        else if (operand == "while"){
            int evaluation = evaluate(var2val, t.left());
            while (evaluation > 0 and evaluation <= 9) {
                execute(var2val, t.right());
                evaluation = evaluate(var2val, t.left());
            }
        }

        else if (operand == "if") {
            int evaluation = evaluate(var2val, t.left());
            if (evaluation > 0 and evaluation <= 9) {
                execute(var2val, t.right());
            }
        }

        else if (operand == "list") {
            execute(var2val, t.left());
            execute(var2val, t.right());
        }
    }
}
