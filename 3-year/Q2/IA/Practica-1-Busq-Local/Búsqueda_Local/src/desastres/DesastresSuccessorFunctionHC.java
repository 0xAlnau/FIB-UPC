package desastres;

import aima.search.framework.Successor;
import aima.search.framework.SuccessorFunction;

import java.util.ArrayList;
import java.util.EnumSet;
import java.util.List;

/**
 * Aquesta classe genera els estats veïns (successors) a partir d'un estat donat.
 */
public class DesastresSuccessorFunctionHC implements SuccessorFunction {

    public enum Operador {
        OP1_MOURE_EXHAUSTIU,
        OP2_INTERCANVIAR,
        OP3_MOURE_K_NEAREST,
        OP4_ALLEUJAR_PITJOR
    }

    private final EnumSet<Operador> operadorsActius;
    private final int kNearest;

    public DesastresSuccessorFunctionHC() {
        this(EnumSet.of(Operador.OP3_MOURE_K_NEAREST, Operador.OP4_ALLEUJAR_PITJOR), 5);
    }

    public DesastresSuccessorFunctionHC(EnumSet<Operador> operadors) {
        this(operadors, 3);
    }

    public DesastresSuccessorFunctionHC(EnumSet<Operador> operadors, int kNearest) {
        this.operadorsActius = operadors;
        this.kNearest = kNearest;
    }

    @Override
    public List getSuccessors(Object aState) {
        ArrayList<Successor> retVal = new ArrayList<>();
        DesastresEstat estatActual = (DesastresEstat) aState;
        int numCentres = estatActual.getNumCentres();
        int numGrups = DesastresEstat.getGrups().size();

        // Operador 1: Moure un grup d'un centre a un altre (exhaustiu)
        if (operadorsActius.contains(Operador.OP1_MOURE_EXHAUSTIU)) {
            for (int cOrigen = 0; cOrigen < numCentres; cOrigen++) {
                int grupsAlCentre = estatActual.getGrupsAlCentre(cOrigen);
                for (int i = 0; i < grupsAlCentre; i++) {
                    for (int cDesti = 0; cDesti < numCentres; cDesti++) {
                        if (cOrigen != cDesti) {
                            DesastresEstat nouEstat = new DesastresEstat(estatActual);
                            nouEstat.moureGrup(cOrigen, i, cDesti);
                            retVal.add(new Successor("Moure grup " + i + " de centre " + cOrigen + " a " + cDesti, nouEstat));
                        }
                    }
                }
            }
        }

        // Operador 2: Intercanviar dos grups (diferent o mateix centre)
        if (operadorsActius.contains(Operador.OP2_INTERCANVIAR)) {
            for (int c1 = 0; c1 < numCentres; c1++) {
                for (int i = 0; i < estatActual.getGrupsAlCentre(c1); i++) {
                    for (int c2 = c1; c2 < numCentres; c2++) {
                        int iniciJ = (c1 == c2) ? i + 1 : 0;
                        for (int j = iniciJ; j < estatActual.getGrupsAlCentre(c2); j++) {
                            DesastresEstat nouEstat = new DesastresEstat(estatActual);
                            nouEstat.intercanviarGrups(c1, i, c2, j);
                            if (c1 == c2) {
                                retVal.add(new Successor("Intercanviar ordre dins centre " + c1 + ", grup " + i + " per grup " + j, nouEstat));
                            } else {
                                retVal.add(new Successor("Intercanviar grup " + i + " centre " + c1 + " per grup " + j + " centre " + c2, nouEstat));
                            }
                        }
                    }
                }
            }
        }

        // Operador 3: Moure un grup als seus k centres més propers
        if (operadorsActius.contains(Operador.OP3_MOURE_K_NEAREST)) {
            for (int i = 0; i < numGrups; i++) {
                int centreActual = estatActual.getCentreAssignat(i);
                List<Integer> centresPropers = estatActual.getCentresMesPropers(i, kNearest);

                for (int j : centresPropers) {
                    if (centreActual != j) {
                        DesastresEstat nouEstat = new DesastresEstat(estatActual);
                        nouEstat.moureGrup(i, j);
                        retVal.add(new Successor("Moure grup " + i + " al centre proper " + j, nouEstat));
                    }
                }
            }
        }

        // Operador 4: Moure només els grups del centre amb més temps d'espera
        if (operadorsActius.contains(Operador.OP4_ALLEUJAR_PITJOR)) {
            int pitjorCentre = estatActual.getCentreAmbMesTemps();
            for (int i = 0; i < numGrups; i++) {
                if (estatActual.getCentreAssignat(i) == pitjorCentre) {
                    for (int j = 0; j < numCentres; j++) {
                        if (j != pitjorCentre) {
                            DesastresEstat nouEstat = new DesastresEstat(estatActual);
                            nouEstat.moureGrup(i, j);
                            retVal.add(new Successor("Alleujar pitjor centre movent grup " + i + " a " + j, nouEstat));
                        }
                    }
                }
            }
        }

        return retVal;
    }
}