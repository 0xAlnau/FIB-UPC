#include "CacheSim.h"
#include <stdio.h>
#include <string.h>
/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */
int linies[128]; //en cada linia guardarem quin tag hi ha
int valid[128]; //0 esta buit, 1 ple
unsigned int num_hits = 0;
unsigned int num_miss = 0;
char buff[256];

/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al començar cada un dels tests.
 * */
void init_cache ()
{
    totaltime=0.0;
	/* Escriu aqui el teu codi */
	for (int i = 0; i < 128; ++i) linies[i] = 0;
	for (int j = 0; j < 128; ++j) valid[j] = 0;
}

/* La rutina reference es cridada per cada referencia a simular */ 
void reference (unsigned int address)
{
	unsigned int byte;
	unsigned int bloque_m; 
	unsigned int linea_mc;
	unsigned int tag;
	unsigned int miss;	   // boolea que ens indica si es miss
	unsigned int replacement;  // boolea que indica si es reemplaça una linia valida
	unsigned int tag_out;	   // TAG de la linia reemplaçada
	float t1,t2;		// Variables per mesurar el temps (NO modificar)
	
	t1=GetTime();
	/* Escriu aqui el teu codi */
	byte = address & 0x0000001F; //recullo els ultims 5 bits
	bloque_m = address >> 5; //fem shift dreta 5 vegades, tag + index
	linea_mc = bloque_m & 0x0000007F; //cogemos los 7 bits de linea, que son los ultimos 7 del bloque
	tag = (address & 0xFFFFF000) >> 12; //afagem els 20 bits de TAG

	if (valid[linea_mc] == 1 && linies[linea_mc] != tag) {
		miss = 1; //hi ha miss
		tag_out = linies[linea_mc];
		linies[linea_mc] = tag;
		replacement = 1; //hi ha un reemplaç
		++num_miss;
	}

	else if (valid[linea_mc] == 1 && linies[linea_mc] == tag) {
		miss = 0; //hit
		replacement = 0; //no hi ha reemplaç
		++num_hits;
	}

	else {
		miss = 1;
		linies[linea_mc] = tag;
		replacement = 0;
		++num_miss;
		valid[linea_mc] = 1;
	}

	/* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual. També mesurem el temps d'execució
	 * */
	t2=GetTime();
	totaltime+=t2-t1;
	test_and_print (address, byte, bloque_m, linea_mc, tag,
			miss, replacement, tag_out);
}

/* La rutina final es cridada al final de la simulacio */ 
void final ()
{
 	/* Escriu aqui el teu codi */ 
	sprintf(buff, "Numero de hits: %d\n", num_hits);
	write(1, buff, strlen(buff));

	sprintf(buff, "Numero de miss: %d\n", num_miss);
	write(1, buff, strlen(buff));
  
}
