package desastres;

import aima.search.framework.HeuristicFunction;

/**
 * Heurística 2: Minimitza el temps total i a més penalitza el temps d'espera
 * de l'últim grup de prioritat 1 (ferits).
 */
public class DesastresHeuristicFunction2 implements HeuristicFunction {

    // Pes de ponderació de l'arribada tardana de P1
    private double pesP1 = 2.0;

    public DesastresHeuristicFunction2() {}
    public DesastresHeuristicFunction2(double pesP1) { this.pesP1 = pesP1; }

    @Override
    public double getHeuristicValue(Object state) {
        DesastresEstat estat = (DesastresEstat) state;
        // Cost total + pes * retard maxim Prioritat 1
        return estat.getTempsTotal() + (pesP1 * estat.getMaxTempsP1());
    }
}