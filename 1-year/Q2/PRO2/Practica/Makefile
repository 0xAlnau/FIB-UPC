OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers

program.exe: program.o Riu.o Inventari.o Vaixell.o Producte.o
	g++ -o program.exe *.o

program.o: program.cc Riu.hh
	g++ -c program.cc $(OPCIONS)

Riu.o: Riu.cc Riu.hh Inventari.hh Producte.hh BinTree.hh Vaixell.hh
	g++ -c Riu.cc $(OPCIONS)

Inventari.o: Inventari.cc Inventari.hh Producte.hh
	g++ -c Inventari.cc $(OPCIONS)

Vaixell.o: Vaixell.cc Vaixell.hh
	g++ -c Vaixell.cc $(OPCIONS)

Producte.o: Producte.cc Producte.hh
	g++ -c Producte.cc $(OPCIONS)

clean:
	rm -f *.o
	rm -f *.exe
	rm -f *.tar

tar: program.cc Riu.cc Riu.hh Inventari.cc Inventari.hh Producte.cc Producte.hh  Vaixell.cc Vaixell.hh html.zip Makefile
	tar -cvf practica.tar program.cc Riu.cc Riu.hh Inventari.cc Inventari.hh Producte.cc Producte.hh  Vaixell.cc Vaixell.hh html.zip Makefile
