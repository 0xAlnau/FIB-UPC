#include <iostream>

using namespace std;

#include "BinTree.hh"
typedef BinTree<int> BT;

BT calculate(BT t, int& sum, bool even){
    BT resultat;
    BT aux;
    if (t.empty()) {}
    else {
        bool left_empty = t.left().empty();
        bool right_empty = t.right().empty();

        if (not left_empty and not right_empty) {
            if (even) {
                even = false;
                int sum_l = 0;
                int sum_r = 0;
                BT left = calculate(t.left(), sum_l, even);
                BT right = calculate(t.right(), sum_r, even);
                sum += t.value() + sum_l + sum_r;
                resultat = BT (sum, left, right);
            }

            else {
                even = true;
                int sum_l = 0;
                int sum_r = 0;
                BT left = calculate(t.left(), sum_l, even);
                BT right = calculate(t.right(), sum_r, even);
                sum += t.value() + sum_l + sum_r;
                resultat = BT (t.value(), left, right);
            }
        }

        else if (not left_empty and right_empty) {
            if (even) {
                even = false;
                int sum_l = 0;
                BT left = calculate(t.left(), sum_l, even);
                sum += t.value() + sum_l;
                resultat = BT (sum, left, aux);
            }

            else {
                even = true;
                int sum_l = 0;
                BT left = calculate(t.left(), sum_l, even);
                sum += t.value() + sum_l;
                resultat = BT (t.value(), left, aux);
            }
        }

        else if (left_empty and not right_empty) {
            if (even) {
                even = false;
                int sum_r = 0;
                BT right = calculate(t.right(), sum_r, even);
                sum += t.value() + sum_r;
                resultat = BT (sum, aux, right);
            }

            else {
                even = true;
                int sum_r = 0;
                BT right = calculate(t.right(), sum_r, even);
                sum += t.value() + sum_r;
                resultat = BT (t.value(), aux, right);
            }
        }

        else {
            sum += t.value();
            resultat = BT (t.value(), aux, aux);
        }
    }
    return resultat;
}

// Pre:  Sigui T el valor inicial de t.
// Post: Retorna un arbre d'enters R amb la mateixa estructura que T.
//       Per a cada posició p de T i R, si p és a profunditat senar,
//       llavors T i R tenen el mateix valor a posició p.
//       En canvi, si p es a profunditat parell, llavors el valor de R a posició
//       p és la suma de tots els valors que es troben a T a posició p o per sota.
BT SumBelowAtEvenDepth(BT t){
    BT resultat;
    if(t.empty()){}
    else {
        bool even = true;
        int sum = 0;
        resultat = calculate(t, sum, even);
    }
    return resultat;
}
