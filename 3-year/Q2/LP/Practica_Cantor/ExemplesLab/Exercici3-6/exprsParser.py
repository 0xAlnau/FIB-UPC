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
        4,1,23,76,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,1,0,5,0,10,8,0,10,0,12,
        0,13,9,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,1,26,8,1,
        10,1,12,1,29,9,1,1,1,1,1,1,1,1,1,1,1,1,1,5,1,37,8,1,10,1,12,1,40,
        9,1,1,1,1,1,3,1,44,8,1,1,2,1,2,1,2,1,2,1,2,3,2,51,8,2,1,3,1,3,1,
        3,1,3,1,3,1,3,1,3,3,3,60,8,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,
        5,3,71,8,3,10,3,12,3,74,9,3,1,3,0,1,6,4,0,2,4,6,0,3,1,0,13,16,1,
        0,18,20,1,0,21,22,83,0,11,1,0,0,0,2,43,1,0,0,0,4,50,1,0,0,0,6,59,
        1,0,0,0,8,10,3,2,1,0,9,8,1,0,0,0,10,13,1,0,0,0,11,9,1,0,0,0,11,12,
        1,0,0,0,12,14,1,0,0,0,13,11,1,0,0,0,14,15,5,0,0,1,15,1,1,0,0,0,16,
        17,5,10,0,0,17,44,3,6,3,0,18,19,5,12,0,0,19,20,5,9,0,0,20,44,3,6,
        3,0,21,22,5,3,0,0,22,23,3,4,2,0,23,27,5,4,0,0,24,26,3,2,1,0,25,24,
        1,0,0,0,26,29,1,0,0,0,27,25,1,0,0,0,27,28,1,0,0,0,28,30,1,0,0,0,
        29,27,1,0,0,0,30,31,5,7,0,0,31,44,1,0,0,0,32,33,5,5,0,0,33,34,3,
        4,2,0,34,38,5,6,0,0,35,37,3,2,1,0,36,35,1,0,0,0,37,40,1,0,0,0,38,
        36,1,0,0,0,38,39,1,0,0,0,39,41,1,0,0,0,40,38,1,0,0,0,41,42,5,7,0,
        0,42,44,1,0,0,0,43,16,1,0,0,0,43,18,1,0,0,0,43,21,1,0,0,0,43,32,
        1,0,0,0,44,3,1,0,0,0,45,46,3,6,3,0,46,47,7,0,0,0,47,48,3,6,3,0,48,
        51,1,0,0,0,49,51,5,8,0,0,50,45,1,0,0,0,50,49,1,0,0,0,51,5,1,0,0,
        0,52,53,6,3,-1,0,53,54,5,1,0,0,54,55,3,6,3,0,55,56,5,2,0,0,56,60,
        1,0,0,0,57,60,5,11,0,0,58,60,5,12,0,0,59,52,1,0,0,0,59,57,1,0,0,
        0,59,58,1,0,0,0,60,72,1,0,0,0,61,62,10,5,0,0,62,63,5,17,0,0,63,71,
        3,6,3,6,64,65,10,4,0,0,65,66,7,1,0,0,66,71,3,6,3,5,67,68,10,3,0,
        0,68,69,7,2,0,0,69,71,3,6,3,4,70,61,1,0,0,0,70,64,1,0,0,0,70,67,
        1,0,0,0,71,74,1,0,0,0,72,70,1,0,0,0,72,73,1,0,0,0,73,7,1,0,0,0,74,
        72,1,0,0,0,8,11,27,38,43,50,59,70,72
    ]

class exprsParser ( Parser ):

    grammarFileName = "exprs.g4"

    atn = ATNDeserializer().deserialize(serializedATN())

    decisionsToDFA = [ DFA(ds, i) for i, ds in enumerate(atn.decisionToState) ]

    sharedContextCache = PredictionContextCache()

    literalNames = [ "<INVALID>", "'('", "')'", "'if'", "'then'", "'while'", 
                     "'do'", "'end'", "<INVALID>", "':='", "'write'", "<INVALID>", 
                     "<INVALID>", "'='", "'<'", "'>'", "'<>'", "'^'", "'*'", 
                     "'/'", "'%'", "'+'", "'-'" ]

    symbolicNames = [ "<INVALID>", "<INVALID>", "<INVALID>", "IF", "THEN", 
                      "WHILE", "DO", "END", "VALB", "ASSIGNA", "ESCRIU", 
                      "NUM", "VAR", "EQU", "LT", "GT", "DIF", "POW", "MUL", 
                      "DIV", "MOD", "ADD", "SUB", "WS" ]

    RULE_root = 0
    RULE_inst = 1
    RULE_exBo = 2
    RULE_expr = 3

    ruleNames =  [ "root", "inst", "exBo", "expr" ]

    EOF = Token.EOF
    T__0=1
    T__1=2
    IF=3
    THEN=4
    WHILE=5
    DO=6
    END=7
    VALB=8
    ASSIGNA=9
    ESCRIU=10
    NUM=11
    VAR=12
    EQU=13
    LT=14
    GT=15
    DIF=16
    POW=17
    MUL=18
    DIV=19
    MOD=20
    ADD=21
    SUB=22
    WS=23

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

        def inst(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(exprsParser.InstContext)
            else:
                return self.getTypedRuleContext(exprsParser.InstContext,i)


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
            while (((_la) & ~0x3f) == 0 and ((1 << _la) & 5160) != 0):
                self.state = 8
                self.inst()
                self.state = 13
                self._errHandler.sync(self)
                _la = self._input.LA(1)

            self.state = 14
            self.match(exprsParser.EOF)
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



    def inst(self):

        localctx = exprsParser.InstContext(self, self._ctx, self.state)
        self.enterRule(localctx, 2, self.RULE_inst)
        self._la = 0 # Token type
        try:
            self.state = 43
            self._errHandler.sync(self)
            token = self._input.LA(1)
            if token in [10]:
                localctx = exprsParser.EscripturaContext(self, localctx)
                self.enterOuterAlt(localctx, 1)
                self.state = 16
                self.match(exprsParser.ESCRIU)
                self.state = 17
                self.expr(0)
                pass
            elif token in [12]:
                localctx = exprsParser.AssignacioContext(self, localctx)
                self.enterOuterAlt(localctx, 2)
                self.state = 18
                self.match(exprsParser.VAR)
                self.state = 19
                self.match(exprsParser.ASSIGNA)
                self.state = 20
                self.expr(0)
                pass
            elif token in [3]:
                localctx = exprsParser.IfContext(self, localctx)
                self.enterOuterAlt(localctx, 3)
                self.state = 21
                self.match(exprsParser.IF)
                self.state = 22
                localctx.expBo = self.exBo()
                self.state = 23
                self.match(exprsParser.THEN)
                self.state = 27
                self._errHandler.sync(self)
                _la = self._input.LA(1)
                while (((_la) & ~0x3f) == 0 and ((1 << _la) & 5160) != 0):
                    self.state = 24
                    self.inst()
                    self.state = 29
                    self._errHandler.sync(self)
                    _la = self._input.LA(1)

                self.state = 30
                self.match(exprsParser.END)
                pass
            elif token in [5]:
                localctx = exprsParser.WhileContext(self, localctx)
                self.enterOuterAlt(localctx, 4)
                self.state = 32
                self.match(exprsParser.WHILE)
                self.state = 33
                localctx.expBo = self.exBo()
                self.state = 34
                self.match(exprsParser.DO)
                self.state = 38
                self._errHandler.sync(self)
                _la = self._input.LA(1)
                while (((_la) & ~0x3f) == 0 and ((1 << _la) & 5160) != 0):
                    self.state = 35
                    self.inst()
                    self.state = 40
                    self._errHandler.sync(self)
                    _la = self._input.LA(1)

                self.state = 41
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
        self.enterRule(localctx, 4, self.RULE_exBo)
        self._la = 0 # Token type
        try:
            self.state = 50
            self._errHandler.sync(self)
            token = self._input.LA(1)
            if token in [1, 11, 12]:
                localctx = exprsParser.BinariBoolContext(self, localctx)
                self.enterOuterAlt(localctx, 1)
                self.state = 45
                localctx.esq = self.expr(0)
                self.state = 46
                localctx.op = self._input.LT(1)
                _la = self._input.LA(1)
                if not((((_la) & ~0x3f) == 0 and ((1 << _la) & 122880) != 0)):
                    localctx.op = self._errHandler.recoverInline(self)
                else:
                    self._errHandler.reportMatch(self)
                    self.consume()
                self.state = 47
                localctx.dre = self.expr(0)
                pass
            elif token in [8]:
                localctx = exprsParser.CasBaseContext(self, localctx)
                self.enterOuterAlt(localctx, 2)
                self.state = 49
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
        _startState = 6
        self.enterRecursionRule(localctx, 6, self.RULE_expr, _p)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 59
            self._errHandler.sync(self)
            token = self._input.LA(1)
            if token in [1]:
                localctx = exprsParser.ParentContext(self, localctx)
                self._ctx = localctx
                _prevctx = localctx

                self.state = 53
                self.match(exprsParser.T__0)
                self.state = 54
                localctx.mig = self.expr(0)
                self.state = 55
                self.match(exprsParser.T__1)
                pass
            elif token in [11]:
                localctx = exprsParser.NumeroContext(self, localctx)
                self._ctx = localctx
                _prevctx = localctx
                self.state = 57
                self.match(exprsParser.NUM)
                pass
            elif token in [12]:
                localctx = exprsParser.VariabContext(self, localctx)
                self._ctx = localctx
                _prevctx = localctx
                self.state = 58
                self.match(exprsParser.VAR)
                pass
            else:
                raise NoViableAltException(self)

            self._ctx.stop = self._input.LT(-1)
            self.state = 72
            self._errHandler.sync(self)
            _alt = self._interp.adaptivePredict(self._input,7,self._ctx)
            while _alt!=2 and _alt!=ATN.INVALID_ALT_NUMBER:
                if _alt==1:
                    if self._parseListeners is not None:
                        self.triggerExitRuleEvent()
                    _prevctx = localctx
                    self.state = 70
                    self._errHandler.sync(self)
                    la_ = self._interp.adaptivePredict(self._input,6,self._ctx)
                    if la_ == 1:
                        localctx = exprsParser.BinariContext(self, exprsParser.ExprContext(self, _parentctx, _parentState))
                        localctx.esq = _prevctx
                        self.pushNewRecursionContext(localctx, _startState, self.RULE_expr)
                        self.state = 61
                        if not self.precpred(self._ctx, 5):
                            from antlr4.error.Errors import FailedPredicateException
                            raise FailedPredicateException(self, "self.precpred(self._ctx, 5)")
                        self.state = 62
                        localctx.op = self.match(exprsParser.POW)
                        self.state = 63
                        localctx.dre = self.expr(6)
                        pass

                    elif la_ == 2:
                        localctx = exprsParser.BinariContext(self, exprsParser.ExprContext(self, _parentctx, _parentState))
                        localctx.esq = _prevctx
                        self.pushNewRecursionContext(localctx, _startState, self.RULE_expr)
                        self.state = 64
                        if not self.precpred(self._ctx, 4):
                            from antlr4.error.Errors import FailedPredicateException
                            raise FailedPredicateException(self, "self.precpred(self._ctx, 4)")
                        self.state = 65
                        localctx.op = self._input.LT(1)
                        _la = self._input.LA(1)
                        if not((((_la) & ~0x3f) == 0 and ((1 << _la) & 1835008) != 0)):
                            localctx.op = self._errHandler.recoverInline(self)
                        else:
                            self._errHandler.reportMatch(self)
                            self.consume()
                        self.state = 66
                        localctx.dre = self.expr(5)
                        pass

                    elif la_ == 3:
                        localctx = exprsParser.BinariContext(self, exprsParser.ExprContext(self, _parentctx, _parentState))
                        localctx.esq = _prevctx
                        self.pushNewRecursionContext(localctx, _startState, self.RULE_expr)
                        self.state = 67
                        if not self.precpred(self._ctx, 3):
                            from antlr4.error.Errors import FailedPredicateException
                            raise FailedPredicateException(self, "self.precpred(self._ctx, 3)")
                        self.state = 68
                        localctx.op = self._input.LT(1)
                        _la = self._input.LA(1)
                        if not(_la==21 or _la==22):
                            localctx.op = self._errHandler.recoverInline(self)
                        else:
                            self._errHandler.reportMatch(self)
                            self.consume()
                        self.state = 69
                        localctx.dre = self.expr(4)
                        pass

             
                self.state = 74
                self._errHandler.sync(self)
                _alt = self._interp.adaptivePredict(self._input,7,self._ctx)

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
        self._predicates[3] = self.expr_sempred
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
         




