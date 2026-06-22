;;; ============================================================================
;;; SISTEMA EXPERT DE RECOMANACIO DE VIATGES PERSONALITZATS
;;; Basat en l'ontologia "Agencia de Viatges al Fi del Mon"
;;; ============================================================================

(defmodule MAIN (export ?ALL))

;;; ----------------------------------------------------------------------------
;;; TEMPLATES
;;; ----------------------------------------------------------------------------

(deftemplate usuari
    (slot id (default u1))
    (slot ciutat-origen (type SYMBOL) (default Barcelona))
    (slot edat (type INTEGER))
    (slot tipus (type SYMBOL) (allowed-values solitari familia grupAmics grupGran parella))
    (slot nivell-cultural (type SYMBOL) (allowed-values Baix Mig Alt) (default Mig))
    (slot te-nens (type SYMBOL) (allowed-values si no) (default no))
    (slot esdeveniment-especial (type SYMBOL) (allowed-values cap boda fi-de-curs aniversari) (default cap))
    (slot objectiu (type SYMBOL) (allowed-values descans cultural diversio romantic treball))
)

(deftemplate restriccions
    (slot pressupost-max (type NUMBER))
    (slot min-dies (type INTEGER))
    (slot max-dies (type INTEGER))
    (slot min-dies-ciutat (type INTEGER))
    (slot max-dies-ciutat (type INTEGER) (default 3))
    (slot max-ciutats (type INTEGER))
    (slot min-estrelles (type INTEGER) (default 1))
    (multislot transports-prohibits (type SYMBOL))
)

(deftemplate preferencies
    (slot sacrificar-qualitat (type SYMBOL) (allowed-values si no) (default no))
    (slot sacrificar-duracio (type SYMBOL) (allowed-values si no) (default no))
    (slot llocs-poc-coneguts (type SYMBOL) (allowed-values si no) (default no))
    (slot tematica-preferida (type SYMBOL))
)

(deftemplate ciutat
    (slot nom (type SYMBOL))
    (slot pais (type SYMBOL))
    (slot regio (type SYMBOL) (allowed-values Europa SudAmerica) (default Europa))
    (slot nivell-vida (type SYMBOL) (allowed-values Baix Normal Alt))
    (slot popularitat (type SYMBOL) (allowed-values PocConegut Conegut BastantConegut DestiInusual))
    (multislot tematiques (type SYMBOL))
)

(deftemplate allotjament
    (slot ciutat (type SYMBOL))
    (slot nom (type SYMBOL))
    (slot estrelles (type INTEGER) (range 1 5))
    (slot preu-nit (type FLOAT))
)

(deftemplate lloc-interes
    (slot nom (type SYMBOL))
    (slot ciutat (type SYMBOL))
    (slot tipus (type SYMBOL) (allowed-values monument museu parc activitat))
    (slot importancia (type SYMBOL) (allowed-values PocRellevant Rellevant Indispensable))
    (slot preu (type FLOAT))
    (slot es-perillos (type SYMBOL) (allowed-values si no) (default no))
)

(deftemplate trajecte
    (slot origen (type SYMBOL))
    (slot desti (type SYMBOL))
    (slot transport (type SYMBOL) (allowed-values autobus avio cotxe tren vaixell))
    (slot preu (type FLOAT))
    (slot duracio (type FLOAT))
)

(deftemplate viatge-proposat
    (slot num-ordre (type INTEGER)) ;; Sera 1 (Top 1) o 2 (Top 2)
    (slot id-original (type INTEGER))
    (multislot ciutats-visitades (type SYMBOL))
    (multislot rutes (type SYMBOL))
    (slot preu-total (type FLOAT) (default 0.0))
    (slot duracio-total (type INTEGER) (default 0))
    (slot valid (type SYMBOL) (allowed-values si no))
    (multislot motius (type STRING))
)

(deftemplate viatge-candidat
    (slot id (type INTEGER))
    (multislot ciutats-visitades (type SYMBOL))
    (multislot rutes (type SYMBOL))
    (slot preu-total (type FLOAT) (default 0.0))
    (slot duracio-total (type INTEGER) (default 0))
    (slot valid (type SYMBOL) (allowed-values si no) (default si))
    (slot puntuacio (type INTEGER) (default 0))
    (multislot motius (type STRING))
)

(deftemplate estada
    (slot id-viatge (type INTEGER))
    (slot ciutat (type SYMBOL))
    (slot dies (type INTEGER))
    (slot allotjament (type SYMBOL))
    (multislot visites (type SYMBOL))
)

(deftemplate usuari-temp (slot atribut) (slot valor))
(deftemplate tematica-clau (slot nom) (slot prioritat (type INTEGER) (default 2)))
(deftemplate ciutat-compatible (slot nom) (slot prioritat (type INTEGER) (default 3)))
(deftemplate fase-control (slot actual))
(deftemplate pressupost-estimat (slot nivell (allowed-values Baix Mig Alt)))
(deftemplate recomanacio-mostrada)
(deftemplate avis-impossible)
(deftemplate incoherencia-detectada)
(deftemplate preferencia-complerta (slot nom) (slot descripcio))

(deftemplate cerca-allotjament (slot id-viatge) (slot ciutat) (slot min-estrelles) (slot max-estrelles))
(deftemplate limit-visites (slot id-viatge) (slot ciutat) (slot maxim))
(deftemplate tram (slot id-viatge) (slot origen) (slot desti) (slot posicio) (slot transport (default unassigned)) (slot preu (default 0.0)))
(deftemplate trams-generats (slot id-viatge))
(deftemplate estada-comptabilitzada (slot id-viatge) (slot ciutat))
(deftemplate tram-comptabilitzat (slot id-viatge) (slot posicio))

;;; ----------------------------------------------------------------------------
;;; FUNCIONS AUXILIARS
;;; ----------------------------------------------------------------------------


(deffunction llegir-valid (?missatge ?valors)
    (printout t ?missatge " (" (implode$ ?valors) "): ")
    (bind ?in (read))
    (while (not (member$ ?in ?valors)) do
        (printout t "[Error] Valor no valid. Tria entre: " (implode$ ?valors) ": ")
        (bind ?in (read)))
    ?in)

(deffunction llegir-num-positiu (?missatge)
    (printout t ?missatge " ")
    (bind ?in (read))
    (while (or (not (numberp ?in)) (<= ?in 0)) do
        (printout t "[Error] Ha de ser un numero positiu: ")
        (bind ?in (read)))
    ?in)

(deffunction llegir-enter-rang (?missatge ?min ?max)
    (printout t ?missatge " ")
    (bind ?in (read))
    (while (or (not (integerp ?in)) (< ?in ?min) (> ?in ?max)) do
        (printout t "[Error] Ha de ser un enter entre " ?min " i " ?max ": ")
        (bind ?in (read)))
    ?in)

;;; ----------------------------------------------------------------------------
;;; INSTANCIES DE LA BASE DE CONEIXEMENT
;;; ----------------------------------------------------------------------------

(deffacts dades-expertes
    ;; Ciutats
    (ciutat (nom Barcelona) (pais Espanya) (nivell-vida Alt) (popularitat BastantConegut) (tematiques CiutatsDelMediterrani Cultural Diversio))
    (ciutat (nom Roma) (pais Italia) (nivell-vida Alt) (popularitat BastantConegut) (tematiques CiutatsDelMediterrani Cultural Romantic))
    (ciutat (nom Paris) (pais Franca) (nivell-vida Alt) (popularitat BastantConegut) (tematiques GransCiutatsEuropees Cultural Romantic))
    (ciutat (nom Londres) (pais RegneUnit) (nivell-vida Alt) (popularitat BastantConegut) (tematiques GransCiutatsEuropees Cultural Diversio))
    (ciutat (nom Berlin) (pais Alemanya) (nivell-vida Normal) (popularitat BastantConegut) (tematiques GransCiutatsEuropees Cultural Diversio))
    (ciutat (nom Atenes) (pais Grecia) (nivell-vida Normal) (popularitat BastantConegut) (tematiques CiutatsDelMediterrani Cultural))
    (ciutat (nom Marsella) (pais Franca) (nivell-vida Normal) (popularitat Conegut) (tematiques CiutatsDelMediterrani))
    (ciutat (nom Venecia) (pais Italia) (nivell-vida Alt) (popularitat BastantConegut) (tematiques CiutatsDelMediterrani Romantic Cultural))
    (ciutat (nom Viena) (pais Austria) (nivell-vida Alt) (popularitat BastantConegut) (tematiques GransCiutatsEuropees Cultural Romantic))
    (ciutat (nom Amsterdam) (pais PaisosBaixos) (nivell-vida Alt) (popularitat BastantConegut) (tematiques GransCiutatsEuropees Diversio Cultural))

    (ciutat (nom Madrid) (pais Espanya) (nivell-vida Alt) (popularitat BastantConegut) (tematiques GransCiutatsEuropees Cultural Diversio))
    (ciutat (nom Praga) (pais RepublicaTxeca) (nivell-vida Normal) (popularitat BastantConegut) (tematiques GransCiutatsEuropees Cultural Romantic))
    (ciutat (nom Estambul) (pais Turquia) (nivell-vida Normal) (popularitat BastantConegut) (tematiques CiutatsDelMediterrani Cultural))
    (ciutat (nom Lisboa) (pais Portugal) (nivell-vida Normal) (popularitat Conegut) (tematiques CiutatsDelMediterrani Cultural Romantic))

    (ciutat (nom Quito) (pais Equador) (regio SudAmerica) (nivell-vida Baix) (popularitat PocConegut) (tematiques SudamericaNatural))
    (ciutat (nom Lima) (pais Peru) (regio SudAmerica) (nivell-vida Baix) (popularitat Conegut) (tematiques SudamericaNatural Cultural))
    (ciutat (nom RioDeJaneiro) (pais Brasil) (regio SudAmerica) (nivell-vida Normal) (popularitat BastantConegut) (tematiques SudamericaNatural Diversio))
    (ciutat (nom BuenosAires) (pais Argentina) (regio SudAmerica) (nivell-vida Normal) (popularitat BastantConegut) (tematiques SudamericaNatural Cultural Romantic))
    (ciutat (nom Cuzco) (pais Peru) (regio SudAmerica) (nivell-vida Baix) (popularitat PocConegut) (tematiques SudamericaNatural Cultural))
    (ciutat (nom Cartagena) (pais Colombia) (regio SudAmerica) (nivell-vida Baix) (popularitat PocConegut) (tematiques SudamericaNatural Romantic))

    ;; Allotjaments
    (allotjament (ciutat Barcelona) (nom Hotel-Arts) (estrelles 5) (preu-nit 350.0))
    (allotjament (ciutat Barcelona) (nom Hostal-Ramblas) (estrelles 2) (preu-nit 65.0))

    (allotjament (ciutat Roma) (nom Hotel-Hassler) (estrelles 5) (preu-nit 400.0))
    (allotjament (ciutat Roma) (nom Pension-Roma) (estrelles 2) (preu-nit 55.0))

    (allotjament (ciutat Paris) (nom Ritz-Paris) (estrelles 5) (preu-nit 600.0))
    (allotjament (ciutat Paris) (nom Ibis-Paris) (estrelles 3) (preu-nit 110.0))

    (allotjament (ciutat Londres) (nom The-Savoy) (estrelles 5) (preu-nit 550.0))
    (allotjament (ciutat Londres) (nom Generator-Hostel) (estrelles 2) (preu-nit 45.0))

    (allotjament (ciutat Berlin) (nom Hotel-Adlon) (estrelles 5) (preu-nit 300.0))
    (allotjament (ciutat Berlin) (nom Ibis-Berlin) (estrelles 3) (preu-nit 80.0))

    (allotjament (ciutat Atenes) (nom Grande-Bretagne) (estrelles 5) (preu-nit 250.0))
    (allotjament (ciutat Atenes) (nom Athens-Backpackers) (estrelles 2) (preu-nit 35.0))

    (allotjament (ciutat Marsella) (nom InterContinental-Marseille) (estrelles 5) (preu-nit 220.0))
    (allotjament (ciutat Marsella) (nom B-and-B-Marseille) (estrelles 2) (preu-nit 50.0))

    (allotjament (ciutat Venecia) (nom Gritti-Palace) (estrelles 5) (preu-nit 750.0))
    (allotjament (ciutat Venecia) (nom Ostello-Venezia) (estrelles 2) (preu-nit 60.0))

    (allotjament (ciutat Viena) (nom Hotel-Sacher) (estrelles 5) (preu-nit 400.0))
    (allotjament (ciutat Viena) (nom Motel-One-Wien) (estrelles 3) (preu-nit 95.0))

    (allotjament (ciutat Amsterdam) (nom Waldorf-Astoria) (estrelles 5) (preu-nit 500.0))
    (allotjament (ciutat Amsterdam) (nom Stayokay-Hostel) (estrelles 2) (preu-nit 50.0))

    (allotjament (ciutat Quito) (nom Casa-Gangotena) (estrelles 5) (preu-nit 180.0))
    (allotjament (ciutat Quito) (nom Hostal-Centro-Quito) (estrelles 2) (preu-nit 25.0))

    (allotjament (ciutat Lima) (nom Miraflores-Park) (estrelles 5) (preu-nit 200.0))
    (allotjament (ciutat Lima) (nom Pariwana-Hostel) (estrelles 2) (preu-nit 20.0))

    (allotjament (ciutat RioDeJaneiro) (nom Copacabana-Palace) (estrelles 5) (preu-nit 350.0))
    (allotjament (ciutat RioDeJaneiro) (nom Ipanema-Beach-Hostel) (estrelles 2) (preu-nit 30.0))

    (allotjament (ciutat BuenosAires) (nom Alvear-Palace) (estrelles 5) (preu-nit 280.0))
    (allotjament (ciutat BuenosAires) (nom Milhouse-Hostel) (estrelles 2) (preu-nit 22.0))

    (allotjament (ciutat Madrid) (nom Hotel-Ritz-Madrid) (estrelles 5) (preu-nit 380.0))
    (allotjament (ciutat Madrid) (nom Hostal-Gran-Via) (estrelles 2) (preu-nit 55.0))

    (allotjament (ciutat Praga) (nom Hotel-Pariz) (estrelles 5) (preu-nit 260.0))
    (allotjament (ciutat Praga) (nom Hostel-Sokolska) (estrelles 2) (preu-nit 30.0))

    (allotjament (ciutat Estambul) (nom Pera-Palace) (estrelles 5) (preu-nit 220.0))
    (allotjament (ciutat Estambul) (nom Cheers-Hostel) (estrelles 2) (preu-nit 25.0))

    (allotjament (ciutat Lisboa) (nom Hotel-Avenida) (estrelles 5) (preu-nit 240.0))
    (allotjament (ciutat Lisboa) (nom Lisboa-Central-Hostel) (estrelles 2) (preu-nit 35.0))

    (allotjament (ciutat Cuzco) (nom Belmond-Monasterio) (estrelles 5) (preu-nit 320.0))
    (allotjament (ciutat Cuzco) (nom Pariwana-Cuzco) (estrelles 2) (preu-nit 18.0))

    (allotjament (ciutat Cartagena) (nom Hotel-Charleston) (estrelles 5) (preu-nit 240.0))
    (allotjament (ciutat Cartagena) (nom Hostal-Getsemani) (estrelles 2) (preu-nit 28.0))

    ;; Llocs d'interes
    (lloc-interes (nom SagradaFamilia) (ciutat Barcelona) (tipus monument) (importancia Indispensable) (preu 26.0))
    (lloc-interes (nom ParcGuell) (ciutat Barcelona) (tipus parc) (importancia Rellevant) (preu 10.0))

    (lloc-interes (nom Coliseu) (ciutat Roma) (tipus monument) (importancia Indispensable) (preu 18.0))
    (lloc-interes (nom MuseusVaticans) (ciutat Roma) (tipus museu) (importancia Indispensable) (preu 22.0))

    (lloc-interes (nom Louvre) (ciutat Paris) (tipus museu) (importancia Indispensable) (preu 22.0))
    (lloc-interes (nom TorreEiffel) (ciutat Paris) (tipus monument) (importancia Indispensable) (preu 28.0))

    (lloc-interes (nom BritishMuseum) (ciutat Londres) (tipus museu) (importancia Indispensable) (preu 0.0))
    (lloc-interes (nom LondonEye) (ciutat Londres) (tipus activitat) (importancia Rellevant) (preu 35.0))

    (lloc-interes (nom PortaBrandenburg) (ciutat Berlin) (tipus monument) (importancia Indispensable) (preu 0.0))
    (lloc-interes (nom IllaDelsMuseus) (ciutat Berlin) (tipus museu) (importancia Rellevant) (preu 19.0))

    (lloc-interes (nom Acropolis) (ciutat Atenes) (tipus monument) (importancia Indispensable) (preu 20.0))
    (lloc-interes (nom PortVell) (ciutat Marsella) (tipus activitat) (importancia Rellevant) (preu 0.0))
    (lloc-interes (nom BasilicaSanMarco) (ciutat Venecia) (tipus monument) (importancia Indispensable) (preu 3.0))
    (lloc-interes (nom PalauSchonbrunn) (ciutat Viena) (tipus monument) (importancia Indispensable) (preu 24.0))
    (lloc-interes (nom MuseuVanGogh) (ciutat Amsterdam) (tipus museu) (importancia Indispensable) (preu 22.0))

    (lloc-interes (nom MitadDelMundo) (ciutat Quito) (tipus monument) (importancia Rellevant) (preu 5.0))
    (lloc-interes (nom CentreHistoricLima) (ciutat Lima) (tipus monument) (importancia Indispensable) (preu 0.0))
    (lloc-interes (nom CristRedemptor) (ciutat RioDeJaneiro) (tipus monument) (importancia Indispensable) (preu 25.0))
    (lloc-interes (nom FavelasTour) (ciutat RioDeJaneiro) (tipus activitat) (importancia Rellevant) (preu 30.0) (es-perillos si))
    (lloc-interes (nom TeatreColon) (ciutat BuenosAires) (tipus monument) (importancia Indispensable) (preu 15.0))

    (lloc-interes (nom MuseuPrado) (ciutat Madrid) (tipus museu) (importancia Indispensable) (preu 15.0))
    (lloc-interes (nom PlaçaMajor) (ciutat Madrid) (tipus monument) (importancia Rellevant) (preu 0.0))
    (lloc-interes (nom ParcReina) (ciutat Madrid) (tipus parc) (importancia Rellevant) (preu 0.0))

    (lloc-interes (nom CastellPraga) (ciutat Praga) (tipus monument) (importancia Indispensable) (preu 14.0))
    (lloc-interes (nom PontCarles) (ciutat Praga) (tipus monument) (importancia Rellevant) (preu 0.0))

    (lloc-interes (nom SantaSofia) (ciutat Estambul) (tipus monument) (importancia Indispensable) (preu 12.0))
    (lloc-interes (nom GranBasarEstambul) (ciutat Estambul) (tipus activitat) (importancia Rellevant) (preu 0.0))

    (lloc-interes (nom TorreBelem) (ciutat Lisboa) (tipus monument) (importancia Indispensable) (preu 8.0))
    (lloc-interes (nom BarriAlfama) (ciutat Lisboa) (tipus activitat) (importancia Rellevant) (preu 0.0))

    (lloc-interes (nom MachuPicchu) (ciutat Cuzco) (tipus monument) (importancia Indispensable) (preu 50.0))
    (lloc-interes (nom ValleSagrado) (ciutat Cuzco) (tipus activitat) (importancia Rellevant) (preu 30.0))

    (lloc-interes (nom CiutatEmmurallada) (ciutat Cartagena) (tipus monument) (importancia Indispensable) (preu 0.0))
    (lloc-interes (nom IllesRosario) (ciutat Cartagena) (tipus activitat) (importancia Rellevant) (preu 40.0))

    ;; Trajectes - Europa (avio)
    (trajecte (origen Barcelona) (desti Paris) (transport avio) (preu 80.0) (duracio 2.0))
    (trajecte (origen Barcelona) (desti Roma) (transport avio) (preu 60.0) (duracio 1.5))
    (trajecte (origen Barcelona) (desti Amsterdam) (transport avio) (preu 95.0) (duracio 2.5))
    (trajecte (origen Paris) (desti Berlin) (transport avio) (preu 110.0) (duracio 1.5))
    (trajecte (origen Roma) (desti Atenes) (transport avio) (preu 70.0) (duracio 2.0))
    (trajecte (origen Londres) (desti Amsterdam) (transport avio) (preu 65.0) (duracio 1.2))
    (trajecte (origen Viena) (desti Roma) (transport avio) (preu 120.0) (duracio 2.0))
    (trajecte (origen Atenes) (desti Berlin) (transport avio) (preu 140.0) (duracio 2.5))

    ;; Trajectes - Europa (tren)
    (trajecte (origen Paris) (desti Londres) (transport tren) (preu 120.0) (duracio 2.5))
    (trajecte (origen Roma) (desti Venecia) (transport tren) (preu 50.0) (duracio 4.0))
    (trajecte (origen Venecia) (desti Viena) (transport tren) (preu 85.0) (duracio 7.5))
    (trajecte (origen Viena) (desti Berlin) (transport tren) (preu 90.0) (duracio 8.0))
    (trajecte (origen Berlin) (desti Amsterdam) (transport tren) (preu 75.0) (duracio 6.5))
    (trajecte (origen Paris) (desti Amsterdam) (transport tren) (preu 100.0) (duracio 3.5))
    (trajecte (origen Marsella) (desti Paris) (transport tren) (preu 90.0) (duracio 3.5))
    (trajecte (origen Roma) (desti Paris) (transport tren) (preu 150.0) (duracio 11.0))

    ;; Trajectes - Europa (cotxe / autobus)
    (trajecte (origen Barcelona) (desti Marsella) (transport cotxe) (preu 50.0) (duracio 4.0))
    (trajecte (origen Barcelona) (desti Marsella) (transport autobus) (preu 35.0) (duracio 7.0))
    (trajecte (origen Marsella) (desti Venecia) (transport autobus) (preu 60.0) (duracio 14.0))
    (trajecte (origen Berlin) (desti Viena) (transport autobus) (preu 45.0) (duracio 10.0))

    ;; Trajectes - Europa (vaixell, rutes mediterranies)
    (trajecte (origen Marsella) (desti Roma) (transport vaixell) (preu 130.0) (duracio 22.0))
    (trajecte (origen Venecia) (desti Atenes) (transport vaixell) (preu 180.0) (duracio 30.0))
    (trajecte (origen Barcelona) (desti Roma) (transport vaixell) (preu 110.0) (duracio 20.0))

    ;; Trajectes - intercontinentals (avio)
    (trajecte (origen Barcelona) (desti BuenosAires) (transport avio) (preu 850.0) (duracio 13.0))
    (trajecte (origen Roma) (desti RioDeJaneiro) (transport avio) (preu 900.0) (duracio 12.0))
    (trajecte (origen Paris) (desti Lima) (transport avio) (preu 950.0) (duracio 13.5))

    ;; Trajectes - Sud-Amèrica
    (trajecte (origen BuenosAires) (desti RioDeJaneiro) (transport avio) (preu 200.0) (duracio 3.0))
    (trajecte (origen BuenosAires) (desti RioDeJaneiro) (transport autobus) (preu 90.0) (duracio 36.0))
    (trajecte (origen Lima) (desti Quito) (transport avio) (preu 150.0) (duracio 2.5))
    (trajecte (origen Lima) (desti Quito) (transport autobus) (preu 40.0) (duracio 22.0))
    (trajecte (origen BuenosAires) (desti Lima) (transport avio) (preu 300.0) (duracio 5.0))
    (trajecte (origen Lima) (desti RioDeJaneiro) (transport avio) (preu 450.0) (duracio 7.0))
    (trajecte (origen RioDeJaneiro) (desti Quito) (transport avio) (preu 500.0) (duracio 8.0))

    ;; Trajectes - noves ciutats Europa
    (trajecte (origen Barcelona) (desti Madrid) (transport tren) (preu 70.0) (duracio 3.0))
    (trajecte (origen Madrid) (desti Lisboa) (transport tren) (preu 60.0) (duracio 9.0))
    (trajecte (origen Madrid) (desti Paris) (transport avio) (preu 90.0) (duracio 2.0))
    (trajecte (origen Madrid) (desti Lisboa) (transport autobus) (preu 30.0) (duracio 8.0))
    (trajecte (origen Berlin) (desti Praga) (transport tren) (preu 40.0) (duracio 4.5))
    (trajecte (origen Praga) (desti Viena) (transport tren) (preu 35.0) (duracio 4.0))
    (trajecte (origen Atenes) (desti Estambul) (transport avio) (preu 90.0) (duracio 1.5))
    (trajecte (origen Estambul) (desti Roma) (transport avio) (preu 140.0) (duracio 3.0))
    (trajecte (origen Lisboa) (desti Barcelona) (transport avio) (preu 75.0) (duracio 2.0))

    ;; Trajectes - noves ciutats Sud-Amèrica
    (trajecte (origen Lima) (desti Cuzco) (transport avio) (preu 80.0) (duracio 1.5))
    (trajecte (origen Lima) (desti Cuzco) (transport autobus) (preu 25.0) (duracio 20.0))
    (trajecte (origen Cuzco) (desti Quito) (transport avio) (preu 200.0) (duracio 3.0))
    (trajecte (origen Lima) (desti Cartagena) (transport avio) (preu 280.0) (duracio 4.0))
    (trajecte (origen Cartagena) (desti Quito) (transport avio) (preu 220.0) (duracio 3.0))
)

;;; ----------------------------------------------------------------------------
;;; MÒDUL ENTREVISTA
;;; ----------------------------------------------------------------------------

(defmodule ENTREVISTA (import MAIN ?ALL) (export ?ALL))

(defrule preguntar-edat
    (declare (salience 100))
    (not (usuari-temp (atribut edat)))
    =>
    (printout t crlf "Benvingut a l'agencia 'Al Fi del Mon'." crlf)
    (assert (usuari-temp (atribut edat)
        (valor (llegir-enter-rang "Quina edat tens?" 1 120)))))

(defrule preguntar-origen
    (declare (salience 95))
    (usuari-temp (atribut edat))
    (not (usuari-temp (atribut origen)))
    =>
    (assert (usuari-temp (atribut origen)
        (valor (llegir-valid "Des de quina ciutat inicies el viatge?"
            (create$ Barcelona Madrid Paris Roma Londres Berlin Atenes Viena Amsterdam Lisboa BuenosAires Lima RioDeJaneiro Quito Cuzco Cartagena Estambul))))))

(defrule preguntar-tipus-grup
    (declare (salience 90))
    (usuari-temp (atribut origen))
    (not (usuari-temp (atribut tipus)))
    =>
    (assert (usuari-temp (atribut tipus)
        (valor (llegir-valid "Amb qui viatges?"
            (create$ solitari familia grupAmics grupGran parella))))))

(defrule preguntar-nens
    (declare (salience 80))
    (usuari-temp (atribut tipus) (valor familia))
    (not (usuari-temp (atribut te-nens)))
    =>
    (assert (usuari-temp (atribut te-nens)
        (valor (llegir-valid "Viatgeu amb nens?" (create$ si no))))))

(defrule preguntar-esdeveniment
    (declare (salience 80))
    (usuari-temp (atribut tipus) (valor parella))
    (not (usuari-temp (atribut esdeveniment)))
    =>
    (assert (usuari-temp (atribut esdeveniment)
        (valor (llegir-valid "Es un esdeveniment especial?"
            (create$ boda aniversari cap))))))

(defrule preguntar-esdeveniment-amics
    (declare (salience 80))
    (usuari-temp (atribut tipus) (valor grupAmics))
    (not (usuari-temp (atribut esdeveniment)))
    =>
    (assert (usuari-temp (atribut esdeveniment)
        (valor (llegir-valid "Es un esdeveniment especial?"
            (create$ fi-de-curs cap))))))

(defrule preguntar-nivell-cultural
    (declare (salience 70))
    (usuari-temp (atribut tipus))
    (not (usuari-temp (atribut nivell-cultural)))
    =>
    (assert (usuari-temp (atribut nivell-cultural)
        (valor (llegir-valid "Quin es el teu nivell cultural?" (create$ Baix Mig Alt))))))

(defrule preguntar-restriccions-pressupost
    (declare (salience 60))
    (usuari-temp (atribut tipus))
    (not (restriccions))
    =>
    (bind ?p (llegir-num-positiu "Quin es el pressupost maxim PER PERSONA al viatge?"))
    (bind ?minD (llegir-enter-rang "Quants dies minim vol que duri el viatge?" 1 365))
    (bind ?maxD (llegir-enter-rang "Quants dies maxim vol que duri el viatge?" ?minD 365))
    (bind ?maxC (llegir-enter-rang "Quantes ciutats vols visitar com a maxim?" 1 20))
    (bind ?minDC (llegir-enter-rang "Quin es el minim de dies per estar a cada ciutat?" 1 ?maxD))
    (bind ?minE (llegir-enter-rang "Quin nombre minim d'estrelles vols a l'allotjament? (1-5)" 1 5))
    (if (integerp ?p) then (bind ?p (float ?p)))
    (assert (restriccions (pressupost-max ?p) (min-dies ?minD) (max-dies ?maxD)
                         (max-ciutats ?maxC) (min-dies-ciutat ?minDC) (min-estrelles ?minE))))

(defrule preguntar-preferencies
    (declare (salience 50))
    (restriccions)
    (not (preferencies))
    =>
    (bind ?sq (llegir-valid "Sacrificaries qualitat per ajustar el pressupost?" (create$ si no)))
    (bind ?sd (llegir-valid "Sacrificaries duracio per ajustar el pressupost?" (create$ si no)))
    (bind ?pc (llegir-valid "Vols visitar llocs poc coneguts?" (create$ si no)))
    (bind ?tem (llegir-valid "Prefereixes una tematica?" (create$ Mediterrani Europa Sudamerica cap)))
    (assert (preferencies (sacrificar-qualitat ?sq) (sacrificar-duracio ?sd)
                          (llocs-poc-coneguts ?pc) (tematica-preferida ?tem))))

(defrule preguntar-transports-prohibits
    (declare (salience 40))
    ?r <- (restriccions (transports-prohibits $?buit))
    (not (usuari-temp (atribut transport-preguntat)))
    =>
    (printout t "Pots prohibir varis mitjans de transport. Introdueix 'cap' per acabar." crlf)
    (bind ?prohibits (create$))
    (bind ?seguir TRUE)
    (while ?seguir do
        (bind ?t (llegir-valid "Transport a prohibir (o 'cap' per acabar):"
                              (create$ avio vaixell tren autobus cotxe cap)))
        (if (eq ?t cap)
            then (bind ?seguir FALSE)
            else (if (not (member$ ?t ?prohibits))
                    then (bind ?prohibits (insert$ ?prohibits (+ (length$ ?prohibits) 1) ?t))
                         (printout t "  Prohibits fins ara: " (implode$ ?prohibits) crlf))))
    (assert (usuari-temp (atribut transport-preguntat) (valor si)))
    (if (> (length$ ?prohibits) 0) then (modify ?r (transports-prohibits ?prohibits))))

;;; ----------------------------------------------------------------------------
;;; MÒDUL INFERÈNCIA
;;; ----------------------------------------------------------------------------

(defmodule INFERENCIA (import MAIN ?ALL) (export ?ALL))

(defrule deduir-objectiu-boda
    (declare (salience 75))
    (usuari-temp (atribut esdeveniment) (valor boda))
    (not (usuari-temp (atribut objectiu)))
    =>
    (assert (usuari-temp (atribut objectiu) (valor romantic)))
    (printout t "[Info] Boda detectada -> objectiu romantic." crlf))

(defrule deduir-objectiu-nens
    (declare (salience 75))
    (usuari-temp (atribut te-nens) (valor si))
    (not (usuari-temp (atribut objectiu)))
    =>
    (assert (usuari-temp (atribut objectiu) (valor diversio)))
    (printout t "[Info] Viatge amb nens -> prioritzem diversio." crlf))

(defrule deduir-objectiu-aniversari
    (declare (salience 70))
    (usuari-temp (atribut esdeveniment) (valor aniversari))
    (not (usuari-temp (atribut objectiu)))
    =>
    (assert (usuari-temp (atribut objectiu) (valor romantic)))
    (printout t "[Info] Aniversari detectat -> objectiu romantic." crlf))

(defrule deduir-objectiu-fi-de-curs
    (declare (salience 70))
    (usuari-temp (atribut esdeveniment) (valor fi-de-curs))
    (not (usuari-temp (atribut objectiu)))
    =>
    (assert (usuari-temp (atribut objectiu) (valor diversio)))
    (printout t "[Info] Fi de curs detectat -> objectiu diversio." crlf))

(defrule deduir-objectiu-nivell-cultural-alt
    (declare (salience 65))
    (usuari-temp (atribut nivell-cultural) (valor Alt))
    (not (usuari-temp (atribut objectiu)))
    =>
    (assert (usuari-temp (atribut objectiu) (valor cultural)))
    (printout t "[Info] Nivell cultural alt -> objectiu cultural." crlf))

(defrule deduir-objectiu-edat-gran
    (declare (salience 60))
    (usuari-temp (atribut edat) (valor ?e))
    (test (> ?e 60))
    (not (usuari-temp (atribut objectiu)))
    =>
    (assert (usuari-temp (atribut objectiu) (valor descans)))
    (printout t "[Info] Edat avancada -> objectiu descans." crlf))

(defrule deduir-objectiu-grupAmics
    (declare (salience 50))
    (usuari-temp (atribut tipus) (valor grupAmics))
    (not (usuari-temp (atribut objectiu)))
    =>
    (assert (usuari-temp (atribut objectiu) (valor diversio)))
    (printout t "[Info] Grup d'amics -> objectiu diversio." crlf))

(defrule deduir-objectiu-grupGran
    (declare (salience 50))
    (usuari-temp (atribut tipus) (valor grupGran))
    (not (usuari-temp (atribut objectiu)))
    =>
    (assert (usuari-temp (atribut objectiu) (valor cultural)))
    (printout t "[Info] Grup gran -> objectiu cultural." crlf))

(defrule finalitzar-perfil
    (declare (salience 10))
    (usuari-temp (atribut edat) (valor ?e))
    (usuari-temp (atribut tipus) (valor ?t))
    (not (usuari))
    =>
    (bind ?orig Barcelona)
    (bind ?obj cultural)
    (bind ?nc Mig)
    (bind ?tn no)
    (bind ?ev cap)
    (do-for-fact ((?o usuari-temp)) (eq ?o:atribut origen) (bind ?orig ?o:valor))
    (do-for-fact ((?o usuari-temp)) (eq ?o:atribut objectiu) (bind ?obj ?o:valor))
    (do-for-fact ((?o usuari-temp)) (eq ?o:atribut nivell-cultural) (bind ?nc ?o:valor))
    (do-for-fact ((?o usuari-temp)) (eq ?o:atribut te-nens) (bind ?tn ?o:valor))
    (do-for-fact ((?o usuari-temp)) (eq ?o:atribut esdeveniment) (bind ?ev ?o:valor))
    (assert (usuari (edat ?e) (tipus ?t) (nivell-cultural ?nc) (te-nens ?tn)
                    (esdeveniment-especial ?ev) (objectiu ?obj) (ciutat-origen ?orig)))
    (printout t "[Deteccio] Perfil: " ?t " amb objectiu " ?obj
              " (nivell cultural " ?nc ")" crlf))

(defrule inferir-nivell-pressupost
    (restriccions (pressupost-max ?p) (max-dies ?d))
    (not (pressupost-estimat))
    =>
    (bind ?ratio (/ ?p ?d))
    (if (< ?ratio 100) then (assert (pressupost-estimat (nivell Baix)))
    else (if (>= ?ratio 250) then (assert (pressupost-estimat (nivell Alt)))
    else (assert (pressupost-estimat (nivell Mig))))))

(defrule detectar-incoherencia-restriccions
    (declare (salience 35))
    (restriccions (min-dies-ciutat ?mdc) (max-ciutats ?mc) (max-dies ?md)
                  (pressupost-max ?p) (min-estrelles ?me))
    (not (incoherencia-detectada))
    =>
    (assert (incoherencia-detectada))
    (if (> (* ?mdc ?mc) ?md) then
        (printout t crlf "[ATENCIO] Restriccions contradictories:" crlf)
        (printout t "  min-dies-ciutat (" ?mdc ") x max-ciutats (" ?mc ") = " (* ?mdc ?mc)
                  " > max-dies (" ?md ")." crlf)
        (printout t "  El sistema reduira automaticament el nombre de ciutats." crlf crlf))
    (if (< ?p 150) then
        (printout t crlf "[ATENCIO] Pressupost molt baix (" ?p " EUR)." crlf)
        (printout t "  Sera dificil trobar un pla viable." crlf crlf))
    (if (>= ?me 4) then
        (printout t crlf "[Info] Has demanat allotjaments de " ?me "+ estrelles." crlf)
        (printout t "  Aixo pot encarir el viatge significativament." crlf crlf)))

(defrule tematica-per-preferencia
    (declare (salience 30))
    (preferencies (tematica-preferida ?t&~cap))
    =>
    (if (eq ?t Mediterrani) then (assert (tematica-clau (nom CiutatsDelMediterrani) (prioritat 1))))
    (if (eq ?t Europa) then (assert (tematica-clau (nom GransCiutatsEuropees) (prioritat 1))))
    (if (eq ?t Sudamerica) then (assert (tematica-clau (nom SudamericaNatural) (prioritat 1)))))

(defrule tematica-per-objectiu
    (declare (salience 20))
    (usuari (objectiu ?obj))
    =>
    (if (eq ?obj romantic) then
        (assert (tematica-clau (nom Romantic) (prioritat 2)))
        (assert (tematica-clau (nom Cultural) (prioritat 3))))
    (if (eq ?obj cultural) then
        (assert (tematica-clau (nom Cultural) (prioritat 2))))
    (if (eq ?obj diversio) then
        (assert (tematica-clau (nom Diversio) (prioritat 2))))
    (if (eq ?obj descans) then
        (assert (tematica-clau (nom SudamericaNatural) (prioritat 2)))
        (assert (tematica-clau (nom CiutatsDelMediterrani) (prioritat 3)))))

(defrule marcar-ciutats-prio-1
    (declare (salience 15))
    (tematica-clau (nom ?tem) (prioritat 1))
    (ciutat (nom ?c) (tematiques $? ?tem $?))
    (not (ciutat-compatible (nom ?c)))
    =>
    (assert (ciutat-compatible (nom ?c) (prioritat 1))))

(defrule marcar-ciutats-prio-2
    (declare (salience 10))
    (tematica-clau (nom ?tem) (prioritat 2))
    (ciutat (nom ?c) (tematiques $? ?tem $?))
    (not (ciutat-compatible (nom ?c)))
    =>
    (assert (ciutat-compatible (nom ?c) (prioritat 2))))

(defrule marcar-ciutats-prio-3
    (declare (salience 5))
    (tematica-clau (nom ?tem) (prioritat 3))
    (ciutat (nom ?c) (tematiques $? ?tem $?))
    (not (ciutat-compatible (nom ?c)))
    =>
    (assert (ciutat-compatible (nom ?c) (prioritat 3))))

;;; ----------------------------------------------------------------------------
;;; MÒDUL GENERACIÓ
;;; ----------------------------------------------------------------------------

(defmodule GENERACIO (import MAIN ?ALL) (export ?ALL))

(defrule iniciar-generacio
    (declare (salience 10))
    =>
    (assert (fase-control (actual seleccio-ciutats))))

(defrule seleccionar-ciutats-pla-1
    (fase-control (actual seleccio-ciutats))
    (restriccions (max-ciutats ?max) (max-dies ?md) (min-dies-ciutat ?minDC))
    (preferencies (llocs-poc-coneguts ?pc))
    (usuari (ciutat-origen ?orig))
    (not (viatge-candidat (id 1)))
    =>
    (bind ?llista (create$))
    (bind ?max-real (min ?max (max 1 (integer (/ ?md ?minDC)))))

    ;; Per viatges curts (<=6 dies) ens limitem a una sola regio per evitar saltos transatlantics
    (bind ?regio-fix nil)
    (if (<= ?md 6) then
        (do-for-fact ((?cc ciutat-compatible)) (and (eq ?cc:prioritat 1) (neq ?cc:nom ?orig))
            (if (eq ?regio-fix nil) then
                (do-for-fact ((?cit ciutat)) (and (eq ?cit:nom ?cc:nom) (neq ?cit:nom ?orig))
                    (bind ?regio-fix ?cit:regio))))
        (if (eq ?regio-fix nil) then
            (do-for-fact ((?cc ciutat-compatible)) (and (eq ?cc:prioritat 2) (neq ?cc:nom ?orig))
                (if (eq ?regio-fix nil) then
                    (do-for-fact ((?cit ciutat)) (and (eq ?cit:nom ?cc:nom) (neq ?cit:nom ?orig))
                        (bind ?regio-fix ?cit:regio))))))

    (loop-for-count (?pri 1 3)
        (do-for-all-facts ((?cc ciutat-compatible)) (and (eq ?cc:prioritat ?pri) (neq ?cc:nom ?orig))
            (if (< (length$ ?llista) ?max-real) then
                (bind ?coincid TRUE)
                (if (neq ?regio-fix nil) then
                    (bind ?coincid FALSE)
                    (do-for-fact ((?cit ciutat)) (and (eq ?cit:nom ?cc:nom) (eq ?cit:regio ?regio-fix))
                        (bind ?coincid TRUE)))
                (if ?coincid then
                    (bind ?llista (insert$ ?llista (+ (length$ ?llista) 1) ?cc:nom))))))

    (if (< (length$ ?llista) ?max-real) then
        (if (eq ?pc si) then
            (do-for-all-facts ((?c ciutat)) (and (not (member$ ?c:nom ?llista))
                                                 (neq ?c:nom ?orig)
                                                 (or (eq ?c:popularitat PocConegut) (eq ?c:popularitat Conegut))
                                                 (or (eq ?regio-fix nil) (eq ?c:regio ?regio-fix)))
                (if (< (length$ ?llista) ?max-real) then
                    (bind ?llista (insert$ ?llista (+ (length$ ?llista) 1) ?c:nom))))))

    (do-for-all-facts ((?c ciutat)) (and (not (member$ ?c:nom ?llista))
                                         (neq ?c:nom ?orig)
                                         (or (eq ?regio-fix nil) (eq ?c:regio ?regio-fix)))
        (if (< (length$ ?llista) ?max-real) then
            (bind ?llista (insert$ ?llista (+ (length$ ?llista) 1) ?c:nom))))

    (printout t crlf "[Generant Pla 1] Ciutats: " (implode$ ?llista) crlf)
    (assert (viatge-candidat (id 1) (ciutats-visitades ?llista))))

(defrule seleccionar-ciutats-pla-2
    ?f <- (fase-control (actual seleccio-ciutats))
    (viatge-candidat (id 1) (ciutats-visitades $?c1))
    (restriccions (max-ciutats ?max) (max-dies ?md) (min-dies-ciutat ?minDC))
    (usuari (ciutat-origen ?orig))
    (not (viatge-candidat (id 2)))
    =>
    (bind ?llista (create$))
    (bind ?max-real (min ?max (max 1 (integer (/ ?md ?minDC)))))

    (loop-for-count (?pri 1 3)
        (do-for-all-facts ((?cc ciutat-compatible)) (and (eq ?cc:prioritat ?pri) (not (member$ ?cc:nom ?c1)) (neq ?cc:nom ?orig))
            (if (< (length$ ?llista) ?max-real) then
                (bind ?llista (insert$ ?llista (+ (length$ ?llista) 1) ?cc:nom)))))

    (do-for-all-facts ((?c ciutat)) (and (not (member$ ?c:nom ?c1)) (not (member$ ?c:nom ?llista)) (neq ?c:nom ?orig))
        (if (< (length$ ?llista) ?max-real) then
            (bind ?llista (insert$ ?llista (+ (length$ ?llista) 1) ?c:nom))))

    (printout t "[Generant Pla 2] Ciutats: " (implode$ ?llista) crlf)
    (assert (viatge-candidat (id 2) (ciutats-visitades ?llista)))
    (assert (fase-control (actual crear-estades))))

(defrule crear-estada-base
    (fase-control (actual crear-estades))
    (viatge-candidat (id ?id) (ciutats-visitades $? ?c $?))
    (not (estada (id-viatge ?id) (ciutat ?c)))
    (restriccions (max-dies ?md) (min-dies-ciutat ?minc) (max-dies-ciutat ?maxc))
    (preferencies (sacrificar-duracio ?sd))
    =>
    (bind ?ncits 1)
    (do-for-fact ((?v viatge-candidat)) (eq ?v:id ?id)
        (bind ?ncits (length$ ?v:ciutats-visitades)))
    (bind ?dies (integer (/ ?md ?ncits)))
    (if (< ?dies 1) then (bind ?dies 1))
    (if (> ?dies ?maxc) then (bind ?dies ?maxc))
    (if (<= (* ?minc ?ncits) ?md) then
        (if (< ?dies ?minc) then (bind ?dies ?minc)))
    (if (eq ?sd si) then
        (bind ?dies (max ?minc (- ?dies 1))))
    (assert (estada (id-viatge ?id) (ciutat ?c) (dies ?dies) (allotjament nil) (visites (create$)))))

;; Regles per deduir el rang d'estrelles desitjat
(defrule calcular-rang-allotjament-pla2
    (fase-control (actual crear-estades))
    (estada (id-viatge 2) (ciutat ?c) (allotjament nil))
    (restriccions (min-estrelles ?me-rest))
    (not (cerca-allotjament (id-viatge 2) (ciutat ?c)))
    =>
    (assert (cerca-allotjament (id-viatge 2) (ciutat ?c) (min-estrelles (max 1 ?me-rest)) (max-estrelles 3))))

(defrule calcular-rang-allotjament-economic
    (fase-control (actual crear-estades))
    (estada (id-viatge ?id&~2) (ciutat ?c) (allotjament nil))
    (pressupost-estimat (nivell Baix))
    (restriccions (min-estrelles ?me-rest))
    (not (cerca-allotjament (id-viatge ?id) (ciutat ?c)))
    =>
    (assert (cerca-allotjament (id-viatge ?id) (ciutat ?c) (min-estrelles (max 1 ?me-rest)) (max-estrelles 3))))

(defrule calcular-rang-allotjament-sacrifica
    (fase-control (actual crear-estades))
    (estada (id-viatge ?id&~2) (ciutat ?c) (allotjament nil))
    (preferencies (sacrificar-qualitat si))
    (restriccions (min-estrelles ?me-rest))
    (not (cerca-allotjament (id-viatge ?id) (ciutat ?c)))
    =>
    (assert (cerca-allotjament (id-viatge ?id) (ciutat ?c) (min-estrelles (max 1 ?me-rest)) (max-estrelles 3))))

(defrule calcular-rang-allotjament-standard
    (fase-control (actual crear-estades))
    (estada (id-viatge ?id&~2) (ciutat ?c) (allotjament nil))
    (pressupost-estimat (nivell ?np&~Baix))
    (preferencies (sacrificar-qualitat no))
    (restriccions (min-estrelles ?me-rest))
    (not (cerca-allotjament (id-viatge ?id) (ciutat ?c)))
    =>
    (assert (cerca-allotjament (id-viatge ?id) (ciutat ?c) (min-estrelles (max 4 ?me-rest)) (max-estrelles 5))))

;; Regla declarativa que troba l'allotjament ideal per Pattern Matching
(defrule assignar-allotjament-ideal
    (fase-control (actual crear-estades))
    ?cerca <- (cerca-allotjament (id-viatge ?id) (ciutat ?c) (min-estrelles ?min) (max-estrelles ?max))
    ?estada <- (estada (id-viatge ?id) (ciutat ?c) (allotjament nil))
    (allotjament (ciutat ?c) (nom ?nom) (estrelles ?e&:(and (>= ?e ?min) (<= ?e ?max))))
    =>
    (modify ?estada (allotjament ?nom))
    (retract ?cerca))

;; Fallback per si cap hotel s'ajusta exactament al rang ideal de qualitat demanat
(defrule assignar-allotjament-fallback
    (declare (salience -10))
    (fase-control (actual crear-estades))
    ?cerca <- (cerca-allotjament (id-viatge ?id) (ciutat ?c))
    ?estada <- (estada (id-viatge ?id) (ciutat ?c) (allotjament nil))
    (allotjament (ciutat ?c) (nom ?nom))
    =>
    (modify ?estada (allotjament ?nom))
    (retract ?cerca))

(defrule inicialitzar-limit-visites
    (fase-control (actual crear-estades))
    (estada (id-viatge ?id) (ciutat ?c) (dies ?dies))
    (not (limit-visites (id-viatge ?id) (ciutat ?c)))
    =>
    (bind ?max-v (min 5 (max 1 (* ?dies 2))))
    (assert (limit-visites (id-viatge ?id) (ciutat ?c) (maxim ?max-v))))

(defrule afegir-visita-indispensable
    (declare (salience 20)) ;; Prioritat alta: entren primer
    (fase-control (actual crear-estades))
    ?estada <- (estada (id-viatge ?id) (ciutat ?c) (visites $?vst))
    (limit-visites (id-viatge ?id) (ciutat ?c) (maxim ?max-v))
    (usuari (tipus ?ut))
    (lloc-interes (nom ?nom) (ciutat ?c) (importancia Indispensable) (es-perillos ?per))
    (test (< (length$ ?vst) ?max-v))
    (test (not (member$ ?nom ?vst)))
    (test (or (neq ?ut familia) (eq ?per no)))
    =>
    (modify ?estada (visites (insert$ ?vst (+ (length$ ?vst) 1) ?nom))))

(defrule afegir-visita-rellevant-pla1
    (declare (salience 10))
    (fase-control (actual crear-estades))
    ?estada <- (estada (id-viatge 1) (ciutat ?c) (visites $?vst))
    (limit-visites (id-viatge 1) (ciutat ?c) (maxim ?max-v))
    (usuari (tipus ?ut))
    (lloc-interes (nom ?nom) (ciutat ?c) (importancia Rellevant) (es-perillos ?per))
    (test (< (length$ ?vst) ?max-v))
    (test (not (member$ ?nom ?vst)))
    (test (or (neq ?ut familia) (eq ?per no)))
    =>
    (modify ?estada (visites (insert$ ?vst (+ (length$ ?vst) 1) ?nom))))

(defrule afegir-visita-rellevant-cultural-alt
    (declare (salience 10))
    (fase-control (actual crear-estades))
    ?estada <- (estada (id-viatge ?id) (ciutat ?c) (visites $?vst))
    (limit-visites (id-viatge ?id) (ciutat ?c) (maxim ?max-v))
    (usuari (tipus ?ut) (nivell-cultural Alt))
    (lloc-interes (nom ?nom) (ciutat ?c) (importancia Rellevant) (es-perillos ?per))
    (test (< (length$ ?vst) ?max-v))
    (test (not (member$ ?nom ?vst)))
    (test (or (neq ?ut familia) (eq ?per no)))
    =>
    (modify ?estada (visites (insert$ ?vst (+ (length$ ?vst) 1) ?nom))))

(defrule passar-a-transports
    ?f <- (fase-control (actual crear-estades))
    (forall (viatge-candidat (id ?id) (ciutats-visitades $? ?c $?))
            (estada (id-viatge ?id) (ciutat ?c) (allotjament ?allotj&~nil)))
    =>
    (modify ?f (actual crear-transports)))

(defrule generar-trams-viatge
    (fase-control (actual crear-transports))
    (viatge-candidat (id ?id) (ciutats-visitades $?ciuts))
    (usuari (ciutat-origen ?orig))
    (not (trams-generats (id-viatge ?id)))
    =>
    (bind ?len (length$ ?ciuts))
    (if (> ?len 0) then
        (assert (tram (id-viatge ?id) (origen ?orig) (desti (nth$ 1 ?ciuts)) (posicio 1)))
        (loop-for-count (?i 1 (- ?len 1))
            (assert (tram (id-viatge ?id) (origen (nth$ ?i ?ciuts)) (desti (nth$ (+ ?i 1) ?ciuts)) (posicio (+ ?i 1)))))
        (assert (tram (id-viatge ?id) (origen (nth$ ?len ?ciuts)) (desti ?orig) (posicio (+ ?len 1)))))
    (assert (trams-generats (id-viatge ?id))))

(defrule assignar-transport-real-inicial
    (fase-control (actual crear-transports))
    (restriccions (transports-prohibits $?proh))
    ?t <- (tram (id-viatge ?id) (origen ?o) (desti ?d) (transport unassigned))
    (trajecte (origen ?o2) (desti ?d2) (transport ?tr) (preu ?p))
    (test (or (and (eq ?o2 ?o) (eq ?d2 ?d)) (and (eq ?o2 ?d) (eq ?d2 ?o))))
    (test (not (member$ ?tr ?proh)))
    =>
    (modify ?t (transport ?tr) (preu ?p)))

;; Regla de refinament i optimització: Si hi ha un transport real mes barat, el canvia en calent!
(defrule optimitzar-transport-real
    (fase-control (actual crear-transports))
    (restriccions (transports-prohibits $?proh))
    ?t <- (tram (id-viatge ?id) (origen ?o) (desti ?d) (transport ?tr-actual) (preu ?p-actual))
    (trajecte (origen ?o2) (desti ?d2) (transport ?tr-nou) (preu ?p-nou))
    (test (or (and (eq ?o2 ?o) (eq ?d2 ?d)) (and (eq ?o2 ?d) (eq ?d2 ?o))))
    (test (not (member$ ?tr-nou ?proh)))
    (test (< ?p-nou ?p-actual))
    =>
    (modify ?t (transport ?tr-nou) (preu ?p-nou)))

;; Regles de Fallback si no hi ha trajectes directes registrats
(defrule assignar-transport-estimat-avio
    (declare (salience -10))
    (fase-control (actual crear-transports))
    (restriccions (transports-prohibits $?proh))
    ?t <- (tram (id-viatge ?id) (origen ?o) (desti ?d) (transport unassigned))
    (test (not (member$ avio ?proh)))
    =>
    (modify ?t (transport avio-estimat) (preu 250.0)))

(defrule assignar-transport-estimat-tren
    (declare (salience -10))
    (fase-control (actual crear-transports))
    (restriccions (transports-prohibits $?proh))
    ?t <- (tram (id-viatge ?id) (origen ?o) (desti ?d) (transport unassigned))
    (test (member$ avio ?proh))
    (test (not (member$ tren ?proh)))
    =>
    (modify ?t (transport tren-estimat) (preu 150.0)))

(defrule assignar-transport-estimat-autobus
    (declare (salience -10))
    (fase-control (actual crear-transports))
    (restriccions (transports-prohibits $?proh))
    ?t <- (tram (id-viatge ?id) (origen ?o) (desti ?d) (transport unassigned))
    (test (member$ avio ?proh))
    (test (member$ tren ?proh))
    =>
    (modify ?t (transport autobus-estimat) (preu 80.0)))

(defrule GENERACIO::sumar-cost-estada
    (fase-control (actual crear-transports))
    ?v <- (viatge-candidat (id ?id) (preu-total ?pt) (duracio-total ?dt))
    (estada (id-viatge ?id) (ciutat ?c) (dies ?d) (allotjament ?allotj) (visites $?vis))
    (allotjament (nom ?allotj) (preu-nit ?preu-n))
    (ciutat (nom ?c) (nivell-vida ?nv))
    (not (estada-comptabilitzada (id-viatge ?id) (ciutat ?c)))
    =>
    (bind ?factor 1.0)
    (if (eq ?nv Alt) then (bind ?factor 1.1))
    (if (eq ?nv Baix) then (bind ?factor 0.9))
    (bind ?cost-allotj (* ?d ?preu-n ?factor))

    (bind ?cost-vis 0.0)
    (progn$ (?visita ?vis)
        (do-for-fact ((?ll lloc-interes)) (eq ?ll:nom ?visita)
            (bind ?cost-vis (+ ?cost-vis ?ll:preu))))

    (modify ?v (preu-total (+ ?pt ?cost-allotj ?cost-vis))
               (duracio-total (+ ?dt ?d)))
    (assert (estada-comptabilitzada (id-viatge ?id) (ciutat ?c))))

(defrule GENERACIO::sumar-cost-transport
    (fase-control (actual crear-transports))
    ?v <- (viatge-candidat (id ?id) (preu-total ?pt))
    (tram (id-viatge ?id) (posicio ?pos) (transport ?tr&~unassigned) (preu ?p))
    (not (tram-comptabilitzat (id-viatge ?id) (posicio ?pos)))
    =>
    (modify ?v (preu-total (+ ?pt ?p)))
    (assert (tram-comptabilitzat (id-viatge ?id) (posicio ?pos))))

;; Regla de tancament: reconstrueix la llista ordenada de rutes un cop calculat tot
(defrule GENERACIO::finalitzar-viatge-candidat
    (fase-control (actual crear-transports))
    ?v <- (viatge-candidat (id ?id) (ciutats-visitades $?ciuts) (rutes $?buit))
    (test (= (length$ ?buit) 0))
    (forall (estada (id-viatge ?id) (ciutat ?c))
            (estada-comptabilitzada (id-viatge ?id) (ciutat ?c)))
    (forall (tram (id-viatge ?id) (posicio ?pos))
            (tram-comptabilitzat (id-viatge ?id) (posicio ?pos)))
    =>
    (bind ?llista-rutes (create$))
    (bind ?total-trams (+ (length$ ?ciuts) 1))
    (loop-for-count (?i 1 ?total-trams)
        (do-for-fact ((?t tram)) (and (eq ?t:id-viatge ?id) (eq ?t:posicio ?i))
            (bind ?llista-rutes (insert$ ?llista-rutes ?i ?t:transport))))
    (modify ?v (rutes ?llista-rutes)))

;;; ----------------------------------------------------------------------------
;;; MÒDUL VALIDACIÓ (Hard Constraints)
;;; ----------------------------------------------------------------------------
(defmodule VALIDACIO (import MAIN ?ALL) (export ?ALL))

(defrule descartar-per-pressupost
    ?cand <- (viatge-candidat (id ?id) (preu-total ?p) (valid si) (puntuacio ?pts) (motius $?m))
    (restriccions (pressupost-max ?max))
    (test (> ?p ?max))
    =>
    (modify ?cand (valid no)
                  (puntuacio (- ?pts 10000))
                  (motius (insert$ ?m 1 (str-cat "[AVIS] Supera el pressupost maxim: " ?p " > " ?max " EUR.")))))

(defrule descartar-per-duracio-maxima
    ?cand <- (viatge-candidat (id ?id) (duracio-total ?d) (valid si) (puntuacio ?pts) (motius $?m))
    (restriccions (max-dies ?md))
    (test (> ?d ?md))
    =>
    (modify ?cand (valid no)
                  (puntuacio (- ?pts 10000))
                  (motius (insert$ ?m 1 (str-cat "[AVIS] Supera els dies maxims: " ?d " > " ?md " dies.")))))

(defrule descartar-per-duracio-minima
    ?cand <- (viatge-candidat (id ?id) (duracio-total ?d) (valid si) (puntuacio ?pts) (motius $?m))
    (restriccions (min-dies ?mind))
    (preferencies (sacrificar-duracio no)) ;; Només penalitza si l'usuari NO vol sacrificar dies
    (test (< ?d ?mind))
    =>
    (modify ?cand (valid no)
                  (puntuacio (- ?pts 10000))
                  (motius (insert$ ?m 1 (str-cat "[AVIS] No assoleix els dies minims demanats: " ?d " < " ?mind " dies.")))))

;;; ----------------------------------------------------------------------------
;;; MODUL PUNTUACIO (Scoring & Heuristiques)
;;; ----------------------------------------------------------------------------
(defmodule PUNTUACIO (import MAIN ?ALL) (export ?ALL))

(defrule premiar-ajust-pressupost
    ?cand <- (viatge-candidat (id ?id) (valid si) (preu-total ?p) (puntuacio ?pts) (motius $?m))
    (restriccions (pressupost-max ?max))
    (test (<= ?p (* ?max 0.9)))
    (not (puntuat-pressupost ?id))
    =>
    (modify ?cand (puntuacio (+ ?pts 20))
                  (motius (insert$ ?m 1 "+ Excellent ajust al pressupost.")))
    (assert (puntuat-pressupost ?id)))

(defrule penalitzar-hostal-familia
    ?cand <- (viatge-candidat (id ?id) (valid si) (puntuacio ?pts) (motius $?m))
    (usuari (tipus familia) (te-nens si))
    (estada (id-viatge ?id) (allotjament ?allotj))
    (allotjament (nom ?allotj) (estrelles 2))
    (not (penalitzat-hostal ?id))
    =>
    (modify ?cand (puntuacio (- ?pts 30))
                  (motius (insert$ ?m 1 "- Allotjament poc adequat per a nens (Hostal).")))
    (assert (penalitzat-hostal ?id)))

(defrule premiar-tematica-preferida
    ?cand <- (viatge-candidat (id ?id) (valid si) (puntuacio ?pts) (motius $?m) (ciutats-visitades $?cv))
    (preferencies (tematica-preferida ?tem&~cap))
    (ciutat (nom ?c) (tematiques $? ?tem $?))
    (test (member$ ?c ?cv))
    (not (puntuat-tematica ?id ?c))
    =>
    (modify ?cand (puntuacio (+ ?pts 15))
                  (motius (insert$ ?m 1 (str-cat "+ Inclou la ciutat " ?c " de la teva tematica preferida."))))
    (assert (puntuat-tematica ?id ?c)))

;;; ----------------------------------------------------------------------------
;;; MÒDUL SELECCIÓ (Ranking)
;;; ----------------------------------------------------------------------------
(defmodule SELECCIO (import MAIN ?ALL) (export ?ALL))

(defrule escollir-top-1
    ?cand <- (viatge-candidat (id ?id) (valid ?v) (puntuacio ?pts) (ciutats-visitades $?cv)
                              (rutes $?r) (preu-total ?pt) (duracio-total ?dt) (motius $?m))
    (not (viatge-candidat (puntuacio ?pts2&:(> ?pts2 ?pts))))
    (not (viatge-proposat (num-ordre 1)))
    =>
    (assert (viatge-proposat (num-ordre 1) (id-original ?id) (valid ?v) (ciutats-visitades ?cv)
                             (rutes ?r) (preu-total ?pt) (duracio-total ?dt) (motius ?m)))
    (retract ?cand)) ;; L'eliminem perque la següent regla agafi el 2n millor

(defrule escollir-top-2
    (viatge-proposat (num-ordre 1)) ;; Ens assegurem que el 1r ja esta escollit
    ?cand <- (viatge-candidat (id ?id) (valid ?v) (puntuacio ?pts) (ciutats-visitades $?cv)
                              (rutes $?r) (preu-total ?pt) (duracio-total ?dt) (motius $?m))
    (not (viatge-candidat (puntuacio ?pts2&:(> ?pts2 ?pts))))
    (not (viatge-proposat (num-ordre 2)))
    =>
    (assert (viatge-proposat (num-ordre 2) (id-original ?id) (valid ?v) (ciutats-visitades ?cv)
                             (rutes ?r) (preu-total ?pt) (duracio-total ?dt) (motius ?m)))
    (retract ?cand))
;;; ----------------------------------------------------------------------------
;;; MODUL PRESENTACIO
;;; ----------------------------------------------------------------------------

(defmodule PRESENTACIO (import MAIN ?ALL) (export ?ALL))

(defrule mostrar-capcalera-contextual
    (declare (salience 100))
    (viatge-proposat (num-ordre 1) (valid ?v1))
    (viatge-proposat (num-ordre 2) (valid ?v2))
    (not (capcalera-mostrada))
    =>
    (printout t crlf "================================================" crlf)
    (printout t "           RESULTAT DE LA CERCA EXPERTA" crlf)
    (printout t "================================================" crlf)

    (bind ?valids 0)
    (if (eq ?v1 si) then (bind ?valids (+ ?valids 1)))
    (if (eq ?v2 si) then (bind ?valids (+ ?valids 1)))

    (if (= ?valids 2) then
        (printout t "Tots dos plans son satisfactoris i compleixen les teves restriccions." crlf))
    (if (= ?valids 1) then
        (printout t "Nomes 1 pla compleix estrictament les teves restriccions. Te'l mostrem juntament amb una alternativa." crlf))
    (if (= ?valids 0) then
        (printout t "[AVIS] Cap pla compleix totes les teves restriccions (pressupost, dies...). Tot i aixi, et mostrem les 2 opcions que s'hi acosten mes." crlf))
    (assert (capcalera-mostrada)))


(defrule mostrar-recomanacio-estructurada
    (declare (salience 50))
    (capcalera-mostrada)
    (usuari (ciutat-origen ?orig) (tipus ?tipus) (objectiu ?obj))
    (preferencies (tematica-preferida ?tem) (sacrificar-qualitat ?sq) (sacrificar-duracio ?sd) (llocs-poc-coneguts ?pc))
    (restriccions (pressupost-max ?max) (min-dies ?minD) (max-dies ?maxD))
    (not (recomanacio-mostrada))
    =>
    (printout t crlf "================================================" crlf)
    (printout t "          RESUM DE PERFIL DE L'USUARI" crlf)
    (printout t "================================================" crlf)
    (printout t "Ciutat d'origen: " ?orig crlf)
    (printout t "Tipus: " ?tipus crlf)
    (printout t "Objectiu: " ?obj crlf)
    (printout t "Tematica preferida: " ?tem crlf)

    (foreach ?ordre (create$ 1 2)
        (do-for-fact ((?v viatge-proposat)) (eq ?v:num-ordre ?ordre)
            (printout t crlf "================================================" crlf)
            (if (eq ?v:valid si)
                then (printout t "  RECOMANACIO DE VIATGE #" ?ordre " [SATISFACTORIA]" crlf)
                else (printout t "  RECOMANACIO DE VIATGE #" ?ordre " [NO SATISFACTORIA - ALTERNATIVA]" crlf))
            (printout t "================================================" crlf)

            (printout t "Preu total estimat (per persona): " ?v:preu-total " EUR" crlf)
            (printout t "Duracio: " ?v:duracio-total " dies" crlf)
            (printout t "Itinerari: ")

            (printout t ?orig " --(" (nth$ 1 ?v:rutes) ")--> ")
            (loop-for-count (?i 1 (length$ ?v:ciutats-visitades))
                (printout t (nth$ ?i ?v:ciutats-visitades))
                (printout t " --(" (nth$ (+ ?i 1) ?v:rutes) ")--> "))
            (printout t ?orig crlf crlf)

            ;; Imprimir Estades, Allotjaments i Visites (utilitzant id-original)
            (printout t "Detalls per ciutat:" crlf)
            (do-for-all-facts ((?e estada)) (eq ?e:id-viatge ?v:id-original)
                (printout t "  > " ?e:ciutat " (" ?e:dies " dies)" crlf)
                (printout t "    Allotjament: " ?e:allotjament crlf)
                (printout t "    Visites: ")
                (if (= (length$ ?e:visites) 0)
                    then (printout t "(no n'hi ha disponibles)")
                    else (progn$ (?vis ?e:visites) (printout t ?vis " ")))
                (printout t crlf))

            ;; Imprimir els motius experts que vam afegir al nou sistema
            (printout t crlf "Comentaris i puntuacio del Sistema Expert:" crlf)
            (if (= (length$ ?v:motius) 0)
                then (printout t "  Sense comentaris addicionals." crlf)
                else (progn$ (?m ?v:motius) (printout t "  " ?m crlf)))

            ;; Replicar l'antiga llista de preferencies complertes
            (printout t crlf "Preferencies complertes:" crlf)
            (if (<= ?v:preu-total ?max)
                then (printout t "  + S'ajusta al pressupost (" ?v:preu-total " <= " ?max " EUR)" crlf)
                else (printout t "  - No s'ajusta al pressupost (Supera els " ?max " EUR)" crlf))

            (if (and (>= ?v:duracio-total ?minD) (<= ?v:duracio-total ?maxD))
                then (printout t "  + Duracio dins del rang demanat (" ?v:duracio-total " dies)" crlf)
                else (printout t "  - Duracio fora del rang demanat (" ?v:duracio-total " dies)" crlf))

            (if (neq ?tem cap) then
                (bind ?coincid 0)
                (do-for-all-facts ((?cc ciutat-compatible))
                    (and (eq ?cc:prioritat 1) (member$ ?cc:nom ?v:ciutats-visitades))
                    (bind ?coincid (+ ?coincid 1)))
                (if (> ?coincid 0)
                    then (printout t "  + " ?coincid " ciutats coincideixen amb la tematica '" ?tem "'" crlf)
                    else (printout t "  - Cap ciutat coincideix amb la tematica '" ?tem "'" crlf)))

            (if (eq ?pc si) then
                (bind ?poc 0)
                (do-for-all-facts ((?cit ciutat))
                    (and (member$ ?cit:nom ?v:ciutats-visitades)
                         (or (eq ?cit:popularitat PocConegut) (eq ?cit:popularitat Conegut)))
                    (bind ?poc (+ ?poc 1)))
                (printout t "  " (if (> ?poc 0) then "+" else "-")
                          " " ?poc " ciutats poc conegudes" crlf))

            (if (eq ?sq si)
                 then (printout t "  + Allotjaments economics seleccionats per ajustar pressupost" crlf))
            (if (eq ?sd si)
                then (printout t "  + Duracio retallada per ajustar pressupost" crlf))
        )
    )

    (printout t crlf "================================================" crlf)
    (printout t "Esperem que aquestes propostes siguin del seu gust." crlf)
    (printout t "Bon viatge!" crlf)
    (printout t "================================================" crlf crlf)
    (assert (recomanacio-mostrada))
    (halt))

;;; ----------------------------------------------------------------------------
;;; REGLA DE CONTROL
;;; ----------------------------------------------------------------------------

(defrule MAIN::iniciar
    (declare (salience 1000))

    =>
    (printout t crlf "[SISTEMA] Iniciant recomanador de viatges..." crlf)
    (focus ENTREVISTA INFERENCIA GENERACIO VALIDACIO PUNTUACIO SELECCIO PRESENTACIO))
