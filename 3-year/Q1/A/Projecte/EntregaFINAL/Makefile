OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++17 -fno-extended-identifiers

INCLUDES = -/Radix -/Rway

all: main.exe test.exe

main.exe: main.o RWayTrie.o RadixTrie.o
	g++ -o main.exe *.o

main.o: main.cc RWayTrie.o RadixTrie.o
	g++ -c main.cc $(OPCIONS)

RWayTrie.o: RWayTrie.hh RWayTrie.cc NodeRWay.hh
	g++ -c RWayTrie.cc $(OPCIONS)

RadixTrie.o: RadixTrie.hh RadixTrie.cc NodeRadix.hh
	g++ -c RadixTrie.cc $(OPCIONS)

test.exe: test.o RWayTrie.o RadixTrie.o
	g++ -o $@ $^ $(OPCIONS)

test.o: test.cc RWayTrie.hh RadixTrie.hh
	g++ -c test.cc $(OPCIONS)

test: test.exe
	./test.exe

clean:
	rm -f *.o
	rm -f *.exe
	rm -f *.tar

