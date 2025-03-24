#include<iostream>
using namespace std;

bool is_increasing(int n) {
    if (n / 10 == 0) {return true;}
    else {
        if (n % 10 >= (n / 10) % 10) {
            if (n / 10 != 0) {
                n = n / 10;
                return is_increasing(n);
            }
            else {return true;}
        }
        else {return false;}
    }

}

int main(){
    int numero;

    while (cin >> numero) {
        cout << is_increasing(numero) <<endl;
    }

}
