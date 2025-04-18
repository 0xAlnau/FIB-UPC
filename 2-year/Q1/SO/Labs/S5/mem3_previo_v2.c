#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>

#define REGION_SIZE		4096

int *p;
char buff[256];

void f_sigsev(int s) {
    sprintf(buff, "Error de segmentació, configura p amb un sbrk\n");
    write(1, buff, strlen(buff));
    exit(0);
}

int
main (int argc, char *argv[])
{
  struct sigaction sa;
  sigset_t mask;

  sa.sa_flags = 0;
  sa.sa_handler = f_sigsev;
  sigemptyset(&mask);

  sigaction(SIGSEGV, &sa, NULL);

  sprintf (buff, "Addresses:\n");
  write (1, buff, strlen (buff));
  sprintf (buff, "\tp: %p\n", &p);
  write (1, buff, strlen (buff));

  *p = 5;

  sprintf (buff, "\tp Address: %p, p value: %p, *p: %d\n", &p, p, *p);
  write (1, buff, strlen (buff));

  exit (0);

}
