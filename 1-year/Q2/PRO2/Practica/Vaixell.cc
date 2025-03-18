/** @file Vaixell.cc
    @brief Codi de la classe Vaixell.
*/

#include"Vaixell.hh"
//Constructora:
Vaixell::Vaixell() {}


//Consultores:
pair<int,int> Vaixell::consul_compr() const
{
    return comprar_produ;
}

pair<int,int> Vaixell::consul_vend() const
{
    return vendre_produ;
}


//Modificadores:
void Vaixell::canviar_atributs(int id1, int id2, int comp, int vend)
{
    comprar_produ.first = id1;
    comprar_produ.second = comp;

    vendre_produ.first = id2;
    vendre_produ.second = vend;
}

void Vaixell::afegir_a_ruta(string id_ciutat)
{
    llocs_visitats.push_back(id_ciutat);
}

void Vaixell::ruta_buida(){
    llocs_visitats.clear();
}


//Escriure:
void Vaixell::escriure_vaixell() const
{
    cout << comprar_produ.first << " " << comprar_produ.second << " " << vendre_produ.first << " " << vendre_produ.second << endl;

    list<string>::const_iterator it = llocs_visitats.begin();
    list<string>::const_iterator end = llocs_visitats.end();
    while (it != end) {
        cout << *it << endl;
        ++it;
    }
}
