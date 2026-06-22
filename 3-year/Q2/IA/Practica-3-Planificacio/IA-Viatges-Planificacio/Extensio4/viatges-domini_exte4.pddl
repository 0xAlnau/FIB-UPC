(define (domain viatges)
    (:requirements :adl :typing :fluents)

    (:types ciutat hotel - object)

    (:predicates
        (usuari_a ?c - ciutat)
        (visitada ?c - ciutat)
        (vol ?co - ciutat ?cd - ciutat)
        (hotel_a ?h - hotel ?c - ciutat)
        (allotjat_a ?h - hotel)
        (ruta_iniciada)
    )

    (:functions
        (minimCiutats)
        (minimDiesRuta)
        (minDiesPerCiutat)
        (maxDiesPerCiutat)
        (ciutatsVisitades)
        (diesEnRuta)
        (diesEnCiutat ?c - ciutat)

        (interes ?c - ciutat)
        (interesTotal)

        (costTotal)
        (costVol ?co - ciutat ?cd - ciutat)
        (costHotel ?h - hotel)
        (pressupostMin)
        (pressupostMax)
    )

    (:action inicia_ruta
        :parameters (?c - ciutat ?h - hotel)
        :precondition (and
            (not (ruta_iniciada))
            (hotel_a ?h ?c)
        )
        :effect (and
            (usuari_a ?c)
            (visitada ?c)
            (ruta_iniciada)
            (allotjat_a ?h)
            (increase (ciutatsVisitades) 1)
            (increase (interesTotal) (interes ?c))
        )
    )

    (:action visitar
        :parameters (?c - ciutat ?h - hotel)
        :precondition (and
            (usuari_a ?c)
            (allotjat_a ?h)
            (< (diesEnCiutat ?c) (maxDiesPerCiutat))
        )
        :effect (and
            (increase (diesEnCiutat ?c) 1)
            (increase (diesEnRuta) 1)
            (increase (costTotal) (costHotel ?h))
        )
    )

    (:action vola
        :parameters (?co - ciutat ?h_actual - hotel ?cd - ciutat ?h_nou - hotel)
        :precondition (and
            (usuari_a ?co)
            (allotjat_a ?h_actual)
            (vol ?co ?cd)
            (not (visitada ?cd))
            (>= (diesEnCiutat ?co) (minDiesPerCiutat))
            (hotel_a ?h_nou ?cd)
        )
        :effect (and
            (not (usuari_a ?co))
            (not (allotjat_a ?h_actual))
            (usuari_a ?cd)
            (allotjat_a ?h_nou)
            (visitada ?cd)
            (increase (ciutatsVisitades) 1)
            (increase (costTotal) (costVol ?co ?cd))
            (increase (interesTotal) (interes ?cd))
        )
    )
)
