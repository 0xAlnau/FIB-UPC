## ==========================================
## Probabilitat i Estad?stica, Grup 22
## 18.10.2024: An?lisis descriptivo bivariado
## Ejercicios
## ==========================================

## Cargamos el ?rea de trabajo datosPE.RData.
## ------------------------------------------
load("datosPE.RData")
ls()
summary(datosPE)
class(datosPE)

## Variable types
sapply(datosPE, class)


## Posibles preguntas de inter?s:
## * ?Existe una relaci?n entre las pulsaciones por minuto y la altura o
##   las horas dedicadas al deporte?
## * ?Practican m?s deporte las personas a las que les gusta el f?tbol?
## * ?Hay alguna asociaci?n entre vivir fuera de Barcelona y tener el
##   carnet de conducir?


## ======================
## Gr?ficos de dispersi?n
## ======================
## Ejemplo: Resultados del decathlon ol?mpico de Atenas.
## -----------------------------------------------------
library(FactoMineR)
data(decathlon)
athens2004 <- subset(decathlon, Competition == "OlympicG",
                                select = -c(Rank, Competition))
names(athens2004) <- c("M100", "Longjump", "Shotput", "Highjump", "M400",
                       "Hurdle110m", "Discus", "Polevault", "Javeline", "M1500",
                       "Points")
head(athens2004)

## Matriz de gr?ficos de dispersi?n
windows(width = 12, height = 9)
par(las = 1, font = 2)
...(athens2004, main = "Scatterplot Matrix of Decathlon in Athens 2004",
      pch = 19, col = "blue", upper.panel = NULL)

## Gr?fico de dispersi?n entre 100 metros lisos y salto de longitud
X11(width = 9)
par(las = 1, font = 2, font.lab = 4, font.axis = 2)
##pairs o plot
plot(Longjump ~ M100, athens2004, main = "Salto de longitud vs 100m lisos",
     pch = 19, col = "blue", xlab = "100m lisos [seg.]",
     ylab = "Salto de longitud [m]", cex = 1.2)


## ==========================
## Correlaciones (de Pearson)
## ==========================
## Salto de longitud vs 100 metros lisos
with(athens2004, cor(Longjump, M100))
## Todas las correlaciones
round(cor(athens2004), 3)


## Ejercicio 1.
## ------------
## Dibujar gr?ficos de dispersi?n para pulsaciones versus altura y
## pulsaciones versus horas de deporte semanales.
## ?Se observa alguna relaci?n? ?Cu?les son las correlaciones?
## ---------------------------------------------------------------
X11(width = 12)
par(mfrow = 1:2, las = 1, font.lab = 4, font.axis = 2)
plot(Altura ~ Pols, datosPE, main = "Altura vs Pols",
     pch = 19, col = "blue", xlab = "Polsacions",
     ylab = "Altura [cm]", cex = 1.2)

plot(Esport ~ Pols, datosPE, main = "Esport vs Pols",
     pch = 19, col = "blue", xlab = "Polsacions",
     ylab = "Esport", cex = 1.2, ylim=c(0,20))
title("Pulso en funci?n de la altura")

## Las correlaciones:



## Ejercicio 2.
## ------------
## Dibujar boxplots para analizar la relaci?n entre la dedicaci?n al
## deporte y la variable F?tbol.
## Usar, adem?s, la funci?n tapply() para calcular media y desviaci?n
## est?ndar de la variable Esport en funci?n de la variable F?tbol.
## ------------------------------------------------------------------
windows(width = 8)
par(las = 1, font.lab = 4, font.axis = 2)
boxplot(...,
        xlab = "?Te gusta el f?tbol?",
        ylab = "Horas", col = 2:3, cex = 1.5)
title("Horas de depote semanales")

? tapply
with(datosPE, tapply(...))
with(datosPE, tapply(...))


## =====================
## Tabla de contingencia
## =====================
## Relaci?n entre las variables Windows y Futbol.
## ----------------------------------------------
library(descr)
with(datosPE, CrossTable(Windows, Futbol, prop.c = FALSE, prop.t = FALSE,
                         prop.chisq = FALSE, format = "SPSS"))

## ===================
## Gr?fico de mosaicos
## ===================
windows(width = 8)
par(las = 1, font.lab = 4)
mosaicplot(SO ~ Futbol, data = datosPE, col = c("tomato", "steelblue"),
           main = "F?tbol versus Sistema Operativo",
           xlab = "Sistema operativo",
           ylab = "?Te gusta el f?tbol?", cex.axis = 1.2)

## Ejercicio 3.
## ------------
## Estudiar la relaci?n entre vivir fuera de Barcelona y tener el carnet de
## conducir mediante una tabla de contingencia y un gr?ficos de mosaicos.
## ?Qu? observ?is?
## ------------------------------------------------------------------------
## Tabla de contingencia
with(datosPE, CrossTable(...))

## Gr?fico de mosaicos
windows(width = 8)
par(las = 1, font.lab = 4)
mosaicplot(...,
           main = "Carnet versus Ciudad de residencia",
           xlab = "Barcelona",
           ylab = "Carnet", cex.axis = 1.2)
