#include "CacheSim.h"
#include <stdio.h>

/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */
	struct cache{
		unsigned int valid;
		unsigned int tag;
	};

	struct cache linia[128];

	unsigned int hits;
	unsigned int miss;


/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al comensar cada un dels tests.
 * */
void init_cache ()
{
 	/* Escriu aqui el teu codi */
   for (int i = 0; i < 128; ++i) linia[i].valid = 0;

   hits = 0;
   miss = 0;
}

/* La rutina reference es cridada per cada referencia a simular */
void reference (unsigned int address, unsigned int LE) // 0 = Lectura  1 = Escriptura
{
	unsigned int byte;
	unsigned int bloque_m;
	unsigned int linea_mc;
	unsigned int tag;
	unsigned int miss;
	unsigned int lec_mp;
	unsigned int mida_lec_mp;
	unsigned int esc_mp;
	unsigned int mida_esc_mp;
	unsigned int replacement;
	unsigned int tag_out;

	/* Escriu aqui el teu codi */
	byte = address & 0x0000001F; //recullo els ultims 5 bits
	bloque_m = address >> 5; //fem shift dreta 5 vegades
	linea_mc = bloque_m & 0x0000007F; //cogemos los 7 bits de linea, que son los ultimos 7 del bloque
	tag = address >> 12; //afagem els 20 bits de TAG

	miss = linia[linea_mc].valid == 0 || linia[linea_mc].tag != tag;
	replacement = miss && linia[linea_mc].valid == 1 && (LE == 0);

	if (LE == 0) { //Lectura
		mida_esc_mp = 0;
		esc_mp = 0;
		if (miss == 1) { //miss
			mida_lec_mp = 32;
			lec_mp = 1;
			if (replacement == 1) {
				tag_out = linia[linea_mc].tag;
				linia[linea_mc].tag = tag;
			}
			else {
				linia[linea_mc].valid = 1;
				linia[linea_mc].tag = tag;
			}
		}
		else { //hit
			mida_lec_mp = 0;
			lec_mp = 0;
		}
	}

	else { //Ecriptura
		esc_mp = 1;
		mida_esc_mp = 1;
		lec_mp = 0;
		mida_lec_mp = 0;
	}



	/* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual
	 * */
	test_and_print (address, LE, byte, bloque_m, linea_mc, tag,
			miss, lec_mp, mida_lec_mp, esc_mp, mida_esc_mp,
			replacement, tag_out);
}

/* La rutina final es cridada al final de la simulacio */
void final ()
{
 	/* Escriu aqui el teu codi */
	//printf("Hits: %d\n", hits);
	//printf("Miss: %d\n\n", miss);

}
