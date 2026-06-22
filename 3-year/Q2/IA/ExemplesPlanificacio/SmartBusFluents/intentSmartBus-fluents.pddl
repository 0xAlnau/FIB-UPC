(define (domain SmartBus)
    (:requirements :adl :typing :fluents)

    (:functions
        (seientsN ?b)
        (seientsR ?b)
    )

    (:types persona bus seient parada - object
            pNormal pMovilRedu - persona
            sNormal sMovilRedu - seient
    )

    (:predicates
        (bus_en ?b   - bus     ?p - parada)
        (per_en ?per - persona ?p - parada)
        (per_sent ?per - persona ?s - seient)
        (desti  ?per - persona ?p - parada)
        (sei_en ?sei - seient  ?b - bus)
        (pendent  ?p - persona)
        (satisfet ?p - persona)
    )

    (:action pujar_bus_normal
        :parameters (?b - bus ?per - pNormal ?p - parada ?s - sNormal)
        :precondition (and (pendent ?per)
                           (bus_en  ?b   ?p)
                           (per_en  ?per ?p)
                           (sei_en  ?s   ?b)
                           (> (seientsN  ?b) 0)
        )
        :effect (and (per_sent ?per    ?s)
                     (not (per_en ?per ?p))
                     (not (pendent     ?per))
                     (decrease (seientsN ?b) 1)
        )
    )

    (:action pujar_bus_reduida
        :parameters (?b - bus ?per - pMovilRedu ?p - parada ?s - sMovilRedu)
        :precondition (and (pendent ?per)
                           (bus_en  ?b   ?p)
                           (per_en  ?per ?p)
                           (sei_en  ?s   ?b)
                           (> (seientsR  ?b) 0)
        )
        :effect (and (per_sent ?per    ?s)
                     (not (per_en ?per ?p))
                     (not (pendent     ?per))
                     (decrease (seientsR ?b) 1)
        )
    )

    (:action baixar_bus_normal
        :parameters (?b - bus ?per - persona ?s - seient ?p - parada)
        :precondition (and (bus_en ?b ?p)
                           (per_sent ?per ?s)
                           (not (pendent ?per))     ;; està dintre del bus
                           (desti ?per ?p)
        )
        :effect (and (satisfet ?per)
                     (not (per_sent ?per ?s))
                     (increase (seientsN ?b) 1)
        )
    )

    (:action baixar_bus_reduit
        :parameters (?b - bus ?per - persona ?s - seient ?p - parada)
        :precondition (and (bus_en ?b ?p)
                           (per_sent ?per ?s)
                           (not (pendent ?per))     ;; està dintre del bus
                           (desti ?per ?p)
        )
        :effect (and (satisfet ?per)
                     (not (per_sent ?per ?s))
                     (increase (seientsR ?b) 1)
        )
    )

    (:action moure_bus
        :parameters (?b - bus ?p1 - parada ?p2 - parada)
        :precondition (bus_en ?b ?p1)
        :effect (and  (bus_en ?b ?p2)
                      (not (bus_en ?b ?p1))
        )
    )
)
