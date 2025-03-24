//el programa te dara las horas, minutos y segundos de
//un numero n introducido por el usuario
//input: un numero natural n
//output: las horas, minutos y segundos, cumpliendo que
//n=600h+60m+s y m i s no pueden ser superior o igual a 60

#include<iostream>
using namespace std;
int main () {
    int n;
    cin >> n;
    int h=n / 3600;
    int m=(n % 3600) / 60;
    int s=(n % 3600) % 60;

    cout << h << " " << m << " " << s <<endl;
}
