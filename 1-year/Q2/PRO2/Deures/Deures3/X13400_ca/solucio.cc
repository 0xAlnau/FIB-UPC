//arnau.cullell@estudiantat.upc.edu L23
//pol.riveiro@estudiantat.upc.edu L41

#include<iostream>
#include"Estudiant.hh"
#include"Cjt_estudiants.hh"
using namespace std;

/* Pre: el paràmetre implícit no està ple */
/* Post: b = indica si el p.i. original conté un estudiant amb el dni d'est;
   si b = fals, s'ha afegit l'estudiant est al paràmetre implícit */
void Cjt_estudiants::afegir_estudiant(const Estudiant &est, bool& b){
	int pos = cerca_dicot(vest, 0, nest-1, est.consultar_DNI());
    b = pos < nest and vest[pos].consultar_DNI() == est.consultar_DNI();
    if(b) return;
    for(int i = nest-1; i >= pos; i--) vest[i+1] = vest[i];
    vest[pos] = est;
    nest++;
    if(est.te_nota()) incrementar_interval(est.consultar_nota());
}


/* Pre: cert */
/* Post: b indica si el paràmetre implícit original tenia un estudiant
   amb el dni dni; si b, aquest estudiant ha quedat eliminat
   del paràmetre implícit */
void Cjt_estudiants::esborrar_estudiant(int dni, bool& b){
	int left = 0, right = nest-1;
	int index = cerca_dicot(vest, left, right, dni);
	Estudiant aux; //estudiant sense nota ni DNI

	if (index < nest and vest[index].consultar_DNI() == dni) {
    	if (vest[index].te_nota()) decrementar_interval(vest[index].consultar_nota());

    	int max_nest = nest-1;
    	for (int i = index; i < max_nest; ++i) vest[i] = vest[i+1];
    	vest[nest-1] = aux;
    	--nest;
    	b = true;
	}

	else b = false;
}





/* Pre: x és una nota vàlida */
/* Post: al paràmetre implícit, s'ha incrementat en una unitat el valor de
   la posició d'"intervals" corresponent a x */
void Cjt_estudiants::incrementar_interval(double x){
	if (x >= 0 and x < 1) ++intervals[0];
	else if (x >= 1 and x < 2) ++intervals[1];
	else if (x >= 2 and x < 3) ++intervals[2];
	else if (x >= 3 and x < 4) ++intervals[3];
	else if (x >= 4 and x < 5) ++intervals[4];
	else if (x >= 5 and x < 6) ++intervals[5];
	else if (x >= 6 and x < 7) ++intervals[6];
	else if (x >= 7 and x < 8) ++intervals[7];
	else if (x >= 8 and x < 9) ++intervals[8];
	else ++intervals[9];
}


/* Pre: x és una nota vàlida */
/* Post: al paràmetre implícit, s'ha decrementat en una unitat el valor de
   la posició d'"intervals" corresponent a x */
void Cjt_estudiants::decrementar_interval(double x){
	if (x >= 0 and x < 1) --intervals[0];
	else if (x >= 1 and x < 2) --intervals[1];
	else if (x >= 2 and x < 3) --intervals[2];
	else if (x >= 3 and x < 4) --intervals[3];
	else if (x >= 4 and x < 5) --intervals[4];
	else if (x >= 5 and x < 6) --intervals[5];
	else if (x >= 6 and x < 7) --intervals[6];
	else if (x >= 7 and x < 8) --intervals[7];
	else if (x >= 8 and x < 9) --intervals[8];
	else --intervals[9]; //x >= 9 and x <= 10
}

