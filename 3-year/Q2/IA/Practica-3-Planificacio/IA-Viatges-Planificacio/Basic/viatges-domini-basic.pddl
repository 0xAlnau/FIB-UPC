(define (domain viatges)
    (:requirements :adl :typing :fluents)

    (:types ciutat hotel - object)

    (:predicates
        (usuari_a ?c - ciutat)
        (visitada ?c - ciutat)
        (vol ?co - ciutat ?cd - ciutat)
        (hotel_a ?h - hotel ?c - ciutat)
        (ruta_iniciada)
    )

    (:functions
        (ciutatsVisitades)
        (minimCiutats)
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
            (increase (ciutatsVisitades) 1)
        )
    )

    (:action vola
        :parameters (?co - ciutat ?cd - ciutat ?h - hotel)
        :precondition (and
            (usuari_a ?co)
            (vol ?co ?cd)
            (not (visitada ?cd))
            (hotel_a ?h ?cd)
        )
        :effect (and
            (not (usuari_a ?co))
            (usuari_a ?cd)
            (visitada ?cd)
            (increase (ciutatsVisitades) 1)
        )
    )
)
