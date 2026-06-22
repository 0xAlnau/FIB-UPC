all: antlr4

antlr4:
	antlr4 -Dlanguage=Python3 -no-listener -visitor cantor.g4

clean:
	rm -f *.tokens
	rm -f *.interp
	rm -f cantorParser.py
	rm -f cantorLexer.py
	rm -f cantorVisitor.py

