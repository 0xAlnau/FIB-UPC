/** @mainpage
    El programa principal, encarregat d'executar totes les instruccions bàsiques,
    està ubicat en el mòdul de program.cc.

    A partir de l'enunciat donat, són necessaris més mòduls per a solucionar tot
    el problema de la millor forma possible, aquests mòduls són:

    <b>·Riu:</b> mòdul principal i controlador de tota la resta de mòduls. Representa un riu real,
                 amb els seus afluents i ciutats localitzades on dos d'aquests afluents s'uneixen, i
                 amb una sola desembocadura al mar. S'encarrega d'emmagatzemar l'estructura del riu
                 amb les seves ciutats, d'indicar tots els productes que hi ha a la conca, de gestionar
                 les ciutats i les seves activitats, i de controlar el comportament del vaixell.

    <b>·Inventari:</b> aquest mòdul representa el magatzem d'una ciutat, que apunta quin és el pes total
                       i el volum total que tenen tots els productes de la ciutat. Gestiona la quantitat
                       de productes que té i que necessita una ciutat en cada moment.

    <b>·Producte:</b> és el mòdul més simple de tots, pot representar qualsevol objecte real. Té un pes,
                      un volum, i un identificador, els quals es poden consultar.

    <b>·Vaixell:</b> l'últim mòdul del projecte representa un petit vaixell que pot comerciar amb les ciutats
                     del riu. S'encarrega de guardar el producte que vol comprar i la quantitat que vol, del
                     producte que vol vendre i la quantitat, i finalment d'apuntar quina ha sigut l'última ciutat
                     visitada al darrer viatge.

*/

/** @file program.cc
    @brief Programa principal:

    Donem per fet que les dades llegides corresponen sí o sí amb alguna
    de les 17 instruccions que contempla aquest programa principal, ja que
    no hi ha cap comprovació respecte a aquest aspecte. Hi ha un cas especial,
    que consisteix en la possibilitat de fer comentaris, i s'indica posant "//"
    i després el comentari dessitjat. S'utilitzaran strings per tal d'indicar quina
    operació serà la següent. El programa principal acaba quan l'operació indiqui "fin".
*/
#include"Riu.hh"

int main(){
    //Declaració del riu, productes i vaixell
    Riu riu;

    string operacio;
    cin >> operacio;
    while (operacio != "fin") {
        if (operacio == "leer_rio" or operacio == "lr") {
            if (operacio == "leer_rio") cout << "#leer_rio" << endl;
            else cout << "#lr" << endl;
            riu.llegir_conca();
        }

        else if (operacio == "leer_inventario" or operacio == "li") {
            string id_ciutat;
            cin >> id_ciutat;
            if (operacio == "leer_inventario") cout << "#leer_inventario " << id_ciutat << endl;
            else cout << "#li " << id_ciutat << endl;
            riu.llegir_inventari(id_ciutat);
        }

        else if (operacio == "leer_inventarios" or operacio == "ls") {
            if (operacio == "leer_inventarios") cout << "#leer_inventarios" << endl;
            else cout << "#ls" << endl;
            string id_ciutat;
            cin >> id_ciutat;
            while (id_ciutat != "#") {
                riu.llegir_inventari(id_ciutat);
                cin >> id_ciutat;
            }
        }

        else if (operacio == "modificar_barco" or operacio == "mb") {
            int id_produ1, id_produ2, comp, vend;
            if (operacio == "modificar_barco") cout << "#modificar_barco" << endl;
            else cout << "#mb" << endl;
            cin >> id_produ1 >> comp;
            cin >> id_produ2 >> vend;
            riu.modif_vaixell(id_produ1, id_produ2, comp, vend);
        }

        else if (operacio == "escribir_barco" or operacio == "eb") {
            if (operacio == "escribir_barco") cout << "#escribir_barco" << endl;
            else cout << "#eb" << endl;
            riu.veure_vaixell();
        }

        else if (operacio == "consultar_num" or operacio == "cn") {
            if (operacio == "consultar_num") cout << "#consultar_num" << endl;
            else cout << "#cn" << endl;
            cout << riu.num_productes() << endl;
        }

        else if (operacio == "agregar_productos" or operacio == "ap") {
            int n_produs;
            cin >> n_produs;
            if (operacio == "agregar_productos") cout << "#agregar_productos " << n_produs << endl;
            else cout << "#ap " << n_produs << endl;
            for (int i = 0; i < n_produs; ++i) {
                riu.declarar_producte();
            }
        }

        else if (operacio == "escribir_producto" or operacio == "ep") {
            int id_produ;
            cin >> id_produ;
            if (operacio == "escribir_producto") cout << "#escribir_producto " << id_produ << endl;
            else cout << "#ep " << id_produ << endl;
            riu.veure_producte(id_produ);
        }

        else if (operacio == "escribir_ciudad" or operacio == "ec") {
            string id_ciutat;
            cin >> id_ciutat;
            if (operacio == "escribir_ciudad") cout << "#escribir_ciudad " << id_ciutat << endl;
            else cout << "#ec " << id_ciutat << endl;
            riu.veure_ciutat(id_ciutat);
        }

        else if (operacio == "poner_prod" or operacio == "pp") {
            string id_ciutat;
            int id_produ;
            cin >> id_ciutat >> id_produ;
            if (operacio == "poner_prod") cout << "#poner_prod " << id_ciutat << " " << id_produ << endl;
            else cout << "#pp " << id_ciutat << " " << id_produ << endl;
            riu.posar_prod_ciu(id_ciutat, id_produ);
        }

        else if (operacio == "modificar_prod" or operacio == "mp") {
            string id_ciutat;
            int id_produ;
            cin >> id_ciutat >> id_produ;
            if (operacio == "modificar_prod") cout << "#modificar_prod " << id_ciutat << " " << id_produ << endl;
            else cout << "#mp " << id_ciutat << " " << id_produ << endl;
            riu.modificar_prod_ciu(id_ciutat, id_produ);
        }

        else if (operacio == "quitar_prod" or operacio == "qp") {
            string id_ciutat;
            int id_produ;
            cin >> id_ciutat >> id_produ;
            if (operacio == "quitar_prod") cout << "#quitar_prod " << id_ciutat << " " << id_produ << endl;
            else cout << "#qp " << id_ciutat << " " << id_produ << endl;
            riu.treure_prod_ciu(id_ciutat, id_produ);
        }

        else if (operacio == "consultar_prod" or operacio == "cp") {
            string id_ciutat;
            int id_produ;
            cin >> id_ciutat >> id_produ;
            if (operacio == "consultar_prod") cout << "#consultar_prod " << id_ciutat << " " << id_produ << endl;
            else cout << "#cp " << id_ciutat << " " << id_produ << endl;
            riu.veure_prod_ciu(id_ciutat, id_produ);
        }

        else if (operacio == "comerciar" or operacio == "co") {
            string id_ciutat1, id_ciutat2;
            cin >> id_ciutat1 >> id_ciutat2;
            if (operacio == "comerciar") cout << "#comerciar " << id_ciutat1 << " " << id_ciutat2 << endl;
            else cout << "#co " << id_ciutat1 << " " << id_ciutat2 << endl;
            riu.intercanvi_prod(id_ciutat1, id_ciutat2);
        }

        else if (operacio == "redistribuir" or operacio == "re") {
            if (operacio == "redistribuir") cout << "#redistribuir" << endl;
            else cout << "#re" << endl;
            riu.redistribuir();
        }

        else if (operacio == "hacer_viaje" or operacio == "hv") {
            if (operacio == "hacer_viaje") cout << "#hacer_viaje" << endl;
            else cout << "#hv" << endl;
            riu.viatge();
        }

        else if (operacio == "//") getline(cin, operacio);

        cin >> operacio;
    }
}
