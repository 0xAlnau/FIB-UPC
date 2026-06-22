(define (problem viatgesProblem)
    (:domain viatges)

    (:objects Barcelona Paris Roma Florencia Berlin Stuttgart - ciutat
              hotel_vela hotel_eiffel hotel_vatica hotel_art hotel_mur hotel_cervesa - hotel
    )

    (:init
        (= (minimCiutats) 4)
        (= (ciutatsVisitades) 0)
        (vol Paris Roma)
        (vol Paris Stuttgart)
        (vol Paris Barcelona)
        (vol Barcelona Paris)
        (vol Barcelona Florencia)
        (vol Roma Barcelona)
        (vol Roma Berlin)
        (vol Florencia Roma)
        (vol Florencia Barcelona)
        (vol Florencia Berlin)
        (vol Berlin Roma)
        (vol Berlin Stuttgart)
        (vol Stuttgart Florencia)
        (vol Stuttgart Berlin)
        (hotel_a hotel_vela Barcelona)
        (hotel_a hotel_eiffel Paris)
        (hotel_a hotel_cervesa Stuttgart)
        (hotel_a hotel_mur Berlin)
        (hotel_a hotel_vatica Roma)
        (hotel_a hotel_art Florencia)
    )

    (:goal (>= (ciutatsVisitades) (minimCiutats)) )
)
