#include<iostream>
#include"Lavadora.hh"
#include"Cubeta.hh"
#include"Prenda.hh"
#include"readbool.hh"
using namespace std;
int main(){
    Lavadora w;
    Cubeta cu;
    int opcion;
    cin >> opcion;
    while (opcion != -8) {
        if (opcion == -1) {// inicializar lavadora (datos: peso máximo y color)
            int pm;
            cin >> pm;
            bool color;
            color = readbool();
            w.inicializar(pm, color);
        }
        else if (opcion == -2) {// añadir una prenda a la lavadora (datos: peso  y color de la prenda)
            int peso;
            bool color;
            cin >> peso;
            color = readbool();
            Prenda prenda(peso, color);
            w.anadir_prenda (prenda);

        }
        else if (opcion == -3) {// añadir una prenda a la cubeta (datos: peso  y color de la prenda)
            int peso;
            bool color;
            cin >> peso;
            color = readbool();
            Prenda prenda(peso, color);
            cu.anadir_prenda(prenda);
        }
        else if (opcion == -4) {// completar la lavadora
            cu.completar_lavadora(w);
        }
        else if (opcion == -5) {// realizar un lavado
            w.lavado();
        }
        else if (opcion == -6) {// escribir el contenido de la cubeta
            cu.escribir();
            cout << endl;
        }
        else if (opcion == -7) {// escribir el contenido de la lavadora
            w.escribir();
            cout << endl;
        }
        cin >> opcion;
    }
}

