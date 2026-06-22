(define (domain SmartBus)
    (:requirements :adl :typing)

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
        (sei_lliure ?sei - seient)
        (pendent  ?p - persona)
        (satisfet ?p - persona)
    )

    (:action pujar_bus_normal
        :parameters (?b - bus ?per - pNormal ?p - parada ?s - sNormal)
        :precondition (and (pendent ?per)
                           (bus_en  ?b   ?p)
                           (per_en  ?per ?p)
                           (sei_en  ?s   ?b)
                           (sei_lliure   ?s)
        )
        :effect (and (per_sent ?per    ?s)
                     (not (sei_lliure  ?s))
                     (not (per_en ?per ?p))
                     (not (pendent     ?per))
        )
    )

    (:action pujar_bus_reduida
        :parameters (?b - bus ?per - pMovilRedu ?p - parada ?s - sMovilRedu)
        :precondition (and (pendent ?per)
                           (bus_en  ?b   ?p)
                           (per_en  ?per ?p)
                           (sei_en  ?s   ?b)
                           (sei_lliure   ?s)
        )
        :effect (and (per_sent ?per    ?s)
                     (not (sei_lliure  ?s))
                     (not (per_en ?per ?p))
                     (not (pendent     ?per))
        )
    )

    (:action baixar_bus
        :parameters (?b - bus ?per - persona ?s - seient ?p - parada)
        :precondition (and (bus_en ?b ?p)
                           (per_sent ?per ?s)
                           (not (pendent ?per))     ;; està dintre del bus
                           (desti ?per ?p)
        )
        :effect (and (satisfet ?per)
                     (not (per_sent ?per ?s))
                     (sei_lliure     ?s)
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
