/** @file Inventari.cc
    @brief Codi de la classe Inventari.
*/

#include"Inventari.hh"
//Constructora:
Inventari::Inventari(){
    pes_total = 0;
    volum_total = 0;
}


//Funció privada:
void Inventari::modif_nece(int id_produ, int valor)
{
    produc_nece[id_produ] += valor;
}


//Consultores:
int Inventari::consul_mida_invent() const
{
    return produc_te.size();
}

bool Inventari::existeix_produ(int id_produ) const
{
    bool existeix = false;
    if (produc_nece.count(id_produ) == 1) existeix = true;
    return existeix;
}

int Inventari::consul_pes_total() const
{
    return pes_total;
}

int Inventari::consul_volum_total() const
{
    return volum_total;
}

int Inventari::consul_nece(int id_produ) const
{
    return produc_nece.at(id_produ);
}

int Inventari::consul_te(int id_produ) const
{
    return produc_te.at(id_produ);
}

int Inventari::consul_sobr(int id_produ) const
{
    int te = consul_te(id_produ);
    int nece = consul_nece(id_produ);
    int sobr = te - nece;
    return sobr;
}


//Modificadores:
void Inventari::comerciar(Inventari& i2)
{
    map<int,int>::iterator it1 = produc_nece.begin();
    map<int,int>::iterator end1 = produc_nece.end();
    map<int,int>::iterator it2 = i2.produc_nece.begin();
    map<int,int>::iterator end2 = i2.produc_nece.end();

    while ((it1 != end1) and (it2 != end2)) {
        if (it1->first == it2->first) {
            int sobr1 = consul_sobr(it1->first);
            int sobr2 = i2.consul_sobr(it1->first);
            if ((sobr1 < 0 and sobr2 < 0) or (sobr1 == 0 or sobr2 == 0)) {} //els dos inventaris necessiten, no poden intercanviar
            else if (sobr1 > 0 and sobr2 < 0) { //el primer inventari donarà a la segona
                if (abs(sobr2) <= sobr1) { //comprovació per veure si li sobren més al inventari1 del que necessita el inventari2
                    modif_te(it1->first, -abs(sobr2));
                    i2.modif_te(it1->first, abs(sobr2));
                }
                else { //sino, c1 dona tot el que pot
                    modif_te(it1->first, -sobr1);
                    i2.modif_te(it1->first, sobr1);
                }
            }
            else if (sobr1 < 0 and sobr2 > 0) {
                if (abs(sobr1) <= sobr2) {
                    modif_te(it1->first, abs(sobr1));
                    i2.modif_te(it1->first, -abs(sobr1));
                }
                else {
                    modif_te(it1->first, sobr2);
                    i2.modif_te(it1->first, -sobr2);
                }
            }
            else {} //els dos inventaris els sobra, no cal fer res
            ++it1;
            ++it2;
        }

        else if (it1->first > it2->first) ++it2;
        else ++it1;
    }
}

void Inventari::eliminar_produ_inventari(int id_produ)
{
    int te = consul_te(id_produ);
    modif_te(id_produ, -te);

    produc_te.erase(id_produ);
    produc_nece.erase(id_produ);
    producs_inventari.erase(id_produ);
}

void Inventari::afegir_produ_inventari(const Producte& produ, int te, int nece)
{
    int id_produ = produ.consul_id_produ();
    producs_inventari[id_produ] = produ;
    modif_te(id_produ, te);
    modif_nece(id_produ, nece);
}

void Inventari::modif_produ(const Producte& produ, int te, int nece)
{
    int id_produ = produ.consul_id_produ();
    eliminar_produ_inventari(id_produ);
    afegir_produ_inventari(produ, te, nece);
}

void Inventari::modif_te(int id_produ, int valor)
{
    int pes = producs_inventari[id_produ].consul_pes();
    int volum = producs_inventari[id_produ].consul_volum();
    produc_te[id_produ] += valor;
    if (valor <= 0) {
        for (int i = valor; i < 0; ++i) {
            pes_total -= pes;
            volum_total -= volum;
        }
    }

    else {
        for (int j = 0; j < valor; ++j) {
            pes_total += pes;
            volum_total += volum;
        }
    }
}


//Escriure:
void Inventari::escriure_inventari() const
{
    map<int,int>::const_iterator its = produc_te.begin();
    map<int,int>::const_iterator itn = produc_nece.begin();
    map<int,int>::const_iterator end = produc_te.end();

    while (its != end) {
        cout << its->first << " " << its->second << " " << itn->second << endl; //its->first mostrarà l'identificador del producte
        ++its;
        ++itn;
    }
    cout << pes_total << " " << volum_total << endl;
}


