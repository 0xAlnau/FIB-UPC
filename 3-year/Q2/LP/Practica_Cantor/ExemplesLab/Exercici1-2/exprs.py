from antlr4 import *
from exprsLexer import exprsLexer
from exprsParser import exprsParser
from exprsVisitor import exprsVisitor

class EvalVisitor(exprsVisitor):
    def __init__(self):
        self.functions = {'+': lambda x, y: x + y,
                          '-': lambda x, y: x - y,
                          '*': lambda x, y: x * y,
                          '/': lambda x, y: x // y,
                          '^': lambda x, y: x ** y,
                          '%': lambda x, y: x % y}

    def visitRoot(self, ctx):
        print(self.visit(ctx.expr()))

    def visitParent(self, ctx:exprsParser.ParentContext):
        return self.visit(ctx.mig)

    def visitBinari(self, ctx):
        expressio1 = ctx.esq
        expressio2 = ctx.dre
        op = ctx.op.text
        return self.functions[op](self.visit(expressio1), self.visit(expressio2))

    def visitNumero(self, ctx):
        return int(ctx.NUM().getText())



input_stream = InputStream(input('? '))
lexer = exprsLexer(input_stream)
token_stream = CommonTokenStream(lexer)
parser = exprsParser(token_stream)
tree = parser.root()

visitor = EvalVisitor()
visitor.visit(tree)
