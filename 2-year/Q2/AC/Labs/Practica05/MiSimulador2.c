#include "CacheSim.h"

/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */
int conjunts[64*2]; // 128 perque despres per saber si una via esta ocupada o no fare nlinia*1 (via 0) i nlinia + 64 (via 1)
int last_used[64]; //per saber quin dels dos fer fora si cal
unsigned int num_hits = 0;
unsigned int num_miss = 0;
char buff[256];
int valid[128]; //0 esta buit, 1 ple, fem el mateix que al programa 1
/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al començar cada un dels tests.
 * */
void init_cache ()
{
    totaltime=0.0;
	/* Escriu aqui el teu codi */
	for (int i = 0; i < 64*2; ++i) {
		conjunts[i] = -1;
		if (i < 64) {
			last_used[i] = -1;
		}
	}
}

/* La rutina reference es cridada per cada referencia a simular */ 
void reference (unsigned int address)
{
	unsigned int byte;
	unsigned int bloque_m; 
	unsigned int conj_mc;
	unsigned int via_mc;
	unsigned int tag;
	unsigned int miss;	   // boolea que ens indica si es miss
	unsigned int replacement;  // boolea que indica si es reemplaça una linia valida
	unsigned int tag_out;	   // TAG de la linia reemplaçada
	float t1,t2;		// Variables per mesurar el temps (NO modificar)
	
	t1=GetTime();
	/* Escriu aqui el teu codi */
	byte = address & 0x0000001F; //agafem els ultims 5 bits de Byte
	bloque_m = address >> 5; //movem 5 bits a la dreta
	conj_mc = bloque_m & 0x0000003F; //agafem els 6 bits de conjunt, que son els 6 ultims del bloc
	tag = address >> 11; //desplacem els 5 + 6 bits que sobren

	if (valid[conj_mc] == 0 && valid[conj_mc + 64] == 0) {
		miss = 1; //no hi ha res, miss
		conjunts[conj_mc] = tag; //movem a la cache via 0
		replacement = 0; //no cal reemplaç
		via_mc = 0;
		last_used[conj_mc] = 0;
		++num_miss;
	}

	else if (valid[conj_mc] == 1 || valid[conj_mc + 64] == 1) {
		miss = 0; // hi ha encert
		replacement = 0;
		if (conjunts[conj_mc] == tag) {
			via_mc = 0;
			last_used[conj_mc] = 1;
		}
		else {
			via_mc = 1;
			last_used[conj_mc] = 0;
		}
		++num_hits;
	}

	else if (valid[conj_mc] != 1 && valid[conj_mc + 64] == 0) {
		miss = 1; //cal posar el nou
		conjunts[conj_mc + 64] = tag; //movem a la cache via 1
		replacement = 0;
		via_mc = 1;
		last_used[conj_mc] = 0; //el més antic es el de la via 0
		++num_miss;
	}

	else if (valid[conj_mc] != 1 && conjunts[conj_mc + 64] != tag) {
		miss = 1;
		if (last_used[conj_mc] == 0) { //reemplacem via 0
			tag_out = conjunts[conj_mc]; //treiem el de la via 0
			conjunts[conj_mc] = tag; //posem el nou
			via_mc = 0;
			last_used[conj_mc] = 1;
		}
		else { //reemplacem via 1
			tag_out = conjunts[conj_mc + 64]; //treiem el de la via 0
			conjunts[conj_mc + 64] = tag; //posem el nou
			via_mc = 1;
			last_used[conj_mc] = 0;
		}
		replacement = 1;
		++num_miss;
	}

	else { // primera via buida la segona no
		miss = 1; //cal posar el nou
		conjunts[conj_mc] = tag; //movem a la cache via 1
		replacement = 0;
		via_mc = 0;
		last_used[conj_mc] = 1; //el més antic es el de la via 0
		++num_miss;
	}
	/* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual. També mesurem el temps d'execució
	 * */
	t2=GetTime();
	totaltime+=t2-t1;
	test_and_print2 (address, byte, bloque_m, conj_mc, via_mc, tag,
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
