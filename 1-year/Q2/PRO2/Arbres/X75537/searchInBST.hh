#include <iostream>
#include <list>

using namespace std;

#include "BinTree.hh"

// Pre: t és un BST
// Post: Retorna cert si i només si x apareix a t
bool searchInBST(BinTree<int> t, int x){
    if (t.empty()) {
        return false;
    }
    else {
        int value = t.value();
        if (value == x) return true;
        else {
            if (x < value) {
                return searchInBST(t.left(), x);
            }
            else {
                return searchInBST(t.right(), x);
            }
        }
    }
    return false;
}
