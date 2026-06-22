# Generated from exprs.g4 by ANTLR 4.13.1
# encoding: utf-8
from antlr4 import *
from io import StringIO
import sys
if sys.version_info[1] > 5:
	from typing import TextIO
else:
	from typing.io import TextIO

def serializedATN():
    return [
        4,1,27,120,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,1,0,4,0,12,8,
        0,11,0,12,0,13,1,0,1,0,1,1,1,1,5,1,20,8,1,10,1,12,1,23,9,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,5,1,32,8,1,10,1,12,1,35,9,1,1,1,1,1,4,1,39,
        8,1,11,1,12,1,40,1,1,1,1,3,1,45,8,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,
        1,2,1,2,5,2,56,8,2,10,2,12,2,59,9,2,1,2,1,2,1,2,1,2,1,2,1,2,5,2,
        67,8,2,10,2,12,2,70,9,2,1,2,1,2,1,2,1,2,3,2,76,8,2,1,3,1,3,1,3,1,
        3,1,3,3,3,83,8,3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,5,4,95,
        8,4,10,4,12,4,98,9,4,1,4,1,4,1,4,1,4,3,4,104,8,4,1,4,1,4,1,4,1,4,
        1,4,1,4,1,4,1,4,1,4,5,4,115,8,4,10,4,12,4,118,9,4,1,4,0,1,8,5,0,
        2,4,6,8,0,3,1,0,17,20,1,0,22,24,1,0,25,26,133,0,11,1,0,0,0,2,44,
        1,0,0,0,4,75,1,0,0,0,6,82,1,0,0,0,8,103,1,0,0,0,10,12,3,2,1,0,11,
        10,1,0,0,0,12,13,1,0,0,0,13,11,1,0,0,0,13,14,1,0,0,0,14,15,1,0,0,
        0,15,16,5,0,0,1,16,1,1,0,0,0,17,21,5,9,0,0,18,20,3,4,2,0,19,18,1,
        0,0,0,20,23,1,0,0,0,21,19,1,0,0,0,21,22,1,0,0,0,22,24,1,0,0,0,23,
        21,1,0,0,0,24,45,5,8,0,0,25,26,5,11,0,0,26,27,5,16,0,0,27,28,5,1,
        0,0,28,33,5,16,0,0,29,30,5,2,0,0,30,32,5,16,0,0,31,29,1,0,0,0,32,
        35,1,0,0,0,33,31,1,0,0,0,33,34,1,0,0,0,34,36,1,0,0,0,35,33,1,0,0,
        0,36,38,5,3,0,0,37,39,3,4,2,0,38,37,1,0,0,0,39,40,1,0,0,0,40,38,
        1,0,0,0,40,41,1,0,0,0,41,42,1,0,0,0,42,43,5,8,0,0,43,45,1,0,0,0,
        44,17,1,0,0,0,44,25,1,0,0,0,45,3,1,0,0,0,46,47,5,14,0,0,47,76,3,
        8,4,0,48,49,5,16,0,0,49,50,5,13,0,0,50,76,3,8,4,0,51,52,5,4,0,0,
        52,53,3,6,3,0,53,57,5,5,0,0,54,56,3,4,2,0,55,54,1,0,0,0,56,59,1,
        0,0,0,57,55,1,0,0,0,57,58,1,0,0,0,58,60,1,0,0,0,59,57,1,0,0,0,60,
        61,5,8,0,0,61,76,1,0,0,0,62,63,5,6,0,0,63,64,3,6,3,0,64,68,5,7,0,
        0,65,67,3,4,2,0,66,65,1,0,0,0,67,70,1,0,0,0,68,66,1,0,0,0,68,69,
        1,0,0,0,69,71,1,0,0,0,70,68,1,0,0,0,71,72,5,8,0,0,72,76,1,0,0,0,
        73,74,5,10,0,0,74,76,3,8,4,0,75,46,1,0,0,0,75,48,1,0,0,0,75,51,1,
        0,0,0,75,62,1,0,0,0,75,73,1,0,0,0,76,5,1,0,0,0,77,78,3,8,4,0,78,
        79,7,0,0,0,79,80,3,8,4,0,80,83,1,0,0,0,81,83,5,12,0,0,82,77,1,0,
        0,0,82,81,1,0,0,0,83,7,1,0,0,0,84,85,6,4,-1,0,85,86,5,1,0,0,86,87,
        3,8,4,0,87,88,5,3,0,0,88,104,1,0,0,0,89,90,5,16,0,0,90,91,5,1,0,
        0,91,96,3,8,4,0,92,93,5,2,0,0,93,95,3,8,4,0,94,92,1,0,0,0,95,98,
        1,0,0,0,96,94,1,0,0,0,96,97,1,0,0,0,97,99,1,0,0,0,98,96,1,0,0,0,
        99,100,5,3,0,0,100,104,1,0,0,0,101,104,5,15,0,0,102,104,5,16,0,0,
        103,84,1,0,0,0,103,89,1,0,0,0,103,101,1,0,0,0,103,102,1,0,0,0,104,
        116,1,0,0,0,105,106,10,5,0,0,106,107,5,21,0,0,107,115,3,8,4,6,108,
        109,10,4,0,0,109,110,7,1,0,0,110,115,3,8,4,5,111,112,10,3,0,0,112,
        113,7,2,0,0,113,115,3,8,4,4,114,105,1,0,0,0,114,108,1,0,0,0,114,
        111,1,0,0,0,115,118,1,0,0,0,116,114,1,0,0,0,116,117,1,0,0,0,117,
        9,1,0,0,0,118,116,1,0,0,0,13,13,21,33,40,44,57,68,75,82,96,103,114,
        116
    ]

class exprsParser ( Parser ):

    grammarFileName = "exprs.g4"

    atn = ATNDeserializer().deserialize(serializedATN())

    decisionsToDFA = [ DFA(ds, i) for i, ds in enumerate(atn.decisionToState) ]

    sharedContextCache = PredictionContextCache()

    literalNames = [ "<INVALID>", "'('", "','", "')'", "'if'", "'then'", 
                     "'while'", "'do'", "'end'", "'main'", "'return'", "'function'", 
                     "<INVALID>", "':='", "'write'", "<INVALID>", "<INVALID>", 
                     "'='", "'<'", "'>'", "'<>'", "'^'", "'*'", "'/'", "'%'", 
                     "'+'", "'-'" ]

    symbolicNames = [ "<INVALID>", "<INVALID>", "<INVALID>", "<INVALID>", 
                      "IF", "THEN", "WHILE", "DO", "END", "MAIN", "RETURN", 
                      "FUNCTION", "VALB", "ASSIGNA", "ESCRIU", "NUM", "VAR", 
                      "EQU", "LT", "GT", "DIF", "POW", "MUL", "DIV", "MOD", 
                      "ADD", "SUB", "WS" ]

    RULE_root = 0
    RULE_proc = 1
    RULE_inst = 2
    RULE_exBo = 3
    RULE_expr = 4

    ruleNames =  [ "root", "proc", "inst", "exBo", "expr" ]

    EOF = Token.EOF
    T__0=1
    T__1=2
    T__2=3
    IF=4
    THEN=5
    WHILE=6
    DO=7
    END=8
    MAIN=9
    RETURN=10
    FUNCTION=11
    VALB=12
    ASSIGNA=13
    ESCRIU=14
    NUM=15
    VAR=16
    EQU=17
    LT=18
    GT=19
    DIF=20
    POW=21
    MUL=22
    DIV=23
    MOD=24
    ADD=25
    SUB=26
    WS=27

    def __init__(self, input:TokenStream, output:TextIO = sys.stdout):
        super().__init__(input, output)
        self.checkVersion("4.13.1")
        self._interp = ParserATNSimulator(self, self.atn, self.decisionsToDFA, self.sharedContextCache)
        self._predicates = None




    class RootContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def EOF(self):
            return self.getToken(exprsParser.EOF, 0)

        def proc(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(exprsParser.ProcContext)
            else:
                return self.getTypedRuleContext(exprsParser.ProcContext,i)


        def getRuleIndex(self):
            return exprsParser.RULE_root

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitRoot" ):
                return visitor.visitRoot(self)
            else:
                return visitor.visitChildren(self)




    def root(self):

        localctx = exprsParser.RootContext(self, self._ctx, self.state)
        self.enterRule(localctx, 0, self.RULE_root)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 11 
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            while True:
                self.state = 10
                self.proc()
                self.state = 13 
                self._errHandler.sync(self)
                _la = self._input.LA(1)
                if not (_la==9 or _la==11):
                    break

            self.state = 15
            self.match(exprsParser.EOF)
        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class ProcContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser


        def getRuleIndex(self):
            return exprsParser.RULE_proc

     
        def copyFrom(self, ctx:ParserRuleContext):
            super().copyFrom(ctx)



    class FunctionContext(ProcContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a exprsParser.ProcContext
            super().__init__(parser)
            self.nomF = None # Token
            self.var1 = None # Token
            self.varS = None # Token
            self.copyFrom(ctx)

        def FUNCTION(self):
            return self.getToken(exprsParser.FUNCTION, 0)
        def END(self):
            return self.getToken(exprsParser.END, 0)
        def VAR(self, i:int=None):
            if i is None:
                return self.getTokens(exprsParser.VAR)
            else:
                return self.getToken(exprsParser.VAR, i)
        def inst(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(exprsParser.InstContext)
            else:
                return self.getTypedRuleContext(exprsParser.InstContext,i)


        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitFunction" ):
                return visitor.visitFunction(self)
            else:
                return visitor.visitChildren(self)


    class MainContext(ProcContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a exprsParser.ProcContext
            super().__init__(parser)
            self.nomF = None # Token
            self.copyFrom(ctx)

        def END(self):
            return self.getToken(exprsParser.END, 0)
        def MAIN(self):
            return self.getToken(exprsParser.MAIN, 0)
        def inst(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(exprsParser.InstContext)
            else:
                return self.getTypedRuleContext(exprsParser.InstContext,i)


        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitMain" ):
                return visitor.visitMain(self)
            else:
                return visitor.visitChildren(self)



    def proc(self):

        localctx = exprsParser.ProcContext(self, self._ctx, self.state)
        self.enterRule(localctx, 2, self.RULE_proc)
        self._la = 0 # Token type
        try:
            self.state = 44
            self._errHandler.sync(self)
            token = self._input.LA(1)
            if token in [9]:
                localctx = exprsParser.MainContext(self, localctx)
                self.enterOuterAlt(localctx, 1)
                self.state = 17
                localctx.nomF = self.match(exprsParser.MAIN)
                self.state = 21
                self._errHandler.sync(self)
                _la = self._input.LA(1)
                while (((_la) & ~0x3f) == 0 and ((1 << _la) & 83024) != 0):
                    self.state = 18
                    self.inst()
                    self.state = 23
                    self._errHandler.sync(self)
                    _la = self._input.LA(1)

                self.state = 24
                self.match(exprsParser.END)
                pass
            elif token in [11]:
                localctx = exprsParser.FunctionContext(self, localctx)
                self.enterOuterAlt(localctx, 2)
                self.state = 25
                self.match(exprsParser.FUNCTION)
                self.state = 26
                localctx.nomF = self.match(exprsParser.VAR)
                self.state = 27
                self.match(exprsParser.T__0)
                self.state = 28
                localctx.var1 = self.match(exprsParser.VAR)
                self.state = 33
                self._errHandler.sync(self)
                _la = self._input.LA(1)
                while _la==2:
                    self.state = 29
                    self.match(exprsParser.T__1)
                    self.state = 30
                    localctx.varS = self.match(exprsParser.VAR)
                    self.state = 35
                    self._errHandler.sync(self)
                    _la = self._input.LA(1)

                self.state = 36
                self.match(exprsParser.T__2)
                self.state = 38 
                self._errHandler.sync(self)
                _la = self._input.LA(1)
                while True:
                    self.state = 37
                    self.inst()
                    self.state = 40 
                    self._errHandler.sync(self)
                    _la = self._input.LA(1)
                    if not ((((_la) & ~0x3f) == 0 and ((1 << _la) & 83024) != 0)):
                        break

                self.state = 42
                self.match(exprsParser.END)
                pass
            else:
                raise NoViableAltException(self)

        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class InstContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser


        def getRuleIndex(self):
            return exprsParser.RULE_inst

     
        def copyFrom(self, ctx:ParserRuleContext):
            super().copyFrom(ctx)



    class AssignacioContext(InstContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a exprsParser.InstContext
            super().__init__(parser)
            self.copyFrom(ctx)

        def VAR(self):
            return self.getToken(exprsParser.VAR, 0)
        def ASSIGNA(self):
            return self.getToken(exprsParser.ASSIGNA, 0)
        def expr(self):
            return self.getTypedRuleContext(exprsParser.ExprContext,0)


        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitAssignacio" ):
                return visitor.visitAssignacio(self)
            else:
                return visitor.visitChildren(self)


    class EscripturaContext(InstContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a exprsParser.InstContext
            super().__init__(parser)
            self.copyFrom(ctx)

        def ESCRIU(self):
            return self.getToken(exprsParser.ESCRIU, 0)
        def expr(self):
            return self.getTypedRuleContext(exprsParser.ExprContext,0)


        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitEscriptura" ):
                return visitor.visitEscriptura(self)
            else:
                return visitor.visitChildren(self)


    class WhileContext(InstContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a exprsParser.InstContext
            super().__init__(parser)
            self.expBo = None # ExBoContext
            self.copyFrom(ctx)

        def WHILE(self):
            return self.getToken(exprsParser.WHILE, 0)
        def DO(self):
            return self.getToken(exprsParser.DO, 0)
        def END(self):
            return self.getToken(exprsParser.END, 0)
        def exBo(self):
            return self.getTypedRuleContext(exprsParser.ExBoContext,0)

        def inst(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(exprsParser.InstContext)
            else:
                return self.getTypedRuleContext(exprsParser.InstContext,i)


        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitWhile" ):
                return visitor.visitWhile(self)
            else:
                return visitor.visitChildren(self)


    class IfContext(InstContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a exprsParser.InstContext
            super().__init__(parser)
            self.expBo = None # ExBoContext
            self.copyFrom(ctx)

        def IF(self):
            return self.getToken(exprsParser.IF, 0)
        def THEN(self):
            return self.getToken(exprsParser.THEN, 0)
        def END(self):
            return self.getToken(exprsParser.END, 0)
        def exBo(self):
            return self.getTypedRuleContext(exprsParser.ExBoContext,0)

        def inst(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(exprsParser.InstContext)
            else:
                return self.getTypedRuleContext(exprsParser.InstContext,i)


        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitIf" ):
                return visitor.visitIf(self)
            else:
                return visitor.visitChildren(self)


    class ReturnContext(InstContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a exprsParser.InstContext
            super().__init__(parser)
            self.copyFrom(ctx)

        def RETURN(self):
            return self.getToken(exprsParser.RETURN, 0)
        def expr(self):
            return self.getTypedRuleContext(exprsParser.ExprContext,0)


        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitReturn" ):
                return visitor.visitReturn(self)
            else:
                return visitor.visitChildren(self)



    def inst(self):

        localctx = exprsParser.InstContext(self, self._ctx, self.state)
        self.enterRule(localctx, 4, self.RULE_inst)
        self._la = 0 # Token type
        try:
            self.state = 75
            self._errHandler.sync(self)
            token = self._input.LA(1)
            if token in [14]:
                localctx = exprsParser.EscripturaContext(self, localctx)
                self.enterOuterAlt(localctx, 1)
                self.state = 46
                self.match(exprsParser.ESCRIU)
                self.state = 47
                self.expr(0)
                pass
            elif token in [16]:
                localctx = exprsParser.AssignacioContext(self, localctx)
                self.enterOuterAlt(localctx, 2)
                self.state = 48
                self.match(exprsParser.VAR)
                self.state = 49
                self.match(exprsParser.ASSIGNA)
                self.state = 50
                self.expr(0)
                pass
            elif token in [4]:
                localctx = exprsParser.IfContext(self, localctx)
                self.enterOuterAlt(localctx, 3)
                self.state = 51
                self.match(exprsParser.IF)
                self.state = 52
                localctx.expBo = self.exBo()
                self.state = 53
                self.match(exprsParser.THEN)
                self.state = 57
                self._errHandler.sync(self)
                _la = self._input.LA(1)
                while (((_la) & ~0x3f) == 0 and ((1 << _la) & 83024) != 0):
                    self.state = 54
                    self.inst()
                    self.state = 59
                    self._errHandler.sync(self)
                    _la = self._input.LA(1)

                self.state = 60
                self.match(exprsParser.END)
                pass
            elif token in [6]:
                localctx = exprsParser.WhileContext(self, localctx)
                self.enterOuterAlt(localctx, 4)
                self.state = 62
                self.match(exprsParser.WHILE)
                self.state = 63
                localctx.expBo = self.exBo()
                self.state = 64
                self.match(exprsParser.DO)
                self.state = 68
                self._errHandler.sync(self)
                _la = self._input.LA(1)
                while (((_la) & ~0x3f) == 0 and ((1 << _la) & 83024) != 0):
                    self.state = 65
                    self.inst()
                    self.state = 70
                    self._errHandler.sync(self)
                    _la = self._input.LA(1)

                self.state = 71
                self.match(exprsParser.END)
                pass
            elif token in [10]:
                localctx = exprsParser.ReturnContext(self, localctx)
                self.enterOuterAlt(localctx, 5)
                self.state = 73
                self.match(exprsParser.RETURN)
                self.state = 74
                self.expr(0)
                pass
            else:
                raise NoViableAltException(self)

        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class ExBoContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser


        def getRuleIndex(self):
            return exprsParser.RULE_exBo

     
        def copyFrom(self, ctx:ParserRuleContext):
            super().copyFrom(ctx)



    class CasBaseContext(ExBoContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a exprsParser.ExBoContext
            super().__init__(parser)
            self.copyFrom(ctx)

        def VALB(self):
            return self.getToken(exprsParser.VALB, 0)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitCasBase" ):
                return visitor.visitCasBase(self)
            else:
                return visitor.visitChildren(self)


    class BinariBoolContext(ExBoContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a exprsParser.ExBoContext
            super().__init__(parser)
            self.esq = None # ExprContext
            self.op = None # Token
            self.dre = None # ExprContext
            self.copyFrom(ctx)

        def expr(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(exprsParser.ExprContext)
            else:
                return self.getTypedRuleContext(exprsParser.ExprContext,i)

        def EQU(self):
            return self.getToken(exprsParser.EQU, 0)
        def LT(self):
            return self.getToken(exprsParser.LT, 0)
        def GT(self):
            return self.getToken(exprsParser.GT, 0)
        def DIF(self):
            return self.getToken(exprsParser.DIF, 0)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitBinariBool" ):
                return visitor.visitBinariBool(self)
            else:
                return visitor.visitChildren(self)



    def exBo(self):

        localctx = exprsParser.ExBoContext(self, self._ctx, self.state)
        self.enterRule(localctx, 6, self.RULE_exBo)
        self._la = 0 # Token type
        try:
            self.state = 82
            self._errHandler.sync(self)
            token = self._input.LA(1)
            if token in [1, 15, 16]:
                localctx = exprsParser.BinariBoolContext(self, localctx)
                self.enterOuterAlt(localctx, 1)
                self.state = 77
                localctx.esq = self.expr(0)
                self.state = 78
                localctx.op = self._input.LT(1)
                _la = self._input.LA(1)
                if not((((_la) & ~0x3f) == 0 and ((1 << _la) & 1966080) != 0)):
                    localctx.op = self._errHandler.recoverInline(self)
                else:
                    self._errHandler.reportMatch(self)
                    self.consume()
                self.state = 79
                localctx.dre = self.expr(0)
                pass
            elif token in [12]:
                localctx = exprsParser.CasBaseContext(self, localctx)
                self.enterOuterAlt(localctx, 2)
                self.state = 81
                self.match(exprsParser.VALB)
                pass
            else:
                raise NoViableAltException(self)

        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class ExprContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser


        def getRuleIndex(self):
            return exprsParser.RULE_expr

     
        def copyFrom(self, ctx:ParserRuleContext):
            super().copyFrom(ctx)


    class ParentContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a exprsParser.ExprContext
            super().__init__(parser)
            self.mig = None # ExprContext
            self.copyFrom(ctx)

        def expr(self):
            return self.getTypedRuleContext(exprsParser.ExprContext,0)


        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitParent" ):
                return visitor.visitParent(self)
            else:
                return visitor.visitChildren(self)


    class NumeroContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a exprsParser.ExprContext
            super().__init__(parser)
            self.copyFrom(ctx)

        def NUM(self):
            return self.getToken(exprsParser.NUM, 0)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitNumero" ):
                return visitor.visitNumero(self)
            else:
                return visitor.visitChildren(self)


    class BinariContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a exprsParser.ExprContext
            super().__init__(parser)
            self.esq = None # ExprContext
            self.op = None # Token
            self.dre = None # ExprContext
            self.copyFrom(ctx)

        def expr(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(exprsParser.ExprContext)
            else:
                return self.getTypedRuleContext(exprsParser.ExprContext,i)

        def POW(self):
            return self.getToken(exprsParser.POW, 0)
        def MUL(self):
            return self.getToken(exprsParser.MUL, 0)
        def DIV(self):
            return self.getToken(exprsParser.DIV, 0)
        def MOD(self):
            return self.getToken(exprsParser.MOD, 0)
        def ADD(self):
            return self.getToken(exprsParser.ADD, 0)
        def SUB(self):
            return self.getToken(exprsParser.SUB, 0)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitBinari" ):
                return visitor.visitBinari(self)
            else:
                return visitor.visitChildren(self)


    class CallFunctionContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a exprsParser.ExprContext
            super().__init__(parser)
            self.nomF = None # Token
            self.copyFrom(ctx)

        def expr(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(exprsParser.ExprContext)
            else:
                return self.getTypedRuleContext(exprsParser.ExprContext,i)

        def VAR(self):
            return self.getToken(exprsParser.VAR, 0)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitCallFunction" ):
                return visitor.visitCallFunction(self)
            else:
                return visitor.visitChildren(self)


    class VariabContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a exprsParser.ExprContext
            super().__init__(parser)
            self.copyFrom(ctx)

        def VAR(self):
            return self.getToken(exprsParser.VAR, 0)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitVariab" ):
                return visitor.visitVariab(self)
            else:
                return visitor.visitChildren(self)



    def expr(self, _p:int=0):
        _parentctx = self._ctx
        _parentState = self.state
        localctx = exprsParser.ExprContext(self, self._ctx, _parentState)
        _prevctx = localctx
        _startState = 8
        self.enterRecursionRule(localctx, 8, self.RULE_expr, _p)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 103
            self._errHandler.sync(self)
            la_ = self._interp.adaptivePredict(self._input,10,self._ctx)
            if la_ == 1:
                localctx = exprsParser.ParentContext(self, localctx)
                self._ctx = localctx
                _prevctx = localctx

                self.state = 85
                self.match(exprsParser.T__0)
                self.state = 86
                localctx.mig = self.expr(0)
                self.state = 87
                self.match(exprsParser.T__2)
                pass

            elif la_ == 2:
                localctx = exprsParser.CallFunctionContext(self, localctx)
                self._ctx = localctx
                _prevctx = localctx
                self.state = 89
                localctx.nomF = self.match(exprsParser.VAR)
                self.state = 90
                self.match(exprsParser.T__0)
                self.state = 91
                self.expr(0)
                self.state = 96
                self._errHandler.sync(self)
                _la = self._input.LA(1)
                while _la==2:
                    self.state = 92
                    self.match(exprsParser.T__1)
                    self.state = 93
                    self.expr(0)
                    self.state = 98
                    self._errHandler.sync(self)
                    _la = self._input.LA(1)

                self.state = 99
                self.match(exprsParser.T__2)
                pass

            elif la_ == 3:
                localctx = exprsParser.NumeroContext(self, localctx)
                self._ctx = localctx
                _prevctx = localctx
                self.state = 101
                self.match(exprsParser.NUM)
                pass

            elif la_ == 4:
                localctx = exprsParser.VariabContext(self, localctx)
                self._ctx = localctx
                _prevctx = localctx
                self.state = 102
                self.match(exprsParser.VAR)
                pass


            self._ctx.stop = self._input.LT(-1)
            self.state = 116
            self._errHandler.sync(self)
            _alt = self._interp.adaptivePredict(self._input,12,self._ctx)
            while _alt!=2 and _alt!=ATN.INVALID_ALT_NUMBER:
                if _alt==1:
                    if self._parseListeners is not None:
                        self.triggerExitRuleEvent()
                    _prevctx = localctx
                    self.state = 114
                    self._errHandler.sync(self)
                    la_ = self._interp.adaptivePredict(self._input,11,self._ctx)
                    if la_ == 1:
                        localctx = exprsParser.BinariContext(self, exprsParser.ExprContext(self, _parentctx, _parentState))
                        localctx.esq = _prevctx
                        self.pushNewRecursionContext(localctx, _startState, self.RULE_expr)
                        self.state = 105
                        if not self.precpred(self._ctx, 5):
                            from antlr4.error.Errors import FailedPredicateException
                            raise FailedPredicateException(self, "self.precpred(self._ctx, 5)")
                        self.state = 106
                        localctx.op = self.match(exprsParser.POW)
                        self.state = 107
                        localctx.dre = self.expr(6)
                        pass

                    elif la_ == 2:
                        localctx = exprsParser.BinariContext(self, exprsParser.ExprContext(self, _parentctx, _parentState))
                        localctx.esq = _prevctx
                        self.pushNewRecursionContext(localctx, _startState, self.RULE_expr)
                        self.state = 108
                        if not self.precpred(self._ctx, 4):
                            from antlr4.error.Errors import FailedPredicateException
                            raise FailedPredicateException(self, "self.precpred(self._ctx, 4)")
                        self.state = 109
                        localctx.op = self._input.LT(1)
                        _la = self._input.LA(1)
                        if not((((_la) & ~0x3f) == 0 and ((1 << _la) & 29360128) != 0)):
                            localctx.op = self._errHandler.recoverInline(self)
                        else:
                            self._errHandler.reportMatch(self)
                            self.consume()
                        self.state = 110
                        localctx.dre = self.expr(5)
                        pass

                    elif la_ == 3:
                        localctx = exprsParser.BinariContext(self, exprsParser.ExprContext(self, _parentctx, _parentState))
                        localctx.esq = _prevctx
                        self.pushNewRecursionContext(localctx, _startState, self.RULE_expr)
                        self.state = 111
                        if not self.precpred(self._ctx, 3):
                            from antlr4.error.Errors import FailedPredicateException
                            raise FailedPredicateException(self, "self.precpred(self._ctx, 3)")
                        self.state = 112
                        localctx.op = self._input.LT(1)
                        _la = self._input.LA(1)
                        if not(_la==25 or _la==26):
                            localctx.op = self._errHandler.recoverInline(self)
                        else:
                            self._errHandler.reportMatch(self)
                            self.consume()
                        self.state = 113
                        localctx.dre = self.expr(4)
                        pass

             
                self.state = 118
                self._errHandler.sync(self)
                _alt = self._interp.adaptivePredict(self._input,12,self._ctx)

        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.unrollRecursionContexts(_parentctx)
        return localctx



    def sempred(self, localctx:RuleContext, ruleIndex:int, predIndex:int):
        if self._predicates == None:
            self._predicates = dict()
        self._predicates[4] = self.expr_sempred
        pred = self._predicates.get(ruleIndex, None)
        if pred is None:
            raise Exception("No predicate with index:" + str(ruleIndex))
        else:
            return pred(localctx, predIndex)

    def expr_sempred(self, localctx:ExprContext, predIndex:int):
            if predIndex == 0:
                return self.precpred(self._ctx, 5)
         

            if predIndex == 1:
                return self.precpred(self._ctx, 4)
         

            if predIndex == 2:
                return self.precpred(self._ctx, 3)
         




