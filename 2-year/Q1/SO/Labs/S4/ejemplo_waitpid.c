#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

int vect[10];

void
error_y_exit (char *msg, int exit_status)
{
  perror (msg);
  exit (exit_status);
}

void
trata_alarma (int s)
{
  for (int i = 0; i < 10; ++i) kill(vect[i], SIGKILL);
}

int
main (int argc, char *argv[])
{
  int pid, res;
  char buff[256];
  int contador = 0;write (1, buff, strlen (buff));
  int hijos = 0;
  struct sigaction sa;
  sigset_t mask;

  /* Evitamos recibir el SIGALRM fuera del sigsuspend */

  sigemptyset (&mask);
  sigaddset (&mask, SIGALRM);
  sigprocmask (SIG_BLOCK, &mask, NULL);

  for (hijos = 0; hijos < 10; hijos++)
    {
      sprintf (buff, "Creando el hijo numero %d\n", hijos);
      write (1, buff, strlen (buff));

      pid = fork ();
      if (pid == 0)             /* Esta linea la ejecutan tanto el padre como el hijo */
        {
          vect[hijos] = getpid();
          sa.sa_handler = &trata_alarma;
          sa.sa_flags = SA_RESTART;
          sigfillset (&sa.sa_mask);
          if (sigaction (SIGALRM, &sa, NULL) < 0)
            error_y_exit ("sigaction", 1);

          /* Escribe aqui el codigo del proceso hijo */
          sprintf (buff, "Hola, soy %d\n", getpid ());
          write (1, buff, strlen (buff));

          alarm (3);
          sigfillset (&mask);
          sigdelset (&mask, SIGALRM);
          sigdelset (&mask, SIGINT);
          sigsuspend (&mask);

          /* Termina su ejecución */
          exit (0);
        }
      else if (pid < 0)
        {
          /* Se ha producido un error */
          error_y_exit ("Error en el fork", 1);
        }
    }
  /* Esperamos que acaben los hijos */
  while (hijos > 0)
    {
      alarm(2);
      pid = waitpid (-1, &res, 0);
      int left = alarm(0);
      sprintf (buff, "Quedaban %d segundos\n", left);
      write (1, buff, strlen (buff));

      sprintf (buff, "Termina el proceso %d\n", pid);
      write (1, buff, strlen (buff));
      if (WIFEXITED(res)) sprintf (buff, "Termina el proceso %d por causa natural\n", pid);
      else sprintf (buff, "Termina el proceso %d por asesinato\n", pid);
      write (1, buff, strlen (buff));
      hijos--;
      contador++;
    }
  sprintf (buff, "Valor del contador %d\n", contador);
  write (1, buff, strlen (buff));
  return 0;
}
