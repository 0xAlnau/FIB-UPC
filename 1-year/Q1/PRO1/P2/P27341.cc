//el programa leera las parejas a i b dadas, y este
//tendra que hacer la suma de los cubos entre a y b
//input: parejas de enteros a y b
//output: una linia de texto mas la suma de todos los numeros

#include<iostream>
using namespace std;
int main () {
    int a, b,x=0;
   while (cin >> a){
       cin >> b;
       for (int i = a; i <= b; ++i){
           x= x + (i*i*i);
                                  }

       cout << "suma dels cubs entre "<< a <<" i "<< b <<":"<<" "<< x <<endl;
       x= 0;
}


}
