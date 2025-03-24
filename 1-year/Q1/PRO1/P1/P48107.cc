//el programa leera dos numeros enteros, y este hara la
//division de estos dos, como respuesta dara la division
//integra y tambien el residuo de la division
//input: dos numeros enteros, y el segundo mas grande de 0
//output: la division integra y el residuo de la division

#include<iostream>
using namespace std;
int main () {
    int a, b;
    cin >> a >> b;
    int d=a/b;
    int r=a%b;

    cout << d << " " << r <<endl;


}
