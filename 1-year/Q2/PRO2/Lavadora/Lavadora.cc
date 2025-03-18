/** @file Lavadora.cc
    @brief Especificación de la clase Lavadora
*/
#include"Lavadora.hh"
Lavadora::Lavadora() {
    ini = false;
    pes = 0;
}

void Lavadora::inicializar(int pmax, bool col){
    pesmax = pmax;
    this ->col = col;
    ini = true;
    pes = 0;
    prendas.clear();
}

void Lavadora::anadir_prenda (const Prenda& p){
    prendas.insert(prendas.end(), p);
    pes += p.consul_peso();
}

void Lavadora::escribir() const {
    if (not ini) {
        cout << "   Lavadora: "<<endl;
        cout << "Lavadora no inicializada" <<endl;
    }
    else {
        cout << "   Lavadora: \nLavadora de " << (col?"color":"blanco") << ", con peso actual " <<pes<< " y peso maximo " << pesmax << "; sus prendas son\n";
        for (list<Prenda>::const_iterator it = prendas.begin(); it != prendas.end(); ++it) {
            Prenda roba = *it;
            roba.escribir();
        }
    }

}

void Lavadora::lavado() {
    ini = false;
    pes = 0;
}

bool Lavadora::esta_inicializada() const {return ini;}

bool Lavadora::consultar_color() const {return col;}

int Lavadora::consultar_peso() const {return pes;}

int Lavadora::consultar_peso_maximo() const {return pesmax;}
