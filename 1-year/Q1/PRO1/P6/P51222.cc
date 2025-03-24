#include <iostream>
using namespace std;

int number_of_digits(int n){
    int comptador = 0;
    if (n >= 0 and n <= 9) ++comptador;
    else{
        ++comptador;
        comptador += number_of_digits(n / 10);
    }
    return comptador;
}

