package desastres;

import IA.Desastres.Centro;
import IA.Desastres.Centros;
import IA.Desastres.Grupo;
import IA.Desastres.Grupos;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Random;

/**
 * Aquesta classe representa un estat concret dins de l'espai de cerca.
 * Defineix quins grups de rescat estan assignats a quins centres.
 */
public class DesastresEstat {

    // Estratègies per generar la solució inicial.
    public enum EstrategiaInicial {
        // Assignació aleatòria de cada grup a un centre.
        ALEATORI,
        // Assignació vorac: cada grup al centre més proper (distància euclidiana).
        CENTRE_MES_PROPER
    }

    // Dades estàtiques (no canvien durant la cerca, són les dades del problema)
    private static Centros centres;
    private static Grupos grups;
    private static int H_helicopters;

    // L'estat és un array de Llistes. Cada centre té una llista de grups ordenats.
    private ArrayList<Integer>[] grupsPerCentre;

    // Variables per no recalcular l'heurística contínuament
    private boolean calculat = false;
    private double tempsTotal = 0.0;
    private double maxTempsP1 = 0.0;

    /**
     * Constructor per generar l'estat inicial (usa estratègia aleatòria per defecte).
     * @param numCentres Nombre de centres a generar per la simulació.
     * @param numGrups Nombre de grups a generar per la simulació.
     * @param H_helicopters Nombre d'helicopters que hi haurà per centre.
     * @param seed Llavor per a la generació aleatòria (per poder repetir experiments).
     */
    public DesastresEstat(int numCentres, int numGrups, int H_helicopters, int seed) {
        this(numCentres, numGrups, H_helicopters, seed, EstrategiaInicial.ALEATORI);
    }

    /**
     * Constructor per generar l'estat inicial amb l'estratègia escollida.
     * @param numCentres Nombre de centres a generar per la simulació.
     * @param numGrups Nombre de grups a generar per la simulació.
     * @param H_helicopters Nombre d'helicopters que hi haurà per centre.
     * @param seed Llavor per a la generació aleatòria (per poder repetir experiments).
     * @param estrategia Estratègia per generar la solució inicial (ALEATORI o CENTRE_MES_PROPER).
     */
    public DesastresEstat(int numCentres, int numGrups, int H_helicopters, int seed, EstrategiaInicial estrategia) {
        centres = new Centros(numCentres, H_helicopters, seed);
        grups = new Grupos(numGrups, seed);
        DesastresEstat.H_helicopters = H_helicopters;

        grupsPerCentre = new ArrayList[numCentres];
        for (int i = 0; i < numCentres; i++) {
            grupsPerCentre[i] = new ArrayList<>();
        }

        switch (estrategia) {
            case ALEATORI:
                generarEstatInicialAleatori(seed);
                break;
            case CENTRE_MES_PROPER:
                generarEstatInicialCentreMesProper();
                break;
            default:
                generarEstatInicialAleatori(seed);
        }
        calcularMetriques();
    }

    /**
     * Constructor de còpia.
     * Quan l'algorisme explora un nou estat, copiem l'actual i modifiquem la còpia.
     */
    public DesastresEstat(DesastresEstat estatOriginal) {
        // Copiem l'array d'assignacions (no podem fer assignacio = estatOriginal.assignacio
        // perquè copiariem la referència i modificaríem l'estat pare)
        this.grupsPerCentre = new ArrayList[estatOriginal.grupsPerCentre.length];
        for (int i = 0; i < estatOriginal.grupsPerCentre.length; i++) {
            this.grupsPerCentre[i] = new ArrayList<>(estatOriginal.grupsPerCentre[i]);
        }
        this.tempsTotal = estatOriginal.tempsTotal;
        this.maxTempsP1 = estatOriginal.maxTempsP1;
        this.calculat = estatOriginal.calculat;
    }

    /**
     * Mètode privat per crear una primera assignació aleatòria de grups a centres.
     * @param seed Llavor per a reproduïbilitat dels experiments.
     */
    private void generarEstatInicialAleatori(int seed) {
        Random rand = new Random(seed);
        int numCentres = centres.size();
        for (int i = 0; i < grups.size(); i++) {
            grupsPerCentre[rand.nextInt(numCentres)].add(i);
        }
    }

    /**
     * Mètode privat: assigna cada grup al centre més proper segons distància euclidiana.
     * Cost O(G·C). Sol donar una solució inicial millor que l'aleatòria.
     */
    private void generarEstatInicialCentreMesProper() {
        int nGrups = grups.size();
        int nCentres = centres.size();

        for (int g = 0; g < nGrups; g++) {
            Grupo grup = grups.get(g);
            int gx = grup.getCoordX();
            int gy = grup.getCoordY();

            int centreMesProper = 0;
            double distMin = Double.POSITIVE_INFINITY;

            for (int c = 0; c < nCentres; c++) {
                Centro centre = centres.get(c);
                int cx = centre.getCoordX();
                int cy = centre.getCoordY();
                double dx = gx - cx;
                double dy = gy - cy;
                double distSq = dx * dx + dy * dy;

                if (distSq < distMin) {
                    distMin = distSq;
                    centreMesProper = c;
                }
            }
            grupsPerCentre[centreMesProper].add(g);
        }
    }


    /**
     * Mètode per simular els viatges amb les restriccions del problema per calcular metrques de temps per
     * no haver de fer molts recàlculs a l'heurística.
     */
    private void calcularMetriques() {
        if (calculat) return;
        tempsTotal = 0.0;
        maxTempsP1 = 0.0;

        for (int c = 0; c < centres.size(); c++) {
            ArrayList<Integer> llistaGrups = grupsPerCentre[c];
            double[] tempsHelicopters = new double[H_helicopters]; // Temps de cada helicòpter d'aquest centre

            ArrayList<Integer> viatgeActual = new ArrayList<>();
            int personesViatge = 0;

            for (int idGrup : llistaGrups) {
                Grupo g = grups.get(idGrup);

                // Si excedeix capacitat o ja té 3 grups, tanca viatge i n'inicia un de nou
                if (personesViatge + g.getNPersonas() > 15 || viatgeActual.size() >= 3) {
                    assignarViatgeAHelicopter(viatgeActual, c, tempsHelicopters);
                    viatgeActual.clear();
                    personesViatge = 0;
                }
                viatgeActual.add(idGrup);
                personesViatge += g.getNPersonas();
            }
            // Assignar el viatge restant
            if (!viatgeActual.isEmpty()) {
                assignarViatgeAHelicopter(viatgeActual, c, tempsHelicopters);
            }

            // Sumar els temps del centre al total
            for (double t : tempsHelicopters) {
                tempsTotal += t;
            }
        }
        calculat = true;
    }

    /**
     * Mètode privat per assignar un viatge a l'helicòpter més disponible d'un centre.
     * Retorna l'índex de l'helicòpter al qual s'ha assignat el viatge.
     */
    private int assignarViatgeAHelicopter(ArrayList<Integer> viatge, int idCentre, double[] tempsHelicopters) {
        // L'helicòpter més disponible
        int hMin = 0;
        for (int h = 1; h < tempsHelicopters.length; h++) {
            if (tempsHelicopters[h] < tempsHelicopters[hMin]) hMin = h;
        }

        double tempsVol = 0.0;
        double tempsRecollida = 0.0;
        boolean tePrioritat1 = false;

        Centro centre = centres.get(idCentre);
        int xActual = centre.getCoordX();
        int yActual = centre.getCoordY();

        for (int idG : viatge) {
            Grupo g = grups.get(idG);
            double dist = Math.sqrt(Math.pow(g.getCoordX() - xActual, 2) + Math.pow(g.getCoordY() - yActual, 2));
            tempsVol += (dist / 100.0) * 60.0; // 100km/h -> dist/100 hores -> *60 minuts

            if (g.getPrioridad() == 1) {
                tempsRecollida += g.getNPersonas() * 2.0; // 2 minuts per ferit
                tePrioritat1 = true;
            } else {
                tempsRecollida += g.getNPersonas(); // 1 minut per no ferit
            }
            xActual = g.getCoordX();
            yActual = g.getCoordY();
        }

        // Tornada
        double distTornada = Math.sqrt(Math.pow(centre.getCoordX() - xActual, 2) + Math.pow(centre.getCoordY() - yActual, 2));
        tempsVol += (distTornada / 100.0) * 60.0;

        // Temps final
        double tempsFinalViatge = tempsHelicopters[hMin] + tempsVol + tempsRecollida + 10.0; // 10 min descàrrega
        tempsHelicopters[hMin] = tempsFinalViatge;

        if (tePrioritat1 && tempsFinalViatge > maxTempsP1) {
            maxTempsP1 = tempsFinalViatge;
        }

        return hMin;
    }




    // --- OPERADORS (Mètodes per modificar l'estat) ---

    /**
     * Operador: Mou un grup d'un centre a un altre.
     */
    public void moureGrup(int cOrigen, int indexOrigen, int cDesti) {
        int idGrup = grupsPerCentre[cOrigen].remove(indexOrigen);
        grupsPerCentre[cDesti].add(idGrup);
        calculat = false;
    }

     /**
     * Operador: Mou un grup d'un centre a un altre usant només el seu ID.
     */
    public void moureGrup(int idGrup, int cDesti) {
        for (int c = 0; c < grupsPerCentre.length; c++) {
            int index = grupsPerCentre[c].indexOf(idGrup);
            if (index != -1) { // Si trobem el grup en aquest centre
                grupsPerCentre[c].remove(index);
                grupsPerCentre[cDesti].add(idGrup);
                calculat = false;
                return;
            }
        }
    }

    /**
     * Operador: Intercanvia l'assignació de dos grups.
     */
    public void intercanviarGrups(int c1, int i1, int c2, int i2) {
        int grup1 = grupsPerCentre[c1].get(i1);
        int grup2 = grupsPerCentre[c2].get(i2);
        grupsPerCentre[c1].set(i1, grup2);
        grupsPerCentre[c2].set(i2, grup1);
        calculat = false;
    }

    // --- GETTERS ---
    public double getTempsTotal() {
        if (!calculat) calcularMetriques();
        return tempsTotal;
    }

    public double getMaxTempsP1() {
        if (!calculat) calcularMetriques();
        return maxTempsP1;
    }

    public int getNumCentres() { return centres.size(); }
    public int getGrupsAlCentre(int c) { return grupsPerCentre[c].size(); }

    public static Centros getCentres() {
        return centres;
    }

    public static Grupos getGrups() {
        return grups;
    }

    /**
     * Obté els K centres més propers al grup idGrup.
     */
    public List<Integer> getCentresMesPropers(int idGrup, int k) {
        Grupo grup = grups.get(idGrup);
        int gx = grup.getCoordX();
        int gy = grup.getCoordY();

        List<double[]> distancies = new ArrayList<>(); // guardem [distanciaAlQuadrat, id_centre]

        for (int c = 0; c < centres.size(); c++) {
            Centro centre = centres.get(c);
            int cx = centre.getCoordX();
            int cy = centre.getCoordY();
            
            double distSq = Math.pow(gx - cx, 2) + Math.pow(gy - cy, 2);
            distancies.add(new double[]{distSq, c});
        }

        distancies.sort(Comparator.comparingDouble(a -> a[0]));

        List<Integer> centresPropers = new ArrayList<>();
        int limit = Math.min(k, distancies.size());
        for (int i = 0; i < limit; i++) {
            centresPropers.add((int) distancies.get(i)[1]);
        }

        return centresPropers;
    }

    /**
     * Obté el centre amb més temps operatiu
     */
    public int getCentreAmbMesTemps() {
        int centreMesSaturat = -1;
        double maxTempsCentre = -1.0;

        for (int c = 0; c < centres.size(); c++) {
            ArrayList<Integer> llistaGrups = grupsPerCentre[c];
            double[] tempsHelicopters = new double[H_helicopters];

            ArrayList<Integer> viatgeActual = new ArrayList<>();
            int personesViatge = 0;

            for (int idGrup : llistaGrups) {
                Grupo g = grups.get(idGrup);
                
                if (personesViatge + g.getNPersonas() > 15 || viatgeActual.size() >= 3) {
                    assignarViatgeAHelicopter(viatgeActual, c, tempsHelicopters);
                    viatgeActual.clear();
                    personesViatge = 0;
                }
                viatgeActual.add(idGrup);
                personesViatge += g.getNPersonas();
            }
            if (!viatgeActual.isEmpty()) {
                assignarViatgeAHelicopter(viatgeActual, c, tempsHelicopters);
            }

            double tempsCentreActual = 0.0;
            for (double t : tempsHelicopters) {
                tempsCentreActual += t;
            }

            if (tempsCentreActual > maxTempsCentre) {
                maxTempsCentre = tempsCentreActual;
                centreMesSaturat = c;
            }
        }

        return centreMesSaturat;
    }

    /**
     * Retorna el centre al qual està assignat un grup concret.
     */
    public int getCentreAssignat(int idGrup) {
        for (int c = 0; c < grupsPerCentre.length; c++) {
            if (grupsPerCentre[c].contains(idGrup)) {
                return c;
            }
        }
        return -1; //en teoria mai hauria de passar
    }

    // Mètode útil per debugar i veure com està l'estat
    /**
     * Genera el pla de rescat detallat per a la solució final.
     */
    public String obtenirPlaRescat() {
        StringBuilder sb = new StringBuilder();
        sb.append("PLA DE RESCAT FINAL:\n");

        for (int c = 0; c < centres.size(); c++) {
            sb.append("CENTRE ").append(c).append(":\n");
            ArrayList<Integer> llistaGrups = grupsPerCentre[c];
            double[] tempsHelicopters = new double[H_helicopters];

            // Guardem els viatges de cada helicòpter d'aquest centre
            ArrayList<ArrayList<ArrayList<Integer>>> rutesH = new ArrayList<>();
            for(int h = 0; h < H_helicopters; h++) rutesH.add(new ArrayList<>());

            ArrayList<Integer> viatgeActual = new ArrayList<>();
            int personesViatge = 0;

            for (int idGrup : llistaGrups) {
                Grupo g = grups.get(idGrup);
                if (personesViatge + g.getNPersonas() > 15 || viatgeActual.size() >= 3) {
                    int hAssignat = assignarViatgeAHelicopter(viatgeActual, c, tempsHelicopters);
                    rutesH.get(hAssignat).add(new ArrayList<>(viatgeActual));
                    viatgeActual.clear();
                    personesViatge = 0;
                }
                viatgeActual.add(idGrup);
                personesViatge += g.getNPersonas();
            }
            if (!viatgeActual.isEmpty()) {
                int hAssignat = assignarViatgeAHelicopter(viatgeActual, c, tempsHelicopters);
                rutesH.get(hAssignat).add(new ArrayList<>(viatgeActual));
            }

            for(int h = 0; h < H_helicopters; h++) {
                sb.append("  Helicòpter ").append(h).append(" (Temps total: ").append(String.format("%.2f", tempsHelicopters[h])).append(" min):\n");
                ArrayList<ArrayList<Integer>> viatges = rutesH.get(h);
                if (viatges.isEmpty()) {
                    sb.append("    -> Sense sortides.\n");
                } else {
                    for (int v = 0; v < viatges.size(); v++) {
                        sb.append("    -> Sortida ").append(v+1).append(": Grups recollits ").append(viatges.get(v)).append("\n");
                    }
                }
            }
            sb.append("\n");
        }
        return sb.toString();
    }
}