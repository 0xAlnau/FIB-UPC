//el programa leera un numero natural y dara como salida la
//suma de sus tres ultimos digitos
//input: un numero natural igual o mayor a 100
//output: un linia con la suma de los ultimos 3 digitos
#include<iostream>
using namespace std;
int main () {
    int a;
    cin >> a;
    int x= a % 10;
    int x1= a / 10;
    int y= x1 % 10;
    int y1= x1 / 10;
    int z= y1 % 10;
    int n= x+y+z;
    cout << n <<endl;

}
