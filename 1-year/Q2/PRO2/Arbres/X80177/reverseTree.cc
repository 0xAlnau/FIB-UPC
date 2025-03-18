#include <iostream>

using namespace std;

#include "BinTree.hh"

// Pre:  
// Post: retorna el revessat de t.
BinTree<int> reverseTree(BinTree<int> t){
    BinTree<int> resultat;
    if (t.empty()) {}
    else {
        resultat = BinTree<int> (t.value(), reverseTree(t.right()), reverseTree(t.left()));
    }
    return resultat;
}
