#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#include "BinTree.hh"
#include <algorithm>
typedef BinTree<string> BT;

void hasdot (string s, bool& found, string& extension) {
    int size = s.length() -1;
    for (int i = size; not found and i != 0; --i) {
        if (s[i] == '.') found = true;
        else extension += s[i];
    }
    if (found) {
        reverse(extension.begin(), extension.end());
    }
}

// Pre:  Els nodes de 't' o bé son strings no buits de lletres minuscules, o bé
//       son de la forma "s.e", on s i e son strings no buits de lletres minúscules.
//       En l'últim cas, el node ha de ser una fulla, i e s'anomena la extensió de la fulla.
// Post: Retorna l'arbre resultant d'esborrar de t tots els nodes amb strings de
//       la forma "s.e" a on 'e' és igual a 'extension'.
BT removeAll(const string &extension, const BT &t){
    BT resultat = t;
    BT aux;
    if (t.empty()) {}
    else {
        bool dot = false, dot2 = false, dot_a = false;
        string exten = "", exten2 = "", exten_a = "";
        hasdot(t.value(), dot_a, exten_a);
        if (not t.left().empty()) hasdot(t.left().value(), dot, exten);
        if (not t.right().empty()) hasdot(t.right().value(), dot2, exten2);

        if (dot_a and exten_a == extension) {
            resultat = aux;
        }

        else if (dot and not dot2) {
            if (exten == extension) {
                resultat = BT (t.value(), aux, removeAll(extension, t.right()));
            }
            else if (exten != extension) {
                resultat = BT (t.value(), t.left(), removeAll(extension, t.right()));
            }
        }

        else if (not dot and dot2) {
            if (exten2 == extension) {
                resultat = BT (t.value(), removeAll(extension, t.left()), aux);
            }
            else if (exten2 != extension) {
                resultat = BT (t.value(), removeAll(extension, t.left()), t.right());
            }
        }

        else if (dot and dot2) {
            if (exten == extension and exten2 == extension) {
                resultat = BT (t.value(), aux, aux);
            }
            else if (exten == extension and exten2 != extension) {
                resultat = BT (t.value(), aux, t.right());
            }
            else if (exten != extension and exten2 == extension) {
                resultat = BT (t.value(), t.left(), aux);
            }
            else if (exten != extension and exten2 != extension) {
                resultat = BT (t.value(), t.left(), t.right());
            }
        }

        else if (not dot and not dot2) {
            resultat = BT (t.value(), removeAll(extension, t.left()), removeAll(extension, t.right()));
        }
    }
    return resultat;
}

