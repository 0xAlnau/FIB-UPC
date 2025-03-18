/** @file Producte.hh
 *  @brief Classe que representa l'objecte Producte.
 */

#ifndef _PRODUCTE_
#define _PRODUCTE_

#ifndef NO_DIAGRAM
#include<iostream>
#endif
using namespace std;
/*
   Classe Producte
*/

/** @class Producte
    @brief Representa un producte amb les seves característiques i
    les seves operacions pròpies, que són:

    <b>-Constructores:</b> té dues constructores. Una és la que hi ha per defecte, on
     el producte inicialitzat no té cap atribut inicialitzat. La segona inicialitza
     el producte amb el seu id_producte, el seu pes i el seu volum.

    <b>-Consultores:</b> té tres consultores. La primera serveix per consultar el pes
     del prodcute. La segona serveix per consultar el volum que ocupa el producte.
     L'última serveix per consultar el id_producte.

    <b>-Modificadores:</b> no té modificadores.

    <b>-Escriure:</b> no té funcions per escriure.
*/

class Producte {
private:
    /** @brief Identificador del p.i*/
    int id_produ;

    /** @brief Indica quant pesa el p.i.*/
    int pes;

    /** @brief Indica el volum del p.i.*/
    int volum;

public:
    //Constructora:
    /** @brief Creadora per defecte.
      @pre Cert.
      @post El resultat és un producte sense atributs.*/
    Producte();

    /** @brief Segona creadora per defecte.
      @pre Cert.
      @post El resultat és un producte amb massa, un espai que ocupa,
      i el seu identificador.*/
    Producte(int id_produ, int pes, int volum);


    //Consultores:
    /** @brief Consultora de la massa que té el p.i.
     * @pre Cert
     * @post Es retorna un enter positiu indicant la massa del p.i.*/
    int consul_pes() const;

    /** @brief Consultora del espai que ocupa el p.i.
     * @pre Cert
     * @post Es retorna un enter positiu indicant l'espai que ocupa el p.i.*/
    int consul_volum() const;

    /** @brief Consultora del identificador del p.i.
     * @pre Cert
     * @post Es retorna l'identificador del p.i.*/
    int consul_id_produ() const;
};
#endif
