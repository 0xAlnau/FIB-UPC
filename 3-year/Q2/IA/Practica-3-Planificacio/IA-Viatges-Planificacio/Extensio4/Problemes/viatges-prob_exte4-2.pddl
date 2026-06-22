(define (problem viatgesProblemExt4_2)
    (:domain viatges)

    (:objects
        Madrid Londres Amsterdam Viena Praga - ciutat
        h_mad h_lon h_ams h_vie h_pra - hotel
    )

    (:init
        (= (minimCiutats) 3)
        (= (ciutatsVisitades) 0)
        (= (minDiesPerCiutat) 1)
        (= (maxDiesPerCiutat) 3)
        (= (minimDiesRuta) 4)
        (= (diesEnRuta) 0)

        (= (costTotal) 0)
        (= (pressupostMin) 100)
        (= (pressupostMax) 800)
        (= (interesTotal) 0)

        (= (diesEnCiutat Madrid) 0)
        (= (diesEnCiutat Londres) 0)
        (= (diesEnCiutat Amsterdam) 0)
        (= (diesEnCiutat Viena) 0)
        (= (diesEnCiutat Praga) 0)

        (= (interes Londres) 1)
        (= (interes Viena) 1)
        (= (interes Amsterdam) 2)
        (= (interes Madrid) 3)
        (= (interes Praga) 3)

        (vol Madrid Londres) (vol Londres Madrid)
        (vol Londres Amsterdam) (vol Amsterdam Londres)
        (vol Amsterdam Viena) (vol Viena Amsterdam)
        (vol Viena Praga) (vol Praga Viena)
        (vol Praga Madrid) (vol Madrid Praga)
        (vol Madrid Viena) (vol Viena Madrid)

        (hotel_a h_mad Madrid)
        (hotel_a h_lon Londres)
        (hotel_a h_ams Amsterdam)
        (hotel_a h_vie Viena)
        (hotel_a h_pra Praga)

        ; Viajar a las ciudades interesantes (Londres/Viena) es muy caro
        (= (costVol Madrid Londres) 120) (= (costVol Londres Madrid) 120)
        (= (costVol Londres Amsterdam) 90) (= (costVol Amsterdam Londres) 90)
        (= (costVol Amsterdam Viena) 110) (= (costVol Viena Amsterdam) 110)
        (= (costVol Viena Praga) 50) (= (costVol Praga Viena) 50)
        (= (costVol Praga Madrid) 40) (= (costVol Madrid Praga) 40)
        (= (costVol Madrid Viena) 150) (= (costVol Viena Madrid) 150)

        (= (costHotel h_mad) 40)
        (= (costHotel h_lon) 130)
        (= (costHotel h_ams) 80)
        (= (costHotel h_vie) 110)
        (= (costHotel h_pra) 30)
    )

    (:goal (and
        (>= (ciutatsVisitades) (minimCiutats))
        (>= (diesEnRuta) (minimDiesRuta))
        ; Implicación condicional: si se visita, se cumple el mínimo de días
        (forall (?c - ciutat) (imply (usuari_a ?c) (>= (diesEnCiutat ?c) (minDiesPerCiutat))))
        (<= (costTotal) (pressupostMax))
        (>= (costTotal) (pressupostMin))
    ))

    (:metric minimize (+ (* 10 (costTotal)) (* 1 (interesTotal))))
)
