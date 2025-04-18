#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<mis_funciones.h>

int main(int argc,char *argv[])
{
char buf[128];
	if (Usage(argc)) {
		sprintf(buf,"Usage:listaParametros arg1 [arg2..argn]\nEste programa escribe por su salida la lista de argumentos que recibe\n");
		write(1,buf,strlen(buf));
	}

	else {
		for (int i=0;i<argc;i++){
			if (i==0){
				sprintf(buf,"El argumento %d es %s (es el nombre del ejecutable)\n",i,argv[i]);
			}else{
				sprintf(buf,"El argumento %d es %s\n",i,argv[i]);
			}
			write(1,buf,strlen(buf));
		}
	}
	return 0;
}
