#include<stdio.h>
#include<string.h>
int MAX_SIZE = 8;

int
esNumero (char *str)
{
  int tamanio = strlen (str);
  int resposta = 1;

  if ((str == NULL || tamanio > MAX_SIZE) && str[0] != '-')
    resposta = 0;
  else
    {
      if (str[0] == '-' || (str[0] >= '0' && str[0] <= '9'))
	{
	  for (int i = 1; i < tamanio; ++i)
	    {
	      if ((str[i] < '0' || str[i] > '9'))
		resposta = 0;
	    }
	}
      else
	resposta = 0;
    }
  return resposta;
}

int
main (int argc, char *argv[])
{
  char buf[128];
  for (int i = 1; i < argc; ++i)
    {				// i = 1 ya que el ejecutable no es un numero
      int indicador = esNumero (argv[i]);

      if (indicador == 1)
	{			//es un numero y menor de 8 cifras
	  sprintf (buf,
		   "El argumento %d (%s) es un numero con menos o igual a 8 cifras\n",
		   i, argv[i]);
	}

      else
	{			//no es un numero
	  sprintf (buf,
		   "El argumento %d (%s) NO es un numero o es un numero con mas de 8 cifras\n",
		   i, argv[i]);
	}
      write (1, buf, strlen (buf));
    }

  return 0;
}
