/** @file Producte.cc
    @brief Codi de la classe Producte.
*/

#include"Producte.hh"
//Constructores:
Producte::Producte(){}

Producte::Producte(int id_produ, int pes, int volum)
{
    this->id_produ = id_produ;
    this->pes = pes;
    this->volum = volum;
}


//Consultores:
int Producte::consul_pes() const
{
    return pes;
}

int Producte::consul_volum() const
{
    return volum;
}

int Producte::consul_id_produ() const
{
    return id_produ;
}
