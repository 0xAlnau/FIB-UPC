/**
    @file Cubeta.hh
    @brief Especificación de la clase Cubeta
*/

#include"Cubeta.hh"

Cubeta::Cubeta() {}

Cubeta::Cubeta(const Cubeta& c) {
    ropacolor = c.ropacolor;
    ropablanca = c.ropablanca;
}

void Cubeta::anadir_prenda(const Prenda& p) {
    if (p.consul_color()) ropacolor.push(p);
    else ropablanca.push(p);
}

void Cubeta::completar_lavadora(Lavadora& lav) {
    if (lav.consultar_color()) completar_lavadora_pila_rec(ropacolor, lav);
    else completar_lavadora_pila_it(ropablanca, lav);
}

void Cubeta::escribir() const {
    cout << "   Cubeta: \nRopa de color de la cubeta: \n";
    escribir_pila_prenda(ropacolor);
    cout << "Ropa blanca de la cubeta: \n";
    escribir_pila_prenda(ropablanca);
}


void Cubeta::completar_lavadora_pila_rec(stack<Prenda>& p, Lavadora& l){
    if ((l.consultar_peso() == l.consultar_peso_maximo() or p.empty())) return;
    if (p.top().consul_peso() + l.consultar_peso() > l.consultar_peso_maximo()) return;
    l.anadir_prenda(p.top());
    p.pop();
    completar_lavadora_pila_rec(p, l);
}

void Cubeta::completar_lavadora_pila_it(stack<Prenda>& p, Lavadora& l) {
    while (l.consultar_peso() < l.consultar_peso_maximo() and not p.empty()) {
        if (p.top().consul_peso() + l.consultar_peso() <= l.consultar_peso_maximo()) {
            l.anadir_prenda(p.top());
            p.pop();
        }
        else return;
    }
}
void Cubeta::escribir_pila_prenda(const stack<Prenda>& p) {
    stack<Prenda> copia(p);
    while (not copia.empty()) {
        copia.top().escribir();
        copia.pop();
    }
}






