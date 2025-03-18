/** @file Riu.hh
 *  @brief Classe que representa l'objecte Riu.
*/

#ifndef _RIU_
#define _RIU_

#include"Vaixell.hh"
#include"Inventari.hh"
#ifndef NO_DIAGRAM
#include<string>
#include<list>
#include"BinTree.hh"
#endif

/*
   Classe Riu
*/

/** @class Riu
    @brief Representa un riu amb les seves característiques i
    les seves operacions pròpies, que són:

    <b>-Constructora:</b> només té una constructora, la qual obliga al usuari a introduir
     quants productes vol al riu inicialment, i indicar el pes i el volum que ocupa
     cada un. També fa que declari la conca del riu. Finalment es llegirà les dades
     del vaixell.

    <b>-Consultores:</b> té tres consultores. Serveixen per saber el nombre de productes al
     riu, si un producte existeix al riu, i si una ciutat forma part del riu.

    <b>-Modificadores:</b> hi ha catorze modificadores. Que ens permeten modificar la conca actual, que es
     crida des de llegir conca; fer un comerç global de tot el riu, que es crida amb la funció redistribuir;
     també podem calcular la ruta d'un viatge, i realitzar el viatge, que es criden amb la funció viatge;
     podem declarar nous productes al riu; es pot llegir l'inventari d'una ciutat; modificar el vaixell; posar
     productes al riu; treure productes del riu; modificar productes del riu i finalment consultar el nombre
     de productes que hi han al riu.

    <b>-Escriure:</b> existeixen quatre funcions per escriure. La primera serveix per veure per pantalla el vaixell
     del riu; la segona permet veure el pes i el volum d'un producte del riu; la tercera imprimeix per pantalla
     l'inventari d'una ciutat; i l'última permet veure la quantitat que té i que necessita la ciutat d'un producte.
*/

typedef BinTree<string> BT; //per fer-ho més atractiu

class Riu {
private:
    /** @brief Atribut que indica com estan estan distribuides les ciutats en el p.i.*/
    BT arbre_id_ciutats;

    /** @brief Identificador inicial dels productes.*/
    int id_producte_actual;

    /** @brief Atribut que serveix per accedir amb la id d'una ciutat al seu inventari.*/
    map<string,Inventari> id2Inventari;

    /** @brief Atribut que serveix per accedir i saber quins productes conté el p.i.*/
    map<int,Producte> id2Producte;

    /** @brief Atribut que ens permet navegar el p.i, i que interactua amb les ciutats.*/
    Vaixell vaixell;

    /** @brief LLegir arbre de ciutats del canal estàndard d'entrada.
     * @pre L'arbre ha d'estar introduit en preordre pel canal estàndard d'entrada.
     * @post Anirà retornant subarbres per montar l'arbre principal.*/
    BT modificar_conca();

    /** @brief Aquesta acció farà comerciar, des de la desembocadura, cada ciutat amb,
     * mirant riu amunt, primer amb la ciutat de la dreta, i després amb la ciutat de
     * l'esquerra. L'acció s'atura al arribar als naixements del riu.
     * @pre Si un node té almenys un fill, es garanteix que llavors tindrà fill dret i esquerra.
     * @post Es modificaran els productes que sobren i que necessita cada ciutat del riu.*/
    void comerc_global(const BT& t);

    /** @brief Aquesta acció s'encarrega de trobar la ruta més profitosa, voldrà trobar la ruta per la qual el
    * transport aquàtic vengui i compri més productes. I en cas de que dues rutes siguin igual de profitoses,
    * agafarà la més curta, i si encara hi ha empat, agafarà la que estigui més a la dreta mirant riu amunt.
    * @pre El vaixell té productes per comprar i vendre, i la conca no és buida.
    * @post Es retornarà un llista de enters entre 0 i 1, on 1 vol dir anar cap a la dreta mirant
    * riu amunt, i 0 vol dir anar cap a l'esquerra mirant riu amunt.*/
    list<int> calcular_ruta(const BT& t, int& comprat, int& venut, const pair<int,int>& vol_compr, const pair<int,int>& vol_vendre);

    /** @brief Aquesta acció agafarà la llista L, que és la ruta més profitosa possible, i farà que el transport
     *  aquàtic viatgi pel riu, comprant i venent els productes que té.
     * @pre El transport aquàtic comprarà i vendrà productes diferents.
     * @post Els atributs del transport hauran quedat modificats, l'inventari de les ciutats
     * visitades també, i ara la llista l serà buida, ja que ja s'ha fet tot el recorregut.*/
    void realitzar_viatge(const BT& t, list<int> ruta, pair<int,int>& vol_compr, pair<int,int>& vol_vendre);

public:
    //Constructora;
    /** @brief Creadora per defecte.
      @pre Cert
      @post El resultat és un riu amb una conca definida, productes declarats, i
      el transport aquàtic amb els seus atributs inicialitzats.*/
    Riu();


    //Consultores:
    /** @brief Consultora del nombre de productes al p.i
     * @pre Cert
     * @post Es retorna un natural indicant quants productes hi ha en el p.i.*/
    int num_productes() const;

    /** @brief Consultora per saber si una ciutat existeix.
     * @pre Cert
     * @post Es retorna true si la ciutat existeix, es retorna false en el cas contrari.*/
    bool ciutat_exis(string id_ciutat) const;

    /** @brief Consultora per saber si un producte existeix.
     * @pre Cert
     * @post Es retorna true si el producte existeix, es retorna false en el cas contrari.*/
    bool produ_exis(int id_produ) const;


    //Modificadors:
    /** @brief Aquesta acció farà que totes les ciutats del riu facin comerç amb
     *  els seus veïns, primer amb la ciutat que està mirant riu amunt a la dreta, i després
     *  amb la que està a l'esquerra mirant riu amunt.
     * @pre Ha d'existir una conca amb ciutats, i que totes elles tinguin productes
     * que necessitin una certa quantitat.
     * @post Es modificaran els productes que sobren i que necessita cada ciutat del riu.*/
    void redistribuir();

    /** @brief Aquesta acció s'encarrega de fer navegar el transport aquàtic. Segons una ruta
     *  calculada, el transport aquàtic anirà recorrent el p.i, comprant i venent els productes
     *  que necessiti.
     * @pre El transport aquàtic tindrà productes per comprar i vendre.
     * @post Es modificaran els productes que sobren i que necessita cada ciutat
     * de la ruta, i també el transport aquàtic va venent i comprant productes, modificant
     * els seus atributs pel camí.*/
    void viatge();

    /** @brief Llegir del canal estàndard d'entrada nous productes a afegir.
     * @pre Cert
     * @post Es crearan tants productes no buits com indiqui l'usuari.*/
    void declarar_producte();

    /** @brief Donats l'identificador d'una ciutat i el nombre de productes a afegir,
     *  la ciutat tendrà al inventari el nombre de productes dessitjat.
     * @pre Cert
     * @post La ciutat tindrà un inventari amb més productes.*/
    void llegir_inventari(string id_ciutat);

    /** @brief LLegir un arbre de ciutats pel canal estàndard d'entrada.
     * @pre L'arbre ha d'estar introduit en preordre pel canal estàndard d'entrada.
     * @post Es crearà al p.i un arbre amb identificadors de ciutats.*/
    void llegir_conca();

    /** @brief Els atributs del transport aquàtica del p.i seran modificats.
     * @pre Cert
     * @post El transport aquàtic del p.i haurà canviat.*/
    void modif_vaixell(int id1, int id2, int comp, int vend);

    /** @brief S'afegirà un nou producte a la ciutat dessitjada.
     * @pre Cert
     * @post La ciutat indicada tindrà un nou producte al seu inventari.*/
    void posar_prod_ciu(string id_ciutat, int id_produ);

    /** @brief Es modificarà les unitats que té i que necessita una ciutat d'un producte.
     * @pre Cert
     * @post La ciutat indicada tindrà les unitats que té i que necessita d'un producte canviades.*/
    void modificar_prod_ciu(string id_ciutat, int id_produ);

    /** @brief Es treurà un producte de l'inventari d'una ciutat.
     * @pre Cert
     * @post La ciutat indicada ja no tindrà aquell producte.*/
    void treure_prod_ciu(string id_ciutat, int id_produ);

    /** @brief Dues ciutats intercanviaran entre sí productes que els dos tenen, un li donarà a l'altre
     *  tota la quantitat possible d'un producte, però sense quedar-se amb menys del que necessita, i viceversa.
     * @pre Cert
     * @post Les ciutats hauran intercanviat i tindran un inventari modificat.*/
    void intercanvi_prod(string id_ciutat1, string id_ciutat2);


    //Escriure:
    /** @brief Acció que escriurà els atributs del transport aquàtic per pantalla.
     * @pre Cert
     * @post L'usuari veurà la quantitat que es vol comprar d'un producte, la quantitat que es vol vendre
     * d'un producte, i els viatges realitzats per la conca en ordre cronològic.*/
    void veure_vaixell() const;

    /** @brief Acció que escriurà els atributs d'un producte per pantalla.
     * @pre Cert
     * @post L'usuari veurà el pes i el volum del producte.*/
    void veure_producte(int id_produ) const;

    /** @brief Acció que escriurà per pantalla l'inventari d'una ciutat.
     * @pre Cert
     * @post L'usuari veurà els atributs de l'inventari d'aquella ciutat.*/
    void veure_ciutat(string id_ciutat) const;

    /** @brief Acció que imprimirà la quantitat que té i que li sobra a una ciutat
     *  d'un producte en específic.
     * @pre Cert
     * @post L'usuari veurà per pantalla la quantitat que té i que necessita una ciutat d'un producte.*/
    void veure_prod_ciu(string id_ciutat, int id_produ) const;
};
#endif
