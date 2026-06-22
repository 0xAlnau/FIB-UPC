# Generated from exprs.g4 by ANTLR 4.13.1
from antlr4 import *
from io import StringIO
import sys
if sys.version_info[1] > 5:
    from typing import TextIO
else:
    from typing.io import TextIO


def serializedATN():
    return [
        4,0,10,49,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,
        6,7,6,2,7,7,7,2,8,7,8,2,9,7,9,1,0,1,0,1,1,1,1,1,2,4,2,27,8,2,11,
        2,12,2,28,1,3,1,3,1,4,1,4,1,5,1,5,1,6,1,6,1,7,1,7,1,8,1,8,1,9,4,
        9,44,8,9,11,9,12,9,45,1,9,1,9,0,0,10,1,1,3,2,5,3,7,4,9,5,11,6,13,
        7,15,8,17,9,19,10,1,0,2,1,0,48,57,3,0,9,10,13,13,32,32,50,0,1,1,
        0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,
        0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,1,21,1,0,0,
        0,3,23,1,0,0,0,5,26,1,0,0,0,7,30,1,0,0,0,9,32,1,0,0,0,11,34,1,0,
        0,0,13,36,1,0,0,0,15,38,1,0,0,0,17,40,1,0,0,0,19,43,1,0,0,0,21,22,
        5,40,0,0,22,2,1,0,0,0,23,24,5,41,0,0,24,4,1,0,0,0,25,27,7,0,0,0,
        26,25,1,0,0,0,27,28,1,0,0,0,28,26,1,0,0,0,28,29,1,0,0,0,29,6,1,0,
        0,0,30,31,5,94,0,0,31,8,1,0,0,0,32,33,5,42,0,0,33,10,1,0,0,0,34,
        35,5,47,0,0,35,12,1,0,0,0,36,37,5,37,0,0,37,14,1,0,0,0,38,39,5,43,
        0,0,39,16,1,0,0,0,40,41,5,45,0,0,41,18,1,0,0,0,42,44,7,1,0,0,43,
        42,1,0,0,0,44,45,1,0,0,0,45,43,1,0,0,0,45,46,1,0,0,0,46,47,1,0,0,
        0,47,48,6,9,0,0,48,20,1,0,0,0,3,0,28,45,1,6,0,0
    ]

class exprsLexer(Lexer):

    atn = ATNDeserializer().deserialize(serializedATN())

    decisionsToDFA = [ DFA(ds, i) for i, ds in enumerate(atn.decisionToState) ]

    T__0 = 1
    T__1 = 2
    NUM = 3
    POW = 4
    MUL = 5
    DIV = 6
    MOD = 7
    ADD = 8
    SUB = 9
    WS = 10

    channelNames = [ u"DEFAULT_TOKEN_CHANNEL", u"HIDDEN" ]

    modeNames = [ "DEFAULT_MODE" ]

    literalNames = [ "<INVALID>",
            "'('", "')'", "'^'", "'*'", "'/'", "'%'", "'+'", "'-'" ]

    symbolicNames = [ "<INVALID>",
            "NUM", "POW", "MUL", "DIV", "MOD", "ADD", "SUB", "WS" ]

    ruleNames = [ "T__0", "T__1", "NUM", "POW", "MUL", "DIV", "MOD", "ADD", 
                  "SUB", "WS" ]

    grammarFileName = "exprs.g4"

    def __init__(self, input=None, output:TextIO = sys.stdout):
        super().__init__(input, output)
        self.checkVersion("4.13.1")
        self._interp = LexerATNSimulator(self, self.atn, self.decisionsToDFA, PredictionContextCache())
        self._actions = None
        self._predicates = None


