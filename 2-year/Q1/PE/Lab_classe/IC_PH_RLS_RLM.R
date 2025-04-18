## =============================
## Probabilitat i Estad?stica
## Grupo 22, Bloque D, 5.12.2024
## Modelos de regresi?n lineal
## =============================
## Notas:
## * Si us?is Mac, sustituir windows() por quartz()
## * Si us?is Linux, sustituir windows() por x11()

## ---------------------------
## (I) Regresi?n lineal simple
## ---------------------------
## (A) Los datos de la Bundesliga (hasta la temporada 2015/16)
## -----------------------------------------------------------
buliga <- readRDS("Bundesliga.rds")

## El peor equipo de toda la historia de la Bundesliga
## (https://es.wikipedia.org/wiki/SC_Tasmania_1900_Berl%C3%ADn)
## ------------------------------------------------------------
subset(buliga, Season == "1965-1966" & Position == 18)

## El a veces mejor equipo de la Bundesliga
## (https://es.wikipedia.org/wiki/VfB_Stuttgart)
## ---------------------------------------------
subset(buliga, Season %in% c("1983-1984", "1991-1992", "2006-2007") &
               Position == 1)

## Datos desde 1995 (3 puntos por victoria)
## ----------------------------------------
trespunts <- buliga[575:nrow(buliga), ]
windows(width = 8)
par(las = 1, font = 2, font.axis = 2, font.lab = 2)
with(trespunts, plot(Points ~ GF, pch = 16,
                      xlab = "Goles a favor", ylab = "Puntos"))
title("Puntos por temporada vs. Goles marcados")
## La siguiente instrucci?n incluye la recta de regresi?n en el gr?fico
abline(0, 1, lwd = 3)


## El modelo de regresi?n lineal simple: Puntos ~ Goles a favor
## ------------------------------------------------------------
## Estimaci?n de los par?metros mediante la funci?n lm()
## -----------------------------------------------------
lmod <- lm(Points ~ GF, data = trespunts)
lmod
summary(lmod)
print(summary(lmod), signif.stars = FALSE)


## ---------------------------------------------
## (B) Los datos de 6 grupos de PE (2024/25; Q1)
## ---------------------------------------------
## (a) Dibujar un gr?fico de dispersi?n de las pulsaciones por minuto versus
## horas de deporte semanales (usando todos los datos).
## Hay una relaci?n lineal?
## ----------------------------------------------------------------------------
x11(width = 8)
par(las = 1, font.lab = 4, font.axis = 2)
plot(...)


## Modelo de regresi?n lineal para "Pulso versus actividad deportiva".
## -------------------------------------------------------------------
lmod2 <- lm(Pols ~ Esport, data = datosPE)
print(summary(lmod2), signif.stars = FALSE)

## (a) Interpretar los valores de la constante y la pendiente del modelo.
## ----------------------------------------------------------------------


## (b) Calcular el IC del 95% de la pendiente del modelo.
## ------------------------------------------------------


## (c) ?Se puede concluir que el pulso depende de la actividad deportiva?
## ----------------------------------------------------------------------
## No (con nivel de significaci?n 0.05), ya que el IC contiene a 0.


## -----------------------------
## (II) Datos sobre "gender gap"
## -----------------------------
## For information on the data, see
## https://equal4europe.eu/wp-content/uploads/2021/09/Tool-for-Comparing-Institutional-Results-in-Gender-Equality.pdf
gengap <- readRDS("GenderGap.RDS")
head(gengap)
summary(gengap)

## (a) Gr?fico de dispersi?n de salario (total) versus edad.
## ---------------------------------------------------------
windows(width = 8)
par(las = 1, font.lab = 4, font.axis = 2, font = 2)
plot(totalPay ~ age, data = gengap, pch = 16, xlab = "Age",
     ylab = "", col = as.numeric(gender) + 1)
title("Base plus bonus pay versus age of employees")
legend("topleft", levels(gengap$gender), col = 2:3, bty = "n", pch = 16)
## Rectas de regresi?n
abline(lm(totalPay ~ age, data = subset(gengap, gender == "Female")),
       col = 2, lwd = 2)
abline(lm(totalPay ~ age, data = subset(gengap, gender == "Male")),
       col = 3, lwd = 2)

## (b) Modelo de regresi?n lineal m?ltiple: Salario ~ Edad + Sexo
## --------------------------------------------------------------
lmod3 <- lm(totalPay ~ gender + age, gengap)
print(summary(lmod3), signif.stars = FALSE)
