//programa calculara potencias
//input: dos numeros enteros, a y b, siendo b >= 0
//output: a^b, suponiendo tambien que 0^0=1
#include<iostream>
using namespace std;
int main () {
    int a, b;

    while (cin >> a >> b) {
        int x= a * a;
        bool primero= true;
        for(int i=1; i < b-1; ++i){
            x= x * a;
        }
        if (b == 0){x= 1;}
        else if(b == 1){x= a;}
        cout << x <<endl;

    }

}
