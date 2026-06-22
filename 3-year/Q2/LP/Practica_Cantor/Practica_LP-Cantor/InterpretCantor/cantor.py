import sys
from math import isqrt
from antlr4 import *
from cantorLexer import cantorLexer
from cantorParser import cantorParser
from cantorVisitor import cantorVisitor

# excepcions
class CantorError(Exception):
    """Classe base per a tots els errors de l'intèrpret Cantor."""
    pass

class CantorValueError(CantorError):
    """S'alça quan els valors d'entrada no són vàlids."""
    pass

class CantorNameError(CantorError):
    """S'alça quan es crida una funció que no està definida."""
    pass

class CantorImportError(CantorError):
    """S'alça quan hi ha problemes en carregar o parsejar un import."""
    pass

class CantorRuntimeError(CantorError):
    """S'alça per errors d'execució en operadors o l'absència del main."""
    pass


# pi i unpi
def pi(x, y):
    valor = (x**2 + x + 2*x*y + 3*y + y**2) // 2
    return valor

def unpi(z):
    w = (isqrt(8*z + 1) - 1) // 2
    t = (w**2 + w) // 2
    y = int(z - t)
    x = int(w - y)
    return [x, y]


# classe visitor
class EvalVisitor(cantorVisitor):
    def __init__(self):
        self.val_act = 0
        self.extended = False
        self.arxius_importats = set()
        self.nom2func = {}
        self.func_basic = {
            'id'  : lambda x    : x,
            'k_1' : lambda x    : 1,
            'fst' : lambda x, y : x,
            'snd' : lambda x, y : y,
            'add' : lambda x, y : x + y,
            'diff': lambda x, y : max(0, x - y),
            'mul' : lambda x, y : x * y
        }

    # per a no duplicar codi del pair
    def pair(self, ctx, is_compair):
        if not is_compair:
            val_ori = self.val_act

            self.visit(ctx.f)
            val_fin = self.val_act

            self.val_act = val_ori
            self.visit(ctx.g)

            self.val_act = pi(val_fin, self.val_act)
        else:
            val_ori = self.val_act

            self.visit(ctx.g)
            val_fin = self.val_act

            self.val_act = val_ori
            self.visit(ctx.h)

            self.val_act = pi(val_fin, self.val_act)

    # root
    def visitRoot(self, ctx: cantorParser.RootContext):
        nums = ctx.NUM()
        l = []

        # processem la llista inicial
        if len(nums) == 0:              # si la llista inicial és buida llavors 0
            l.append(0)
        else:                           # sinó creem la llista dels paràmetres
            try:
                for x in nums:
                    num = int(x.getText())
                    l.append(num)
            except ValueError:
                raise CantorValueError("L'entrada proporcionada no és correcta.")

        while len(l) > 1:               # calculem valor d'entrada
            x = l[-2]
            y = l[-1]
            l.pop()
            l.pop()
            val = pi(x, y)
            l.append(val)

        # mirem mode extended
        exte = ctx.exte()
        if exte is not None and exte.getText() == 'extended':
            self.extended = True

        # processem imports
        importacions = ctx.impo()
        if len(importacions) != 0:
            for i in importacions:
                self.visit(i)

        # processem cada funció nova
        funcs = ctx.deFu()
        if len(funcs) != 0:
            for x in funcs:
                nom = x.NOMF().getText()
                op  = x.op.text
                if (op != 'compair' and op != 'primrec') or self.extended:       # només afegim si es pot
                    self.nom2func[nom] = x

        # executem el main si existeix
        if ctx.main() is not None:
            self.val_act = l[0]
            self.visit(ctx.main())
            print(self.val_act)
        else:
            raise CantorRuntimeError("No s'ha trobat la directiva 'main' al fitxer principal.")

    # mainI
    def visitMainI(self, ctx: cantorParser.MainIContext):
        nom_f = ctx.func().getText()
        if nom_f in self.func_basic:   # mirem una funció bàsica
            self.visit(ctx.func())
        elif nom_f in self.nom2func:   # mirem una funció definida
            self.visit(self.nom2func[nom_f])
        else:
            raise CantorNameError(f"La funció '{nom_f}' cridada al 'main' no està definida.")

    # importa
    def visitImporta(self, ctx: cantorParser.ImportaContext):
        nom_fitxer = ctx.NOMF().getText()
        if nom_fitxer not in self.arxius_importats:                  # per evitar recursions infinites
            self.arxius_importats.add(nom_fitxer)
            ruta = "../ScriptsCantor/" + nom_fitxer + '.cantor'

            try:
                with open(ruta, 'r') as f:                             # llegim tot el codi
                    codi = f.read()
            except FileNotFoundError:
                raise CantorImportError(f"No s'ha trobat l'arxiu d'importació '{ruta}'.")
            except Exception as e:
                raise CantorImportError(f"Error inesperat en llegir l'arxiu '{ruta}': {e}")

            try:
                input_stream = InputStream(codi)
                lexer = cantorLexer(input_stream)
                token_stream = CommonTokenStream(lexer)
                parser = cantorParser(token_stream)
                tree_imp = parser.root()                                # generem arbre nou

                # processem imports de l'arxiu importat
                importacions = tree_imp.impo()
                if len(importacions) != 0:
                    for i in importacions:
                        self.visit(i)

                # processem cada funció nova de l'arxiu importat
                funcs = tree_imp.deFu()
                if len(funcs) != 0:
                    for x in funcs:
                        nom = x.NOMF().getText()
                        op  = x.op.text
                        if (op != 'compair' and op != 'primrec') or self.extended:    # Només afegim si es pot
                            self.nom2func[nom] = x

            except CantorError:
                # propaguem les nostres pròpies excepcions si s'alcen recursivament
                raise
            except Exception as e:
                raise CantorImportError(f"Error crític en parsejar l'arxiu importat '{nom_fitxer}': {e}")

    # function
    def visitFunction(self, ctx: cantorParser.FunctionContext):
        op = ctx.op.text

        if op == 'pair':
            self.pair(ctx, False)

        elif op == 'comp':
            self.visit(ctx.g)
            self.visit(ctx.f)

        elif op == 'compair':
            self.pair(ctx, True)  # pair
            self.visit(ctx.f)     # comp

        elif op == 'mu':
            found = False
            i = 0
            val_ori = self.val_act
            while not found:
                self.val_act = pi(val_ori, i)
                self.visit(ctx.f)

                if self.val_act == 1:
                    found = True
                    self.val_act = i              # h(x) = i

                i = i + 1
        else:
            x = self.val_act
            tupla = 0
            ult_valor = 0

            for i in range(0, x+1):
                self.val_act = i
                self.visit(ctx.f)
                is_cas_base = self.val_act

                if is_cas_base == 1:              # estem a cas base?
                    self.val_act = i
                    self.visit(ctx.g)
                    ult_valor = self.val_act
                    tupla = ult_valor             # afegim cas base
                else:                             # cas recursiu
                    self.val_act = pi(i, tupla)
                    self.visit(ctx.h)
                    ult_valor = self.val_act
                    tupla = pi(ult_valor, tupla)  # afegim cas recursiu

            self.val_act = ult_valor

    # nomFunction
    def visitNomFunction(self, ctx: cantorParser.NomFunctionContext):
        nom_f = ctx.NOMF().getText()
        if nom_f in self.nom2func:
            self.visit(self.nom2func[nom_f])
        else:
            raise CantorNameError(f"La funció '{nom_f}' cridada no està definida.")

    # unaria
    def visitUnaria(self, ctx: cantorParser.UnariaContext):
        op = ctx.un.text
        try:
            self.val_act = self.func_basic[op](self.val_act)
        except Exception as e:
            raise CantorRuntimeError(f"Error aplicant l'operador unari '{op}': {e}")

    # binaria
    def visitBinaria(self, ctx: cantorParser.BinariaContext):
        op = ctx.bi.text
        try:
            l = unpi(self.val_act)
            self.val_act = self.func_basic[op](l[0], l[1])
        except Exception as e:
            raise CantorRuntimeError(f"Error aplicant l'operador binari '{op}': {e}")


# codi inicial
try:
    arxiu = sys.argv[1]
except IndexError:
    print("Error: Cal proporcionar un fitxer .cantor com a argument (ex: python3 cantor.py script.cantor).", file=sys.stderr)
    sys.exit(1)

arxiu = '../ScriptsCantor/' + arxiu    # busquem a la carpeta de codis

try:
    with open(arxiu, 'r') as f:            # llegim tot el codi
        codi = f.read()
except FileNotFoundError:
    print(f"Error: No s'ha trobat el fitxer '{arxiu}'.", file=sys.stderr)
    sys.exit(1)
except IOError as e:
    print(f"Error de lectura al fitxer '{arxiu}': {e}", file=sys.stderr)
    sys.exit(1)

try:
    numeros = sys.stdin.read().strip()     # agafem els números d'entrada
except Exception as e:
    print(f"Error llegint de l'entrada estàndard: {e}", file=sys.stderr)
    sys.exit(1)

entrada = numeros + "\n" + codi

try:
    input_stream = InputStream(entrada)
    lexer = cantorLexer(input_stream)
    token_stream = CommonTokenStream(lexer)
    parser = cantorParser(token_stream)
    tree = parser.root()

    visitor = EvalVisitor()
    visitor.visit(tree)

except CantorError as ce:
    # captura centralitzada d'errors del llenguatge definits per nosaltres
    print(f"Error d'execució Cantor: {ce}", file=sys.stderr)
    sys.exit(1)
except Exception as e:
    # captura de qualsevol fallada inesperada de Python/ANTLR (un bug de l'intèrpret)
    print(f"Error crític de l'intèrpret: {e}", file=sys.stderr)
    sys.exit(1)
