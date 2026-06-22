package desastres;

import aima.search.framework.HeuristicFunction;
import aima.search.framework.Problem;
import aima.search.framework.Search;
import aima.search.framework.SearchAgent;
import aima.search.framework.SuccessorFunction;
import aima.search.informed.HillClimbingSearch;
import aima.search.informed.SimulatedAnnealingSearch;

import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.File;
import java.util.EnumSet;
import java.util.Scanner;

/**
 * Aquesta classe executa i prepara automàticament els experiments.
 */
public class Main {
    static int repeticions = 10; // Com diu el PDF, 10 repeticions
    static Scanner sc = new Scanner(System.in);
    static final String DIR_CSV = "Experiments/"; // Subcarpeta per als CSVs

    // Operadors guanyadors del Exp 1
    static final SuccessorFunction HC_GUANYADOR = new DesastresSuccessorFunctionHC(
        EnumSet.of(DesastresSuccessorFunctionHC.Operador.OP1_MOURE_EXHAUSTIU,
                   DesastresSuccessorFunctionHC.Operador.OP2_INTERCANVIAR));

    // Millors params SA segons exp3 (k=1, lambda=0.01 -> mitjana=2719.71)
    static final int SA_ITERS = 10000;
    static final int SA_IT_PER_TEMP = 100;
    static final int SA_K = 1;
    static final double SA_LAMBDA = 0.01;

    public static void main(String[] args) {
        // Creem la carpeta si no existeix
        File directory = new File(DIR_CSV);
        if (!directory.exists()) {
            directory.mkdirs();
        }

        System.out.println("====== INICIANT EXPERIMENTS DE DESASTRES ======");
        int resp = 1; // per defecte, ara canvia
        while (resp >= 1 && resp <= 9) {
            System.out.println("\nQuin experiment voldríes executar?");
            System.out.println("·Experiment 1: COMPARACIÓ D'OPERADORS amb HC, H1, C=5, G=100, H=1");
            System.out.println("·Experiment 2: INICIALITZACIÓ (C=5, G=100, H=1)");
            System.out.println("·Experiment 3: AJUST SIMULATED ANNEALING");
            System.out.println("·Experiment 4: HC i SA, evolució de proporcions 5:100");
            System.out.println("·Experiment 5: HC, augmentar grups en 50, augmentar centres en 5");
            System.out.println("·Experiment 6: HC, augmentar centres en 5, augmentar helicòpters en 1");
            System.out.println("·Experiment 7: HC i HEURISTICA 2");
            System.out.println("·Experiment 8: EXECUTAR TOTS ELS EXPERIMENTS I EXPORTAR A CSV (Pregunta K)");
            System.out.println("Prem qualsevol altra tecla per sortir.");

            System.out.print("\nIntrodueix el número d'experiment: ");
            resp = sc.nextInt();

            if (resp == 1) experiment1(false);
            else if (resp == 2) experiment2(false);
            else if (resp == 3) experiment3(false);
            else if (resp == 4) experiment4(false);
            else if (resp == 5) experiment5(false);
            else if (resp == 6) experiment6(false);
            else if (resp == 7) experiment7(false);
            else if (resp == 8) executarTotsCSV();
        }
    }

    private static void executarTotsCSV() {
        System.out.print("\nQuantes repeticions (K) vols per a CADA experiment? (Recomanat: 10): ");
        repeticions = sc.nextInt();
        System.out.println("\nIniciant l'execució MASSIVA (" + repeticions + " repeticions per experiment)...");
        System.out.println("Es generaran fitxers .csv a la carpeta " + DIR_CSV);

        experiment1(true);
        experiment2(true);
        experiment3(true);
        experiment4(true);
        experiment5(true);
        experiment6(true);
        experiment7(true);

        System.out.println("\n>>> TOTS ELS EXPERIMENTS HAN FINALITZAT I S'HAN EXPORTAT A CSV CORRECTAMENT <<<");
        // Tornem a posar a 10 per si segueix usant el menú normal
        repeticions = 10;
    }

    private static double executarHillClimbing(DesastresEstat estat, HeuristicFunction heuristica) {
        return executarHillClimbing(estat, heuristica, new DesastresSuccessorFunctionHC());
    }

    private static double executarHillClimbing(DesastresEstat estat, HeuristicFunction heuristica, SuccessorFunction successorFn) {
        try {
            Problem p = new Problem(estat, successorFn, new DesastresGoalTest(), heuristica);
            Search search = new HillClimbingSearch();
            SearchAgent agent = new SearchAgent(p, search);

            DesastresEstat estatFinal = (DesastresEstat) search.getGoalState();
            return estatFinal != null ? heuristica.getHeuristicValue(estatFinal) : heuristica.getHeuristicValue(estat);
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static double executarSimulatedAnnealing(DesastresEstat estat, HeuristicFunction heuristica, int iteracions, int itPerTemp, int k, double lambda) {
        try {
            Problem p = new Problem(estat, new DesastresSuccessorFunctionSA(), new DesastresGoalTest(), heuristica);
            Search search = new SimulatedAnnealingSearch(iteracions, itPerTemp, k, lambda);
            SearchAgent agent = new SearchAgent(p, search);

            DesastresEstat estatFinal = (DesastresEstat) search.getGoalState();
            return estatFinal != null ? heuristica.getHeuristicValue(estatFinal) : heuristica.getHeuristicValue(estat);
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static double mean(double[] arr) {
        double sum = 0;
        for (double v : arr) sum += v;
        return sum / arr.length;
    }

    private static double stddev(double[] arr) {
        double m = mean(arr);
        double sum = 0;
        for (double v : arr) sum += (v - m) * (v - m);
        return Math.sqrt(sum / arr.length);
    }

    private static void experiment1(boolean exportCSV) {
        System.out.println("\n--- EXPERIMENT 1: COMPARACIÓ D'OPERADORS (HC, H1, C=5, G=100, H=1) ---");
        try {
            PrintWriter pw = null;
            if (exportCSV) {
                pw = new PrintWriter(new FileWriter(DIR_CSV + "exp1_operadors.csv"));
                pw.println("Combinacio,Iteracio,Cost,Temps_ms");
            }

            int C = 5, G = 100, H = 1;
            HeuristicFunction heuristica = new DesastresHeuristicFunction1();

            String[] noms = {
                    "A: Op1+Op2 (exhaustiu)",
                    "B: Op3+Op4 (intel·ligent, K=3)",
                    "C: Op1 sol",
                    "D: Op3 sol (K=3)",
                    "E: Op1+Op2+Op3+Op4 (tots, K=3)"
            };

            SuccessorFunction[] successors = {
                    new DesastresSuccessorFunctionHC(
                            EnumSet.of(DesastresSuccessorFunctionHC.Operador.OP1_MOURE_EXHAUSTIU,
                                    DesastresSuccessorFunctionHC.Operador.OP2_INTERCANVIAR)),
                    new DesastresSuccessorFunctionHC(
                            EnumSet.of(DesastresSuccessorFunctionHC.Operador.OP3_MOURE_K_NEAREST,
                                    DesastresSuccessorFunctionHC.Operador.OP4_ALLEUJAR_PITJOR)),
                    new DesastresSuccessorFunctionHC(
                            EnumSet.of(DesastresSuccessorFunctionHC.Operador.OP1_MOURE_EXHAUSTIU)),
                    new DesastresSuccessorFunctionHC(
                            EnumSet.of(DesastresSuccessorFunctionHC.Operador.OP3_MOURE_K_NEAREST)),
                    new DesastresSuccessorFunctionHC(
                            EnumSet.allOf(DesastresSuccessorFunctionHC.Operador.class))
            };

            for (int s = 0; s < noms.length; s++) {
                double[] costos = new double[repeticions];
                double[] temps = new double[repeticions];

                for (int i = 0; i < repeticions; i++) {
                    DesastresEstat estat = new DesastresEstat(C, G, H, i, DesastresEstat.EstrategiaInicial.CENTRE_MES_PROPER);
                    long t0 = System.currentTimeMillis();
                    costos[i] = executarHillClimbing(estat, heuristica, successors[s]);
                    temps[i] = System.currentTimeMillis() - t0;

                    if (pw != null) {
                        pw.printf(java.util.Locale.US, "%s,%d,%.2f,%.1f\n", noms[s].replace(" ", "_"), i, costos[i], temps[i]);
                    }
                }

                System.out.println("\nCombinació " + noms[s] + ":");
                System.out.printf("  Cost:  %.2f ± %.2f\n", mean(costos), stddev(costos));
                System.out.printf("  Temps: %.1f ± %.1f ms\n", mean(temps), stddev(temps));
            }
            if (pw != null) pw.close();
        } catch (Exception e) { e.printStackTrace(); }
    }

    private static void experiment2(boolean exportCSV) {
        System.out.println("\n--- EXPERIMENT 2: INICIALITZACIÓ (C=5, G=100, H=1) ---");
        try {
            PrintWriter pw = null;
            if (exportCSV) {
                pw = new PrintWriter(new FileWriter(DIR_CSV + "exp2_inicialitzacio.csv"));
                pw.println("Estrategia,Iteracio,Cost,Temps_ms");
            }

            double sumaAleatori = 0, sumaGreedy = 0;
            double tempsCpuAleatori = 0, tempsCpuGreedy = 0;

            for (int i = 0; i < repeticions; i++) {
                // Test 1: Aleatori
                long timeStart = System.currentTimeMillis();
                DesastresEstat estAleat = new DesastresEstat(5, 100, 1, i, DesastresEstat.EstrategiaInicial.ALEATORI);
                double costAleat = executarHillClimbing(estAleat, new DesastresHeuristicFunction1(), HC_GUANYADOR);
                long tAleat = System.currentTimeMillis() - timeStart;
                tempsCpuAleatori += tAleat;
                sumaAleatori += costAleat;

                if (pw != null) pw.printf(java.util.Locale.US, "Aleatori,%d,%.2f,%d\n", i, costAleat, tAleat);

                // Test 2: greedy (centre mes proper)
                timeStart = System.currentTimeMillis();
                DesastresEstat estGreedy = new DesastresEstat(5, 100, 1, i, DesastresEstat.EstrategiaInicial.CENTRE_MES_PROPER);
                double costGreedy = executarHillClimbing(estGreedy, new DesastresHeuristicFunction1(), HC_GUANYADOR);
                long tGreedy = System.currentTimeMillis() - timeStart;
                tempsCpuGreedy += tGreedy;
                sumaGreedy += costGreedy;

                if (pw != null) pw.printf(java.util.Locale.US, "CentreMesProper,%d,%.2f,%d\n", i, costGreedy, tGreedy);
            }

            System.out.println("Estratègia ALEATORI:");
            System.out.println("  -> Cost Mitjà: " + (sumaAleatori / repeticions) + " minuts");
            System.out.println("  -> Temps CPU Mitjà: " + (tempsCpuAleatori / repeticions) + " ms");

            System.out.println("Estratègia CENTRE MÉS PROPER:");
            System.out.println("  -> Cost Mitjà: " + (sumaGreedy / repeticions) + " minuts");
            System.out.println("  -> Temps CPU Mitjà: " + (tempsCpuGreedy / repeticions) + " ms");

            if (pw != null) {
                pw.close();
            }
        } catch (Exception e) { e.printStackTrace(); }
    }

    private static void experiment3(boolean exportCSV) {
        System.out.println("\n--- EXPERIMENT 3: AJUST SIMULATED ANNEALING ---");
        System.out.println("Cerca exhaustiva de paràmetres k i lambda");
        try {
            PrintWriter pw = null;
            if (exportCSV) {
                pw = new PrintWriter(new FileWriter(DIR_CSV + "exp3_simulated_annealing.csv"));
                pw.println("k,lambda,Iteracio,CostMitja_minuts,TempsCPU_ms");
            }

            int[] ks = {1, 5, 25, 125};
            double[] lambdas = {0.1, 0.01, 0.001, 0.0001};

            for (int k : ks) {
                for (double lambda : lambdas) {
                    double sumaSA = 0;
                    double tempsCpuSA = 0;
                    for (int i = 0; i < repeticions; i++) {
                        long timeStart = System.currentTimeMillis();
                        DesastresEstat estSA = new DesastresEstat(5, 100, 1, i, DesastresEstat.EstrategiaInicial.CENTRE_MES_PROPER);
                        // Executem SA amb 10000 iteracions totals per avaluar el comportament
                        double costSA = executarSimulatedAnnealing(estSA, new DesastresHeuristicFunction1(), 10000, 100, k, lambda);
                        long tSA = System.currentTimeMillis() - timeStart;
                        tempsCpuSA += tSA;
                        sumaSA += costSA;

                        if (pw != null) {
                            pw.printf(java.util.Locale.US, "%d,%.4f,%d,%.2f,%d\n", k, lambda, i, costSA, tSA);
                        }
                    }
                    System.out.printf("k = %d, lambda = %.4f -> costMitja(minuts): %.2f | tempsCPU(ms): %.2f\n", k, lambda, (sumaSA / repeticions), (tempsCpuSA / repeticions));
                }
            }
            if (pw != null) pw.close();
        } catch (Exception e) { e.printStackTrace(); }
    }

    private static void experiment4(boolean exportCSV) {
        System.out.println("\n--- EXPERIMENT 4: HC i SA, evolució de proporcions 5:100 ---");
        try {
            PrintWriter pw = null;
            if (exportCSV) {
                pw = new PrintWriter(new FileWriter(DIR_CSV + "exp4_escalabilitat.csv"));
                pw.println("Centres,Grups,Algorisme,Iteracio,Cost,TempsCPU_ms");
            }

            int centresE4 = 5;
            int grupsE4 = 100;
            int factors = 4;

            for (int step = 0; step < factors; step++) {
                double sumaHC_E4 = 0, sumaSA_E4 = 0;
                double tempsCpuHC_E4 = 0, tempsCpuSA_E4 = 0;

                System.out.println("\nProvant mida: " + centresE4 + " centres i " + grupsE4 + " grups");

                for (int i = 0; i < repeticions; i++) {
                    // HC
                    long timeStart = System.currentTimeMillis();
                    DesastresEstat HC_E4 = new DesastresEstat(centresE4, grupsE4, 1, i, DesastresEstat.EstrategiaInicial.CENTRE_MES_PROPER);
                    double costHC_E4 = executarHillClimbing(HC_E4, new DesastresHeuristicFunction1(), HC_GUANYADOR);
                    long tHC = System.currentTimeMillis() - timeStart;
                    tempsCpuHC_E4 += tHC;
                    sumaHC_E4 += costHC_E4;
                    if (pw != null) pw.printf(java.util.Locale.US, "%d,%d,HillClimbing,%d,%.2f,%d\n", centresE4, grupsE4, i, costHC_E4, tHC);

                    // SA
                    timeStart = System.currentTimeMillis();
                    DesastresEstat SA_E4 = new DesastresEstat(centresE4, grupsE4, 1, i, DesastresEstat.EstrategiaInicial.CENTRE_MES_PROPER);
                    double costSA_E4 = executarSimulatedAnnealing(SA_E4, new DesastresHeuristicFunction1(), SA_ITERS, SA_IT_PER_TEMP, SA_K, SA_LAMBDA);
                    long tSA = System.currentTimeMillis() - timeStart;
                    tempsCpuSA_E4 += tSA;
                    sumaSA_E4 += costSA_E4;
                    if (pw != null) pw.printf(java.util.Locale.US, "%d,%d,SimulatedAnnealing,%d,%.2f,%d\n", centresE4, grupsE4, i, costSA_E4, tSA);
                }

                System.out.println("  Hill Climbing:");
                System.out.println("    -> Cost Mitjà: " + (sumaHC_E4 / repeticions) + " minuts");
                System.out.println("    -> Temps CPU Mitjà: " + (tempsCpuHC_E4 / repeticions) + " ms");

                System.out.println("  Simulated Annealing:");
                System.out.println("    -> Cost Mitjà: " + (sumaSA_E4 / repeticions) + " minuts");
                System.out.println("    -> Temps CPU Mitjà: " + (tempsCpuSA_E4 / repeticions) + " ms");

                centresE4 += 5;
                grupsE4 += 100;
            }
            if (pw != null) pw.close();
        } catch (Exception e) { e.printStackTrace(); }
    }

    private static void experiment5(boolean exportCSV) {
        System.out.println("\n--- EXPERIMENT 5: NOMÉS HC I 2 ESCENARIS ---");
        try {
            PrintWriter pw1 = null;
            PrintWriter pw2 = null;
            if (exportCSV) {
                pw1 = new PrintWriter(new FileWriter(DIR_CSV + "exp5_augment_grups.csv"));
                pw1.println("Centres,Grups,Iteracio,Cost,Temps_ms");
                pw2 = new PrintWriter(new FileWriter(DIR_CSV + "exp5_augment_centres.csv"));
                pw2.println("Centres,Grups,Iteracio,Cost,Temps_ms");
            }

            System.out.println("\n -> ESCENARI 1: AUGMENTAR GRUPS DE 50 EN 50");
            int centresE5 = 5, grupsE5 = 100, finsTendencia1 = 15;
            double suma = 0.0, tempsCPU = 0.0;
            for (int i = 0; i < finsTendencia1; i++) {
                suma = 0.0; tempsCPU = 0.0;
                System.out.print("    Provant amb " + centresE5 + " centres i "+ grupsE5 + " grups.");
                for (int j = 0; j < repeticions; j++) {
                    long timeStart = System.currentTimeMillis();
                    DesastresEstat HC_E5 = new DesastresEstat(centresE5, grupsE5, 1, j, DesastresEstat.EstrategiaInicial.CENTRE_MES_PROPER);
                    double costHC_E5 = executarHillClimbing(HC_E5, new DesastresHeuristicFunction1());
                    long t = System.currentTimeMillis() - timeStart;
                    tempsCPU += t;
                    suma += costHC_E5;
                    if (pw1 != null) pw1.printf(java.util.Locale.US, "%d,%d,%d,%.2f,%d\n", centresE5, grupsE5, j, costHC_E5, t);
                }
                System.out.println(" Temps mitjà = " + tempsCPU / repeticions + "ms");
                grupsE5 += 50;
            }

            centresE5 = 5; grupsE5 = 100;
            suma = 0.0; tempsCPU = 0.0;
            int finsTendencia2 = 30;
            System.out.println("\n -> ESCENARI 2: AUGMENTAR CENTRES DE 5 EN 5");
            for (int i = 0; i < finsTendencia2; i++) {
                suma = 0.0; tempsCPU = 0.0;
                System.out.print("    Provant amb " + centresE5 + " centres i "+ grupsE5 + " grups.");
                for (int j = 0; j < repeticions; j++) {
                    long timeStart = System.currentTimeMillis();
                    DesastresEstat HC_E5 = new DesastresEstat(centresE5, grupsE5, 1, j, DesastresEstat.EstrategiaInicial.CENTRE_MES_PROPER);
                    double costHC_E5 = executarHillClimbing(HC_E5, new DesastresHeuristicFunction1());
                    long t = System.currentTimeMillis() - timeStart;
                    tempsCPU += t;
                    suma += costHC_E5;
                    if (pw2 != null) pw2.printf(java.util.Locale.US, "%d,%d,%d,%.2f,%d\n", centresE5, grupsE5, j, costHC_E5, t);
                }
                System.out.println(" Temps mitjà = " + tempsCPU / repeticions + "ms");
                centresE5 += 5;
            }
            if (pw1 != null) pw1.close();
            if (pw2 != null) pw2.close();
        } catch (Exception e) { e.printStackTrace(); }
    }

    private static void experiment6(boolean exportCSV) {
        System.out.println("\n--- EXPERIMENT 6: CENTRES VS HELICÒPTERS ---");
        try {
            PrintWriter pw1 = null;
            PrintWriter pw2 = null;
            if (exportCSV) {
                pw1 = new PrintWriter(new FileWriter(DIR_CSV + "exp6_augment_centres.csv"));
                pw1.println("Centres,Iteracio,CostMitja_minuts,TempsCPU_ms");
                pw2 = new PrintWriter(new FileWriter(DIR_CSV + "exp6_augment_helicopters.csv"));
                pw2.println("Helicopters,Iteracio,CostMitja_minuts,TempsCPU_ms");
            }

            System.out.println("\n -> Escenari 6.1: Augmentar centres (H=1, G=100)");

            for (int c = 5; c <= 25; c += 5) {
                double sumaHC = 0, tempsCpuHC = 0;
                for (int i = 0; i < repeticions; i++) {
                    long t0 = System.currentTimeMillis();
                    DesastresEstat estat = new DesastresEstat(c, 100, 1, i, DesastresEstat.EstrategiaInicial.CENTRE_MES_PROPER);
                    double cost = executarHillClimbing(estat, new DesastresHeuristicFunction1());
                    long t = System.currentTimeMillis() - t0;
                    sumaHC += cost;
                    tempsCpuHC += t;
                    if (pw1 != null) pw1.printf(java.util.Locale.US, "%d,%d,%.2f,%d\n", c, i, cost, t);
                }
                System.out.printf("Centres = %d -> costMitja(minuts): %.2f | tempsCPU(ms): %.2f\n", c, (sumaHC / repeticions), (tempsCpuHC / repeticions));
            }

            System.out.println("\n -> Escenari 6.2: Augmentar helicòpters per centre (C=5, G=100)");

            for (int h = 1; h <= 5; h++) {
                double sumaHC = 0, tempsCpuHC = 0;
                for (int i = 0; i < repeticions; i++) {
                    long t0 = System.currentTimeMillis();
                    DesastresEstat estat = new DesastresEstat(5, 100, h, i, DesastresEstat.EstrategiaInicial.CENTRE_MES_PROPER);
                    double cost = executarHillClimbing(estat, new DesastresHeuristicFunction1());
                    long t = System.currentTimeMillis() - t0;
                    sumaHC += cost;
                    tempsCpuHC += t;
                    if (pw2 != null) pw2.printf(java.util.Locale.US, "%d,%d,%.2f,%d\n", h, i, cost, t);
                }
                System.out.printf("Helicopters = %d -> costMitja(minuts): %.2f | tempsCPU(ms): %.2f\n", h, (sumaHC / repeticions), (tempsCpuHC / repeticions));
            }
            if (pw1 != null) pw1.close();
            if (pw2 != null) pw2.close();
        } catch (Exception e) { e.printStackTrace(); }
    }

    private static void experiment7(boolean exportCSV) {
        System.out.println("\n--- EXPERIMENT 7: HEURISTICA 2 (Comparació pesos) ---");
        try {
            PrintWriter pw = null;
            if (exportCSV) {
                pw = new PrintWriter(new FileWriter(DIR_CSV + "exp7_heuristica2.csv"));
                pw.println("PesAlpha,Algorisme,Iteracio,CostTotal_H2");
            }

            // Anirem doblant el pes de la penalització com diu l'enunciat
            double[] pesos = {0.0, 0.5, 1.0, 2.0, 4.0, 8.0, 16.0, 32.0};

            System.out.println("\nRESULTATS HILL CLIMBING:");
            for (double pes : pesos) {
                double sumH2 = 0;
                for (int i = 0; i < repeticions; i++) {
                    DesastresEstat estat = new DesastresEstat(5, 100, 1, i, DesastresEstat.EstrategiaInicial.CENTRE_MES_PROPER);
                    DesastresHeuristicFunction2 h2 = new DesastresHeuristicFunction2(pes);
                    double cost = executarHillClimbing(estat, h2);
                    sumH2 += cost;
                    if (pw != null) pw.printf(java.util.Locale.US, "%.1f,HillClimbing,%d,%.2f\n", pes, i, cost);
                }
                System.out.printf("Pes = %.1f -> costHeuristica_H2: %.2f\n", pes, sumH2 / repeticions);
            }

            System.out.println("\nRESULTATS SIMULATED ANNEALING (Amb k=" + SA_K + ", lambda=" + SA_LAMBDA + "):");
            for (double pes : pesos) {
                double sumH2 = 0;
                for (int i = 0; i < repeticions; i++) {
                    DesastresEstat estat = new DesastresEstat(5, 100, 1, i, DesastresEstat.EstrategiaInicial.CENTRE_MES_PROPER);
                    DesastresHeuristicFunction2 h2 = new DesastresHeuristicFunction2(pes);
                    double cost = executarSimulatedAnnealing(estat, h2, SA_ITERS, SA_IT_PER_TEMP, SA_K, SA_LAMBDA);
                    sumH2 += cost;
                    if (pw != null) pw.printf(java.util.Locale.US, "%.1f,SimulatedAnnealing,%d,%.2f\n", pes, i, cost);
                }
                System.out.printf("Pes = %.1f -> costHeuristica_H2: %.2f\n", pes, sumH2 / repeticions);
            }
            if (pw != null) pw.close();
        } catch (Exception e) { e.printStackTrace(); }
    }
}