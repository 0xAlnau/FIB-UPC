#include<iostream>
using namespace std;

int main(){
    int number;
    cin >> number;
    bool impar = true;
    int suma = 0;

    if (number == 0) cout << "0 IS COOL" <<endl;
    else {
        int aux = number;
        while (number != 0) {
            if (impar) {
                suma += number % 10;
                impar = false;
            }

            else {
                impar = true;
            }
            number = number / 10;
        }
        if (suma % 2 == 0) cout << aux << " IS COOL" << endl;
        else cout << aux << " IS NOT COOL" << endl;
    }
}
