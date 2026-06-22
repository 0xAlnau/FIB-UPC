; ==============================================================================
; 1. PLANTILLES
; ==============================================================================
(deftemplate persona
   (slot nom (type STRING))
   (slot edat (type INTEGER))
   (slot dni (type STRING))
)

; ==============================================================================
; 2. FETS INICIALS
; ==============================================================================
; Ahora solo cargamos las personas en el sistema, pero NO hay ningún cumpleaños inicial.
(deffacts fets-inicials
   (persona (nom "Joan") (edat 25) (dni "12345678A"))
   (persona (nom "Maria") (edat 30) (dni "87654321B"))
)

; ==============================================================================
; 3. REGLA DE INTERACCIÓN (NUEVA)
; ==============================================================================
(defrule preguntar-aniversari
   "Aquesta regla pregunta a l'usuari quin DNI fa anys"
   (declare (salience 10)) ; Le damos prioridad alta para que se ejecute primero [4]
   =>
   ; Imprimimos la pregunta por pantalla [5]
   (printout t "Introdueix el DNI de la persona que fa anys (amb cometes): ")

   ; Leemos lo que escribe el usuario y lo guardamos en una variable [1, 5]
   (bind ?resposta-dni (read))

   ; Introducimos la respuesta en la base de hechos para que active otras reglas [5]
   (assert (aniversari ?resposta-dni))
)

; ==============================================================================
; 4. REGLA DE CÁLCULO (Modificada)
; ==============================================================================
(defrule celebrar-aniversari
   ?fet-aniversari <- (aniversari ?dni-buscat)
   ?fet-persona <- (persona (nom ?nom) (edat ?edat) (dni ?dni-buscat))
   =>
   (retract ?fet-aniversari)
   (modify ?fet-persona (edat (+ 1 ?edat)))
   (printout t "Feliç aniversari " ?nom "! Ara tens " (+ 1 ?edat) " anys." crlf)
)
