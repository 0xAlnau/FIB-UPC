OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers

program.exe: program.o Cubeta.o Lavadora.o Prenda.o
	g++ -o program.exe program.o Cubeta.o Lavadora.o Prenda.o

program.o: program.cc Prenda.hh Lavadora.hh Cubeta.hh
	g++ -c $(OPCIONS) program.cc

Prenda.o: Prenda.cc Prenda.hh
	g++ -c $(OPCIONS) Prenda.cc

Cubeta.o: Cubeta.cc Cubeta.hh
	g++ -c $(OPCIONS) Cubeta.cc

Lavadora.o: Lavadora.cc Lavadora.hh
	g++ -c $(OPCIONS) Lavadora.cc

clean:
	rm -f *.o
	rm -f *.exe
	rm -f *.*~
	rm -f *~
	rm -f program.tar

tar: Cubeta.cc Prenda.cc Lavadora.cc program.cc Makefile
	tar -cvf program.tar Cubeta.cc Prenda.cc Lavadora.cc program.cc Makefile
