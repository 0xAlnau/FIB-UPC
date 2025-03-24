//el programa indicara si el año introducido
//es bisiesto o no
//input: nombre natural entre 1800 y 9999 incluidos
//output: YES o NO dependiendo de si es o no bisiesto
#include<iostream>
using namespace std;
int main () {
    int a;
    cin >> a;

    if ( a % 4 == 0 and a % 400 ==0){cout << "YES" <<endl;}
    else if (a % 4 == 0){
        if (a % 10 == 0 and a % 100 == 0){cout << "NO" <<endl;}
        else {cout << "YES" <<endl;}
    }


    else{cout << "NO" <<endl;}

}
