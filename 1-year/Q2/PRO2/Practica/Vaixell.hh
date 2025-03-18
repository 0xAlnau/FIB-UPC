/** @file Vaixell.hh
 *  @brief Classe que representa l'objecte Vaixell.
 */

#ifndef _VAIXELL_
#define _VAIXELL_

#ifndef NO_DIAGRAM
#include<iostream>
#include<list>
#endif
using namespace std;
/*
   Classe Vaixell
*/

/** @class Vaixell
    @brief Representa un vaixell amb les seves característiques i
    les seves operacions pròpies, que són:

    <b>-Constructora:</b> només té la constructora per defecte, on el vaixell s'inicialitza
     sense cap valor.

    <b>-Consultores:</b> Té dues consultores. La primera retorna un pair de enters, que
     el primer indica l'identificador del producte a comprar, i el segon la quantitat.
     La segona, el pirmer enter indica l'identificador del producte a comprar, i el segon
     enter la quantitat.

    <b>-Modificadores:</b> Té tres modificadors. El primer serveix per modificar el producte que
     vol comprar i la quantitat, i el mateix per vendre. El segon afegirà a la llista de
     ciutats visitades una nova ciutat, l'última de la darrere ruta feta. L'última modificadora
     buidarà la llista de ciutats visitades pel vaixell.

    <b>-Escriure:</b> la funció per escriure mostrarà per pantalla la id del producte que vol comprar i
     la quantitat, també la id del producte que vol vendre i la quantitat, i finalment les últimes
     ciutats visitades a cada viatge de una conca.
*/

class Vaixell{
private:
    /** @brief Atribut que serveix per accedir i saber quantes unitats d'un
     *  producte vol comprar el p.i. El primer enter indica la id del producte,
     *  el segon indica la quantitat a comprar.*/
    pair<int,int> comprar_produ;

    /** @brief Atribut que serveix per accedir i saber quantes unitats d'un
     *  producte vol vendre el p.i. El primer enter indica la id del producte,
     *  el segon indica la quantitat a vendre.*/
    pair<int,int> vendre_produ;

    /** @brief Atribut que serveix per saber la última ciutat visitada a cada viatge
     *  d'una conca, en ordre cronològic.*/
    list<string> llocs_visitats;

public:
    //Constructora:
    /** @brief Creadora per defecte.
      @pre Cert
      @post El resultat és un vaixell sense cap atribut.*/
    Vaixell();


    //Consultores:
    /** @brief Aquesta consultora permetrà al usuari saber la id del producte i quanta
     *  quantitat vol comprar d'aquell producte.
     * @pre Cert
     * @post L'usuari rebrà un pair d'enters, on el primer serà la id del producte, i el
     * segon serà la quantitat a comprar.*/
    pair<int,int> consul_compr() const;

    /** @brief Aquesta consultora permetrà al usuari saber la id del producte i quanta
     *  quantitat vol vendre d'aquell producte.
     * @pre Cert
     * @post L'usuari rebrà un pair d'enters, on el primer serà la id del producte, i el
     * segon serà la quantitat a vendre.*/
    pair<int,int> consul_vend() const;


    //Modificadores:
    /** @brief Acció que servirà per canviar els atributs del p.i quan es dessitgi.
     * @pre Els proudctes existeixen.
     * @post Es modificarà els atributs del p.i.*/
    void canviar_atributs(int id1, int id2, int comp, int vend);

    /** @brief Acció que serveix per afegir una nova ciutat a la llista de ciutats visitades
     *  pel p.i en una mateixa conca.
     * @pre Cert
     * @post Es modificarà els llocs per on ha passat el p.i en una conca.*/
    void afegir_a_ruta(string id_ciutat);

    /** @brief Acció la qual farà que el p.i no tingui registrada cap ciutat del riu per on ha passat.
     * @pre Cert
     * @post Es modificarà els llocs per on ha passat el p.i.*/
    void ruta_buida();


    //Escriure:
    /** @brief S'escriurà pel canal estàndard de sortida les dades del p.i.
     * @pre El p.i ha de tenir dades inicialitzades.
     * @post L'usuari veurà pel canal estàndard de sortida les dades del vaixell.*/
    void escriure_vaixell() const;
};
#endif
