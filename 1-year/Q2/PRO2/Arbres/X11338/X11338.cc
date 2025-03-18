#include "BinTree.hh"
#include "ParInt.hh"
#include <iostream>
using namespace std;
typedef BinTree<ParInt> BT;

/*Pre: a = A */
/*Post: a es com a A amb k sumat al segon component de cada node */
void sumak(BT& a, int k){
    if (a.empty()) {}
    else {
        int arrel_r = a.value().segon() + k;
        ParInt arrel (a.value().primer(), arrel_r);
        BT left = a.left();
        BT right = a.right();
        sumak(left, k);
        sumak(right, k);
        a = BT (arrel, left, right);
    }
}

