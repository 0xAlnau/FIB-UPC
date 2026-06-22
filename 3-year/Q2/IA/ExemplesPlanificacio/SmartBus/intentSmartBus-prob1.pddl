(define (problem SmartBus)
   (:domain SmartBus)
   (:objects Sbus027 - bus
             a01 a02 a03 a04 a05 a06 a07 a08 a09 a10 a11 a12 a13 a14 - seient
             a01 a02 a03 a04 a05 a06 a07 a08 a11 a12 a13 a14 - sNormal
             a09 a10 - sMovilRedu
             p2701 p2702 p2703 p2704 p2705 p2706 p2707 p2708 p2709 p2710 p2711 p2712 p2713 p2714 - parada
             Esteban Cristina Daniel Luis Lorena Jesus Raul Maria Estela
             Martina Noelia Pau Jordi Susana Beatriz Ruth - pNormal
             Sebas Xavier Alba Kilian Fabiola - pMovilRedu
    )

  (:init
    (per_en Esteban p2701) (desti Esteban p2703) (pendent Esteban)
    (per_en Cristina p2707) (desti Cristina p2712) (pendent Cristina)
    (per_en Daniel p2714) (desti Daniel p2710) (pendent Daniel)
    (per_en Luis p2711) (desti Luis p2705) (pendent Luis)
    (per_en Lorena p2703) (desti Lorena p2707) (pendent Lorena)
    (per_en Jesus p2703) (desti Jesus p2708) (pendent Jesus)
    (per_en Raul p2701) (desti Raul p2705) (pendent Raul)
    (per_en Maria p2713) (desti Maria p2708) (pendent Maria)
    (per_en Estela p2706) (desti Estela p2711) (pendent Estela)
    (per_en Sebas p2712) (desti Sebas p2710) (pendent Sebas)
    (per_en Martina p2701) (desti Martina p2711) (pendent Martina)
    (per_en Noelia p2707) (desti Noelia p2705) (pendent Noelia)
    (per_en Pau p2704) (desti Pau p2710) (pendent Pau)
    (per_en Xavier p2703) (desti Xavier p2705) (pendent Xavier)
    (per_en Alba p2703) (desti Alba p2707) (pendent Alba)
    (per_en Beatriz p2703) (desti Beatriz p2708) (pendent Beatriz)
    (per_en Jordi p2706) (desti Jordi p2705) (pendent Jordi)
    (per_en Kilian p2713) (desti Kilian p2708) (pendent Kilian)
    (per_en Fabiola p2706) (desti Fabiola p2710) (pendent Fabiola)
    (per_en Susana p2714) (desti Susana p2710) (pendent Susana)
    (per_en Ruth p2706) (desti Ruth p2710) (pendent Ruth)

    (sei_en a01 Sbus027) (sei_lliure a01)
    (sei_en a02 Sbus027) (sei_lliure a02)
    (sei_en a03 Sbus027) (sei_lliure a03)
    (sei_en a04 Sbus027) (sei_lliure a04)
    (sei_en a05 Sbus027) (sei_lliure a05)
    (sei_en a06 Sbus027) (sei_lliure a06)
    (sei_en a07 Sbus027) (sei_lliure a07)
    (sei_en a08 Sbus027) (sei_lliure a08)
    (sei_en a09 Sbus027) (sei_lliure a09)
    (sei_en a10 Sbus027) (sei_lliure a10)
    (sei_en a11 Sbus027) (sei_lliure a11)
    (sei_en a12 Sbus027) (sei_lliure a12)
    (sei_en a13 Sbus027) (sei_lliure a13)
    (sei_en a14 Sbus027) (sei_lliure a14)

    (bus_en Sbus027 p2701)
  )

  (:goal (forall (?p - persona) (satisfet ?p)))
)
