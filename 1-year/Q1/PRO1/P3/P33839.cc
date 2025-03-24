// dada una secuencia de numeros, dara la suma de sus digitos
// input: una secuencia de numeros naturales
// output: una linia por cada numero, y la sumad de sus digitos
#include<iostream>
using namespace std;
int main () {
    int a;
    while (cin >> a) {
        int w= a;
        int suma= 0;
        while(w > 0){
            int x= w % 10;
            suma= suma + x;
            w= w / 10;
        }
        cout << "The sum of the digits of "<< a <<" is "<< suma <<"."<<endl;
    }
}
