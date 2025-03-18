#include <iostream>

using namespace std;

#include "BinTree.hh"
typedef BinTree<int> BT;

BT ordenar (BT t, int& sum) {
    BT aux;
    BT resultat;
    if (t.empty()) {}
    else {
        bool left_empty = t.left().empty();
        bool right_empty = t.right().empty();

        if (not left_empty and not right_empty) {
            int sum_l = 0, sum_r = 0;
            BT left = ordenar(t.left(), sum_l);
            BT right = ordenar(t.right(), sum_r);
            sum += sum_l + sum_r + t.value();
            if (sum_r < sum_l) resultat = BT (t.value(), right, left);
            else resultat = BT (t.value(), left, right);
        }

        else if (not left_empty and right_empty) {
            int sum_l = 0;
            BT left = ordenar(t.left(), sum_l);
            sum += sum_l + t.value();
            if (0 < sum_l) resultat = BT (t.value(), aux, left);
            else resultat = BT (t.value(), left, aux);
        }

        else if (left_empty and not right_empty) {
            int sum_r = 0;
            BT right = ordenar(t.right(), sum_r);
            sum += sum_r + t.value();
            if (sum_r < 0) resultat = BT (t.value(), right, aux);
            else resultat = BT (t.value(), aux, right);
        }

        else { //els dos buits
            sum += t.value();
            resultat = BT (t.value(), aux, aux);
        }
    }
    return resultat;
}
// Pre: sigui T el valor inicial de t.
// Post: el valor retornat s'obté a partir de T a base de
// swapejar els fills esquerra i dret dels nodes de T
// que cumpleixen que la suma dels valors que penjen del seu fill esquerra és més gran
// que la suma dels valors que penjen del seu fill dret.
BT sortTree(BT t){
    BT resultat;
    if (t.empty()) {}
    else {
        int sum = 0;
        resultat = ordenar(t, sum);
    }
    return resultat;
}
