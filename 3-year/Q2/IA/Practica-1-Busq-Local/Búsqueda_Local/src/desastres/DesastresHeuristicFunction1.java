package desastres;

import aima.search.framework.HeuristicFunction;

/**
 * Heurística 1: Minimitza exclusivament la suma total del temps
 * emprat per tots els helicòpters.
 */
public class DesastresHeuristicFunction1 implements HeuristicFunction {

    @Override
    public double getHeuristicValue(Object state) {
        DesastresEstat estat = (DesastresEstat) state;
        return estat.getTempsTotal();
    }
}