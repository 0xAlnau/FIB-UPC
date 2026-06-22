from antlr4 import *
from exprsLexer import exprsLexer
from exprsParser import exprsParser
from exprsVisitor import exprsVisitor

class ReturnException(Exception):
    def __init__(self, value):
        self.value = value

class EvalVisitor(exprsVisitor):
    def __init__(self):
        self.functions = {'+': lambda x, y: x + y,
                          '-': lambda x, y: x - y,
                          '*': lambda x, y: x * y,
                          '/': lambda x, y: x // y,
                          '^': lambda x, y: x ** y,
                          '%': lambda x, y: x % y}

        self.variables = []
        self.parametres = {}

        self.functionsB = {'=' : lambda x, y: x == y,
                           '>' : lambda x, y: x > y,
                           '<' : lambda x, y: x < y,
                           '<>': lambda x, y: x != y}

        self.functionsCodi = {}


    def visitRoot(self, ctx):
        nomF = ''
        for n in ctx.proc():
            nomF = n.nomF.text
            self.functionsCodi[nomF] = n
            if nomF != 'main':
                allVars = n.VAR()
                self.parametres[nomF] = []
                for varx in allVars[1:]:
                    self.parametres[nomF].append(varx.getText())

                print(self.parametres[nomF])

        self.variables.append(dict({}))
        self.visit(self.functionsCodi[nomF])
        self.variables.pop()

    # main
    def visitMain(self, ctx:exprsParser.MainContext):
        for inst in ctx.inst():
            self.visit(inst)

    # function
    def visitFunction(self, ctx:exprsParser.FunctionContext):
        try:
            for inst in ctx.inst():
                self.visit(inst)
        except ReturnException as r:
            return r.value

    # callFunction
    def visitCallFunction(self, ctx:exprsParser.CallFunctionContext):
        nomF = ctx.nomF.text
        expressions = ctx.expr()

        valors = []
        for exp in expressions:
            valors.append(self.visit(exp))

        self.variables.append(dict({}))

        i = 0
        for exp in expressions:
            param = self.parametres[nomF][i]
            self.variables[-1][param] = valors[i]
            i = i + 1

        valor = self.visit(self.functionsCodi[nomF])
        self.variables.pop()

        return valor

    # return
    def visitReturn(self, ctx:exprsParser.ReturnContext):
        valor = self.visit(ctx.expr())
        raise ReturnException(valor)

    # write
    def visitEscriptura(self, ctx:exprsParser.EscripturaContext):
        print(self.visit(ctx.expr()))

    # :=
    def visitAssignacio(self, ctx:exprsParser.AssignacioContext):
        valor = self.visit(ctx.expr())
        self.variables[-1][ctx.VAR().getText()] = valor

    # if ... then
    def visitIf(self, ctx:exprsParser.IfContext):
        expressioB = self.visit(ctx.expBo)

        if expressioB == 'TRUE':
            for instruccio in ctx.inst():
                self.visit(instruccio)

    # while ... do ... end
    def visitWhile(self, ctx:exprsParser.WhileContext):
        expressioB = ctx.expBo
        instruccions = ctx.inst()

        while self.visit(expressioB) == 'TRUE':
            for instruccio in instruccions:
                self.visit(instruccio)

    # = > < <>
    def visitBinariBool(self, ctx:exprsParser.BinariBoolContext):
        expressio1 = ctx.esq
        expressio2 = ctx.dre
        op = ctx.op.text
        val = self.functionsB[op](self.visit(expressio1), self.visit(expressio2))
        if (val == 0): return 'FALSE'
        else: return 'TRUE'


    # TRUE o FALSE
    def visitCasBase(self, ctx:exprsParser.CasBaseContext):
        return ctx.VALB().getText()

    # ( ... )
    def visitParent(self, ctx:exprsParser.ParentContext):
        return self.visit(ctx.mig)

    # + - * / ^
    def visitBinari(self, ctx):
        expressio1 = ctx.esq
        expressio2 = ctx.dre
        op = ctx.op.text
        return self.functions[op](self.visit(expressio1), self.visit(expressio2))

    def visitNumero(self, ctx):
        return int(ctx.NUM().getText())

    def visitVariab(self, ctx:exprsParser.VariabContext):
        return self.variables[-1][ctx.VAR().getText()]


input_stream = StdinStream() #InputStream(input('? '))
lexer = exprsLexer(input_stream)
token_stream = CommonTokenStream(lexer)
parser = exprsParser(token_stream)
tree = parser.root()

visitor = EvalVisitor()
visitor.visit(tree)
