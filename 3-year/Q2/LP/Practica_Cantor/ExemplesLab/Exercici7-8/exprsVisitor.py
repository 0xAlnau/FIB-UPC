# Generated from exprs.g4 by ANTLR 4.13.1
from antlr4 import *
if "." in __name__:
    from .exprsParser import exprsParser
else:
    from exprsParser import exprsParser

# This class defines a complete generic visitor for a parse tree produced by exprsParser.

class exprsVisitor(ParseTreeVisitor):

    # Visit a parse tree produced by exprsParser#root.
    def visitRoot(self, ctx:exprsParser.RootContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#main.
    def visitMain(self, ctx:exprsParser.MainContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#function.
    def visitFunction(self, ctx:exprsParser.FunctionContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#escriptura.
    def visitEscriptura(self, ctx:exprsParser.EscripturaContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#assignacio.
    def visitAssignacio(self, ctx:exprsParser.AssignacioContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#if.
    def visitIf(self, ctx:exprsParser.IfContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#while.
    def visitWhile(self, ctx:exprsParser.WhileContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#return.
    def visitReturn(self, ctx:exprsParser.ReturnContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#binariBool.
    def visitBinariBool(self, ctx:exprsParser.BinariBoolContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#casBase.
    def visitCasBase(self, ctx:exprsParser.CasBaseContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#parent.
    def visitParent(self, ctx:exprsParser.ParentContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#numero.
    def visitNumero(self, ctx:exprsParser.NumeroContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#binari.
    def visitBinari(self, ctx:exprsParser.BinariContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#callFunction.
    def visitCallFunction(self, ctx:exprsParser.CallFunctionContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by exprsParser#variab.
    def visitVariab(self, ctx:exprsParser.VariabContext):
        return self.visitChildren(ctx)



del exprsParser