//el programa dibujara octagonos segun el numero introducido
//input: numeros naturales iguales o superiores a 2
//output: el octagono de medida n
#include<iostream>
using namespace std;
int main () {
    int n;
    while (cin >> n) {
        int w= 0;
        for (int i= 1; i < n; ++i) {
            for (int j= 0; j < n - i; ++j) {
                cout << " ";
            }
            for (int k= 2; k < n + i * 2; ++k){
                cout << "X";
                w= k;
            }

            cout <<endl;
       }
        for (int l= 0; l < n; ++l ) {
            for (int m= 0; m < w + 1; ++m){
                cout<<"X";
            }
            cout << endl;
        }

        for (int o= 1; o < n; ++o) {
            for (int p= 0; p < o; ++p){
                cout << " ";
            }

            for (int q= 0; q <= w - o*2; ++q) {
                cout << "X";
            }
           cout << endl;
        }
        cout << endl;
   }
}
