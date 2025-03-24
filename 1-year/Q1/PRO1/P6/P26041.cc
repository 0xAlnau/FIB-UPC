#include<iostream>
#include<string>
using namespace std;

    void change_order() {
    string palabra;
    if (cin >> palabra) {
        change_order();
        cout << palabra <<endl;
    }

}

//el programa llamarÃ¡ una funcion donde se leeran palabras
//e imprimira las palabras en orden contrario
//output:una linia con cada palabra en orden contrario
int main(){
    change_order();
}
