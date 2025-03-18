#include <iostream>

using namespace std;

#include "BinTree.hh"

// Pre:
// Post: Retorna la suma dels valors de t
int sumOfTree(BinTree<int> t){
    int sum = 0;
    if (t.empty()) {}
    else {
        sum = t.value();
        BinTree<int> left = t.left();
        BinTree<int> right = t.right();
        return sum = sum + sumOfTree(left) + sumOfTree(right);
    }
    return sum;
}
