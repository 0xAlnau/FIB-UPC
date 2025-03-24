//dado un numero, el prgrama tendra que representarlo
//de la base 2 hasta la 16
//input: un numero k, del 1 al 10^8
//15 linias, representando cada base i diciendo
//el numero de cifras que corresponde

#include<iostream>
using namespace std;
int main() {
    int n;
    cin >> n;

    for(int b= 2; b <= 16; ++b) {
        int w= n; //variable temporal para poder realizar la accion 16 veces
        int c= 0;
        while (w > 0){

            w= w / b;
            c= c + 1;

        }
        cout << "Base "<< b <<": "<< c << " cifras."<<endl;

    }
}
