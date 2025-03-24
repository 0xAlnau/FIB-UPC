//el programa dara la vuelta al numero natural introducido por el usuario
//input: un numero natural
//output: el numero natural al revés, con el máximo de ceros posible
#include<iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    if (n == 0 or 00 or 000){cout << "0";}
    else{
    while (n > 0) {
        cout << n % 10;
        n = n / 10;
    }


    }

    cout<< endl;
}
