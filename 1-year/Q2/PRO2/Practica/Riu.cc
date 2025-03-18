/** @file Riu.cc
    @brief Codi de la classe Riu.
*/

#include"Riu.hh"
//Constructora:
Riu::Riu()
{
    id_producte_actual = 1;

    //Declaració de tots els productes inicials:
    int n_produ;
    cin >> n_produ;
    for (int i = 0; i < n_produ; ++i) declarar_producte();

    //Declaració de la conca:
    llegir_conca();
    //Declaracio vaixell:
    int id1, id2, comp, vend;
    cin >> id1 >> comp;
    cin >> id2 >> vend;
    vaixell.canviar_atributs(id1, id2, comp, vend);
    vaixell.ruta_buida();
}


//Funcions privades:
BT Riu::modificar_conca()
{
    BT resultat;
    string node;
    Inventari inventari;
    cin >> node;
    if (node != "#") {
        id2Inventari[node] = inventari;
        BT left, right;
        left = modificar_conca();
        right = modificar_conca();
        resultat = BT (node, left, right);
    }

    else {} //"resultat" serà buit
    return resultat;
}

void Riu::comerc_global(const BT& t)
{
    if (t.empty()) {} //cas base
    else {
        bool left_empty = t.left().empty();
        if (not left_empty) { //si té un fill, es segur que tindrà l'altre
            string node_l = t.left().value();
            string node_r = t.right().value();
            id2Inventari[t.value()].comerciar(id2Inventari[node_l]);
            id2Inventari[t.value()].comerciar(id2Inventari[node_r]);

            comerc_global(t.left());
            comerc_global(t.right());
        }

        else {} //les dues buides
    }
}

list<int> Riu::calcular_ruta(const BT& t, int& comprat, int& venut, const pair<int,int>& vol_compr, const pair<int,int>& vol_vendre)
{
    list<int> resultat;

    if (t.empty() or (comprat == vol_compr.second and venut == vol_vendre.second)) {} //cas base
    else {
        string value = t.value();
        if(id2Inventari[value].existeix_produ(vol_compr.first) and comprat != vol_compr.second) {
            int sob = id2Inventari[value].consul_sobr(vol_compr.first);
            if (sob <= 0) {}
            else {
                comprat += sob;
                if (comprat > vol_compr.second) { //ha comprat més del que toca
                    comprat = vol_compr.second;
                }
            }
        }

        if(id2Inventari[value].existeix_produ(vol_vendre.first) and venut != vol_vendre.second) {
            int sob = id2Inventari[value].consul_sobr(vol_vendre.first);
            if (sob >= 0) {}
            else {
                venut += abs(sob);
                if (venut > vol_vendre.second) { //ha venut més del que toca
                    venut = vol_vendre.second;
                }
            }
        }

        int comprat_l = comprat, comprat_r = comprat, venut_l = venut, venut_r = venut;
        list<int> ruta_l = calcular_ruta(t.left(), comprat_l, venut_l, vol_compr, vol_vendre);
        list<int> ruta_r = calcular_ruta(t.right(), comprat_r, venut_r, vol_compr, vol_vendre);

        if (comprat_l + venut_l > comprat_r + venut_r) {
            resultat.push_front(1);
            comprat = comprat_l;
            venut = venut_l;
            resultat.splice(resultat.end(), ruta_l);
        }
        else if (comprat_l + venut_l < comprat_r + venut_r){
            resultat.push_front(0);
            comprat = comprat_r;
            venut = venut_r;
            resultat.splice(resultat.end(), ruta_r);
        }
        else if (comprat_l != comprat or comprat_r != comprat or venut_l != venut or venut_r != venut) { //igual d'aprofitoses
            if (ruta_l.size() <= ruta_r.size()) {
                resultat.push_front(1);
                comprat = comprat_l;
                venut = venut_l;
                resultat.splice(resultat.end(), ruta_l);
            }
            else {
                resultat.push_front(0);
                comprat = comprat_r;
                venut = venut_r;
                resultat.splice(resultat.end(), ruta_r);
            }
        }
    }
    return resultat;
}

void Riu::realitzar_viatge(const BT& t, list<int> ruta, pair<int,int>& vol_compr, pair<int,int>& vol_vendre)
{
    if (ruta.empty() or (vol_compr.second == 0 and vol_vendre.second == 0)) {} //cas base
    else {
        string value = t.value();
        if (id2Inventari[value].existeix_produ(vol_compr.first) and vol_compr.second != 0) {
            int sob = id2Inventari[value].consul_sobr(vol_compr.first);
            if (sob <= 0) {} //no li sobren productes
            else {
                if (vol_compr.second - sob < 0) { //comprovar que no ens passem de comprar
                    sob = vol_compr.second;
                }
                vol_compr.second -= sob;
                id2Inventari[value].modif_te(vol_compr.first, -sob);
            }
        }
        if (id2Inventari[value].existeix_produ(vol_vendre.first) and vol_vendre.second != 0) {
            int sob = id2Inventari[value].consul_sobr(vol_vendre.first);
            if (sob >= 0) {}
            else{
                if(vol_vendre.second - abs(sob) < 0) { //comprovar que no ens passem de vendre
                    sob = vol_vendre.second;
                }
                vol_vendre.second -= abs(sob);
                id2Inventari[value].modif_te(vol_vendre.first, abs(sob));
            }

        }

        if (ruta.front() == 1) {
            ruta.pop_front();
            realitzar_viatge(t.left(), ruta, vol_compr, vol_vendre);
        }
        else if (ruta.front() == 0){
            ruta.pop_front();
            realitzar_viatge(t.right(), ruta, vol_compr, vol_vendre);
        }
        else { //acabar la ruta
            vaixell.afegir_a_ruta(value);
        }
    }
}


//Consultores:
int Riu::num_productes() const
{
    return id_producte_actual - 1; //hem de restar 1 perquè sinó retornarà com si tingués un producte més del que hi ha
}

bool Riu::ciutat_exis(string id_ciutat) const
{
    bool existeix = false;
    if (id2Inventari.count(id_ciutat) == 1) existeix = true;
    return existeix;
}

bool Riu::produ_exis(int id_producte) const
{
    bool existeix = false;
    if (id2Producte.count(id_producte) == 1) existeix = true;
    return existeix;
}


//Modificadores:
void Riu::redistribuir()
{
    comerc_global(arbre_id_ciutats);
}

void Riu::viatge()
{
    int comprat = 0, venut = 0;
    pair<int,int> comprar_v = vaixell.consul_compr();
    pair<int,int> vendre_v = vaixell.consul_vend();
    list<int> ruta = calcular_ruta(arbre_id_ciutats, comprat, venut, comprar_v, vendre_v);
    ruta.push_back(-1); //centinela per parar de fer la ruta

    if (comprat == 0 and venut == 0) {} //si no ha comprat res no cal viatjar
    else realitzar_viatge(arbre_id_ciutats, ruta, comprar_v, vendre_v);
    cout << comprat + venut << endl;

}

void Riu::declarar_producte()
{
    int pes, volum;
    cin >> pes >> volum;
    Producte produ(id_producte_actual, pes, volum);
    id2Producte[id_producte_actual] = produ;
    ++id_producte_actual;
}

void Riu::llegir_inventari(string id_ciutat)
{
    bool exists = true;
    if (not ciutat_exis(id_ciutat)) exists = false;

    int n_produ, id_produ, sob, nec;
    cin >> n_produ;
    Inventari aux;
    if (exists) id2Inventari[id_ciutat] = aux; //creem nou inventari
    for (int i = 0; i < n_produ; ++i) {
        cin >> id_produ >> sob >> nec;
        Producte produ = id2Producte[id_produ];
        aux.afegir_produ_inventari(produ, sob, nec);
    }

    if (exists) id2Inventari[id_ciutat] = aux;
    else cout <<"error: no existe la ciudad" << endl;
}

void Riu::llegir_conca()
{
    id2Inventari.clear();
    BT buit;
    arbre_id_ciutats = buit;
    string node;
    cin >> node;
    Inventari inventari;
    if (node != "#") {
        BT left, right;
        id2Inventari[node] = inventari;
        left = modificar_conca();
        right = modificar_conca();
        arbre_id_ciutats = BT (node, left, right);
    }

    else {} //node buit
    vaixell.ruta_buida();
}

void Riu::modif_vaixell(int id1, int id2, int comp, int vend)
{
    if (not produ_exis(id1)) cout << "error: no existe el producto" << endl;
    else if (not produ_exis(id2)) cout << "error: no existe el producto" << endl;
    else if (id1 == id2) cout << "error: no se puede comprar y vender el mismo producto" << endl;
    else {
        vaixell.canviar_atributs(id1, id2, comp, vend);
    }

}

void Riu::posar_prod_ciu(string id_ciutat, int id_produ)
{
    int te, nece;
    cin >> te >> nece;
    if (not produ_exis(id_produ)) cout << "error: no existe el producto" << endl;
    else if (not ciutat_exis(id_ciutat)) cout << "error: no existe la ciudad" << endl;
    else if (id2Inventari[id_ciutat].existeix_produ(id_produ)) cout << "error: la ciudad ya tiene el producto" <<endl;
    else {
        id2Inventari[id_ciutat].afegir_produ_inventari(id2Producte[id_produ], te, nece);
        cout << id2Inventari[id_ciutat].consul_pes_total() << " " << id2Inventari[id_ciutat].consul_volum_total() << endl;
    }
}

void Riu::modificar_prod_ciu(string id_ciutat, int id_produ)
{
    int te, nece;
    cin >> te >> nece;
    if (not produ_exis(id_produ)) cout << "error: no existe el producto" << endl;
    else if (not ciutat_exis(id_ciutat)) cout << "error: no existe la ciudad" << endl;
    else if (not id2Inventari[id_ciutat].existeix_produ(id_produ)) cout << "error: la ciudad no tiene el producto" <<endl;
    else {
        id2Inventari[id_ciutat].modif_produ(id2Producte[id_produ], te, nece);
        cout << id2Inventari[id_ciutat].consul_pes_total() << " " << id2Inventari[id_ciutat].consul_volum_total() << endl;
    }
}

void Riu::treure_prod_ciu(string id_ciutat, int id_produ)
{
    if (not produ_exis(id_produ)) cout << "error: no existe el producto" << endl;
    else if (not ciutat_exis(id_ciutat)) cout << "error: no existe la ciudad" << endl;
    else if (not id2Inventari[id_ciutat].existeix_produ(id_produ)) cout << "error: la ciudad no tiene el producto" <<endl;
    else {
        id2Inventari[id_ciutat].eliminar_produ_inventari(id_produ);
        cout << id2Inventari[id_ciutat].consul_pes_total() << " " << id2Inventari[id_ciutat].consul_volum_total() << endl;
    }
}

void Riu::intercanvi_prod(string id_ciutat1, string id_ciutat2)
{
    if (not ciutat_exis(id_ciutat1)) cout << "error: no existe la ciudad" << endl;
    else if (not ciutat_exis(id_ciutat2)) cout << "error: no existe la ciudad" << endl;
    else if (id_ciutat1 == id_ciutat2) cout << "error: ciudad repetida" << endl;
    else {
        id2Inventari[id_ciutat1].comerciar(id2Inventari[id_ciutat2]);
    }
}


//Escriure:
void Riu::veure_vaixell() const
{
    vaixell.escriure_vaixell();
}

void Riu::veure_producte(int id_produ) const
{
    if (not produ_exis(id_produ)) cout << "error: no existe el producto" << endl;
    else {
        cout << id_produ << " " << id2Producte.at(id_produ).consul_pes() << " " << id2Producte.at(id_produ).consul_volum() << endl;
    }
}

void Riu::veure_ciutat(string id_ciutat) const
{
    if (not ciutat_exis(id_ciutat)) cout << "error: no existe la ciudad" << endl;
    else {
        id2Inventari.at(id_ciutat).escriure_inventari();
    }
}

void Riu::veure_prod_ciu(string id_ciutat, int id_produ) const
{
    if (not produ_exis(id_produ)) cout << "error: no existe el producto" << endl;
    else if (not ciutat_exis(id_ciutat)) cout << "error: no existe la ciudad" << endl;
    else if (not id2Inventari.at(id_ciutat).existeix_produ(id_produ)) cout << "error: la ciudad no tiene el producto" <<endl;
    else {
        cout << id2Inventari.at(id_ciutat).consul_te(id_produ) << " " << id2Inventari.at(id_ciutat).consul_nece(id_produ) << endl;
    }
}



