/** @file Inventari.hh
 *  @brief Classe que representa l'objecte Inventari.
 */

#ifndef _INVENTARI_
#define _INVENTARI_

#include"Producte.hh"

#ifndef NO_DIAGRAM
#include<string>
#include<map>
#endif
using namespace std;
/*
   Classe Inventari
*/

/** @class Inventari
    @brief Representa un inventari amb les seves característiques i
    les seves operacions pròpies, que són:

    <b>-Constructora:</b> només té la constructora per defecte, on s'inicialitza l'inventari
     amb atributs buits.

    <b>-Consultores:</b> té set consultores. On podem consultar la mida del inventari, si existeix
     un producte a l'inventari, el pes total i el volum total de l'inventari, i també podem
     demanar la quantitat que té, necessita i que sobra d'un producte.

    <b>-Modificadores:</b> hi ha 6 modificadores. Es pot comerciar amb dos inventaris de dues
     ciutats diferents, a més a més es pot afegir, eliminar o modificar un producte existent
     a l'inventari. Finalment es pot modificar la quantitat que es té o que necessita d'un
     producte.

    <b>-Escriure:</b> la funció per escriure mostrarà per pantalla la id de cada producte i la seva
     quantitat que té i que necessita. Al acabar de mostrar cada producte, imprimirà el pes
     i volum total de l'inventari.
*/

class Inventari{
private:
    /** @brief Atribut que serveix per emmagatzemar els productes que té el p.i.*/
    map<int,Producte> producs_inventari;

    /** @brief Atribut que serveix per accedir amb la id d'un producte
     *  a quantes unitats d'aquell producte es necessiten.*/
    map<int,int> produc_nece;

    /** @brief Atribut que serveix per accedir amb la id d'un producte
     *  a quantes unitats d'aquell producte es tenen.*/
    map<int,int> produc_te;

    /** @brief Indica la suma del pes de tots els productes del p.i.*/
    int pes_total;

    /** @brief Indica la suma del volum de tots els productes del p.i.*/
    int volum_total;

    /** @brief Modificador de quantes unitats d'un producte li fan falta al p.i.
     * @pre El producte indicat ha d'existir.
     * @post El p.i li faran falta mes o menys unitats d'un producte.*/
    void modif_nece(int id_produ, int valor);

public:
    //Constructora:
    /** @brief Creadora per defecte.
      @pre Cert
      @post El resultat és una inventari sense cap atribut.*/
    Inventari();


    //Consultores:
    /** @brief Consultora del nombre de productes al p.i.
     * @pre Cert
     * @post Es retorna un enter positiu indicant quants productes hi ha al p.i.*/
    int consul_mida_invent() const;

    /** @brief Consultora per veure si el p.i té un producte en específic.
     * @pre Cert
     * @post Es retorna cert si existeix el producte, fals d'altra banda.*/
    bool existeix_produ(int id_produ) const;

    /** @brief Consultora de la massa total dels productes que té el p.i.
     * @pre Cert
     * @post Es retorna un enter positiu indicant la massa total dels productes
     * del p.i.*/
    int consul_pes_total() const;

    /** @brief Consultora de l'espai total que ocupen els productes en el p.i.
     * @pre Cert
     * @post Es retorna un enter positiu indicant l'espai total que ocupen els
     * productes al p.i.*/
    int consul_volum_total() const;

    /** @brief Consultora de la quantitat que li falten al p.i d'un producte en específic.
     * @pre El producte indicat ha d'existir.
     * @post Es retorna un natural indicant la quantitat de productes que li falten
     * al p.i d'un producte en específic.*/
    int consul_nece(int id_produ) const;

    /** @brief Consultora de la quantitat que té el p.i d'un producte en específic.
     * @pre El producte indicat ha d'existir.
     * @post Es retorna un natural indicant la quantitat de productes que té el
     * p.i d'un producte en específic.*/
    int consul_te(int id_produ) const;

    /** @brief Consultora de la quantitat que li sobre al p.i d'un producte en específic.
     * @pre El producte indicat ha d'existir.
     * @post Es retorna un enter, que si és positiu indica la quantita que li sobra d'un
     * d'un producte. Si és negatiu, indica la quantitat que hem de donar a la ciutat per a
     * que arribi a tindre la mateixa quantitat que té i que necessita.*/
    int consul_sobr(int id_produ) const;


    //Modificadors:
    /** @brief Aquesta acció s'encarrega de fer comerciar dues ciutats amb els seus respectius
     * inventaris. La primera ciutat donarà tots els productes que facin falta a l'altre fins
     * arribar com a molt als que necessita la segona, i viceversa.
     * @pre Els dos inventaris necessitan de tots els seus productes.
     * @post Es modificaran els productes que té i que necessita cada inventari.*/
    void comerciar(Inventari& i2);

    /** @brief Aquesta acció s'encarrega d'eliminar un producte del p.i.
     * @pre El producte ha d'existir, i el producte ha d'estar al p.i.
     * @post El p.i ja no tindrà aquell producte, i per tant, si la ciutat
     * tenia d'aquell producte, la massa total i l'espai total disminueixen.*/
    void eliminar_produ_inventari(int id_produ);

    /** @brief Aquesta acció s'encarrega d'afegir un producte al p.i.
     * @pre El producte ha d'existir, i el producte no ha d'estar al p.i.
     * @post El p.i ara tindrà aquell producte, i per tant, si la ciutat ara té
     * d'aquell producte, augmenta la massa total i l'espai total del p.i.*/
    void afegir_produ_inventari(const Producte& produ, int te, int nece);

    /** @brief Aquesta acció s'encarrega de modificar quantes unitats li sobren i
     *  necessita el p.i d'un producte en específic.
     * @pre El producte ha d'existir, i el producte hi és al p.i.
     * @post Les unitats que té i que necessitava un producte al p.i ha canviat.*/
    void modif_produ(const Producte& produ, int te, int nece);

    /** @brief Modificador de quantes unitats d'un producte té el p.i.
     * @pre El producte indicat ha d'existir.
     * @post El p.i tindrà més o menys d'aquell producte, per tant canviarà la massa
     * total i el espai total que ocupa el p.i.*/
    void modif_te(int id_produ, int valor);


    //Escriure:
    /** @brief Escriurà per pantalla el p.i.
     * @pre Cert.
     * @post Es veurà per pantalla l'identificador de cada producte, les unitats que té i
     * que necessita de cada producte el p.i. Serà de la forma: "id_produ sob nec", serà
     * així per a cada producte del p.i.*/
    void escriure_inventari() const;
};
#endif
