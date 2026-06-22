(define (domain SmartBusFluents2)
  (:requirements :adl :typing :fluents)

  (:types persona parada SBus - object)           

  (:predicates
   (estacionado ?bus - SBus ?l - parada)
   (dentro ?p - persona ?bus - SBus)
   (destino ?p - persona ?l - parada)
   (en ?p - persona ?l - parada)
   (movilidadReducida ?p)
   (pendiente ?p - persona)
   (servido ?p - persona)
  )

  (:functions
    (butacasLibres ?bus - SBus)
    (plazasMrLibres ?bus - SBus)
  )

  (:action montar_en_SBus
    :parameters (?p - persona ?bus - SBus ?l - parada)
    :precondition (and (pendiente ?p) (en ?p ?l) 
                       (estacionado ?bus ?l)
                       (imply (not (movilidadReducida ?p)) (> (butacasLibres ?bus) 0))
                       (imply (movilidadReducida ?p) (> (plazasMrLibres ?bus) 0))
                   )    
    :effect (and (when (not (movilidadReducida ?p)) (decrease (butacasLibres ?bus) 1))
                 (when (movilidadReducida ?p) (decrease (plazasMrLibres ?bus) 1))
		 (dentro ?p ?bus)
                 (not (en ?p ?l)) (not (pendiente ?p))
            )
  )
  
  (:action bajar_de_SBus
    :parameters (?p - persona ?bus - SBus ?l - parada)
    :precondition (and (dentro ?p ?bus) 
                       (estacionado ?bus ?l)
                       (destino ?p ?l) 
                  )
    :effect (and (en ?p ?l) (servido ?p) 
                  (not (dentro ?p ?bus))
                  (when (not (movilidadReducida ?p)) (increase (butacasLibres ?bus) 1))
                  (when (movilidadReducida ?p) (increase (plazasMrLibres ?bus) 1))
            )
  )

  (:action mover_SBus
    :parameters (?bus - SBus ?ori - parada ?des - parada)
    :precondition (estacionado ?bus ?ori)
    :effect (and (estacionado ?bus ?des) (not (estacionado ?bus ?ori))
            )
  )
)