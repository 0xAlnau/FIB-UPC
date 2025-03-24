#include<iostream>
#include<string>
using namespace std;
//esta acción  cambia el orden de las letras
//de un string
//Pre: un string
//Post: el string cambiado de orden
void cambiar_letras (string palabra) {
    int mida = palabra.length();
    for (int i = 0; i < mida / 2; ++i) {
        char aux = palabra[i];
        palabra[i] = palabra[mida -1 -i];
        palabra[mida -1 -i] = aux;
    }
    cout << palabra <<endl;
}
//esta acción cambia el orden de una lista de  n palabras
//Pre: un natural indicando el numero de palabras en la lista
//Post: las palabras cambiadas de orden
void change_order_everything(int n) {
    if (n == 0) {}
    else {
        string palabra;
        if (cin >> palabra) {
            change_order_everything(n -1);
            cambiar_letras(palabra);
        }
    }

}
//este programa llamará a una acción, que cambiara el
//orden de las palabras y tambien el orden de las letras
//de cada palabra;
int main(){
    int n;
    cin >> n;
    change_order_everything(n);
}
