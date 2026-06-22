package desastres;

import aima.search.framework.Successor;
import aima.search.framework.SuccessorFunction;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * Funció Successora per a Simulated Annealing.
 * Només genera 1 estat veí a l'atzar.
 */
public class DesastresSuccessorFunctionSA implements SuccessorFunction {
    private final Random rand;

    public DesastresSuccessorFunctionSA() {
        this.rand = new Random();
    }

    public DesastresSuccessorFunctionSA(long seed) {
        this.rand = new Random(seed);
    }

    @Override
    public List getSuccessors(Object aState) {
        ArrayList<Successor> retVal = new ArrayList<>();
        DesastresEstat estatActual = (DesastresEstat) aState;
        DesastresEstat nouEstat = new DesastresEstat(estatActual);
        int numCentres = estatActual.getNumCentres();
        int numGrups = DesastresEstat.getGrups().size();
        
        int operador = rand.nextInt(5); 

        boolean aplicat = false;
        int intents = 0;

        while (!aplicat && intents < 10) {
            
            if (operador == 0) { // OPERADOR 1: Moure a un altre centre aleatori
                int c1 = rand.nextInt(numCentres);
                int nGrups1 = nouEstat.getGrupsAlCentre(c1);
                if (nGrups1 > 0) {
                    int c2 = rand.nextInt(numCentres);
                    if (c1 != c2) {
                        int indexGrup = rand.nextInt(nGrups1);
                        nouEstat.moureGrup(c1, indexGrup, c2);
                        retVal.add(new Successor("SA: Moure grup de " + c1 + " a " + c2, nouEstat));
                        aplicat = true;
                    }
                }
                
            } else if (operador == 1) { // OPERADOR 2: Intercanvi en centres diferents
                int c1 = rand.nextInt(numCentres);
                int nGrups1 = nouEstat.getGrupsAlCentre(c1);
                if (nGrups1 > 0) {
                    int c2 = rand.nextInt(numCentres);
                    int nGrups2 = nouEstat.getGrupsAlCentre(c2);
                    if (c1 != c2 && nGrups2 > 0) {
                        nouEstat.intercanviarGrups(c1, rand.nextInt(nGrups1), c2, rand.nextInt(nGrups2));
                        retVal.add(new Successor("SA: Intercanvi extern " + c1 + "-" + c2, nouEstat));
                        aplicat = true;
                    }
                }
                
            } else if (operador == 2) { // OPERADOR 2b: Intercanvi en el mateix centre (canviar d'ordre)
                int c1 = rand.nextInt(numCentres);
                int nGrups1 = nouEstat.getGrupsAlCentre(c1);
                if (nGrups1 > 1) {
                    int idx1 = rand.nextInt(nGrups1);
                    int idx2 = rand.nextInt(nGrups1);
                    if (idx1 != idx2) {
                        nouEstat.intercanviarGrups(c1, idx1, c1, idx2);
                        retVal.add(new Successor("SA: Intercanvi intern a " + c1, nouEstat));
                        aplicat = true;
                    }
                }
                
            } else if (operador == 3) { // OPERADOR 3: Moure un grup a l'atzar a un dels seus K centres propers
                if (numGrups > 0) {
                    int idGrup = rand.nextInt(numGrups);
                    int centreActual = nouEstat.getCentreAssignat(idGrup);
                    
                    int K = 5;
                    List<Integer> centresPropers = nouEstat.getCentresMesPropers(idGrup, K); // Triem un dels K centres propers a l'atzar
                    
                    int cDesti = centresPropers.get(rand.nextInt(centresPropers.size()));
                    
                    if (centreActual != cDesti) {
                        nouEstat.moureGrup(idGrup, cDesti);
                        retVal.add(new Successor("SA: Moure grup " + idGrup + " al centre proper " + cDesti, nouEstat));
                        aplicat = true;
                    }
                }
                
            } else if (operador == 4) { // OPERADOR 4: Alleujar el centre amb més temps
                int pitjorCentre = nouEstat.getCentreAmbMesTemps();
                if (pitjorCentre >= 0) {
                    int nGrupsPitjor = nouEstat.getGrupsAlCentre(pitjorCentre);

                    if (nGrupsPitjor > 0) {
                        int indexGrup = rand.nextInt(nGrupsPitjor); // Agafem un grup a l'atzar d'aquest centre en concret
                        int cDesti = rand.nextInt(numCentres);

                        if (pitjorCentre != cDesti) {
                            nouEstat.moureGrup(pitjorCentre, indexGrup, cDesti);
                            retVal.add(new Successor("SA: Alleujar pitjor centre " + pitjorCentre + " movent a " + cDesti, nouEstat));
                            aplicat = true;
                        }
                    }
                }
            }
            
            intents++;
            if (!aplicat) { // Si l'operador ha fallat, per ex: ha triat mateixes coordenades destí i origen
                operador = rand.nextInt(5);
            }
        }

        // Si no s'ha pogut aplicar cap operador retorna l'actual
        if (!aplicat) {
            retVal.add(new Successor("SA: Sense canvi (intents esgotats)", nouEstat));
        }

        return retVal;
    }
}