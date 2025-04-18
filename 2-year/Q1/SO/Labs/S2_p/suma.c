#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include"mis_funciones.h"

int
main (int argc, char *argv[])
{
  char buf[128];
  bool error = false;
  int suma = 0;
  for (int i = 1; error == false && i < argc; ++i)
    {				// i = 1 ya que el ejecutable no es un numero
      int indicador = esNumero (argv[i]);

      if (indicador == 0)
	{			//es un numero y menor de 8 cifras
	  sprintf (buf,"Error: el parametro '%s' no es un numero\n",argv[i]);
      error = true;
	}

      else
	{			//no es un numero
	  suma = suma + mi_atoi(argv[i]);
	}
    }
  if (error) {}

  else {
    sprintf (buf,"La suma es %d\n", suma);
  }
  write (1, buf, strlen (buf));
  return 0;
}
