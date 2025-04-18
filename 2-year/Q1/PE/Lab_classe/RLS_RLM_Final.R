## =======================================================
## Probabilitat i Estad?stica
## Grupo 22, Bloque D, 13.12.2024
## M?s informaci?n sobre modelos de regresi?n lineal con R
## =======================================================
## Notas:
## * Si us?is Mac, sustituir windows() por quartz()
## * Si us?is Linux, sustituir windows() por x11()

## Cargar el ?rea de trabajo Recollida_de_dades2.RData
## ===========================================
load("Recollida_de_dades")
ls()
class(Recollida_de_dades)
summary(Recollida_de_dades)

### =========================
### (I) Modelos m?s sencillos
### =========================
## (a) ?Cu?l es el intervalo de confianza de la media del tiempo
## "Horas de deporte semanales" en estudiantes de la FIB?
## =================================================================
## Subconjunto de estudiantes (edad < 29 a?os).
## --------------------------------------------
students <- subset(Recollida_de_dades2, Edat < 29)

## C?lculo del IC del 95%.
## -----------------------
t.test(students$Esport)
round(t.test(students$Esport)$conf.int, 2)

## Uso de la funci?n lm() para calcular IC
## ----------------------
(lmSport <- lm(Esport ~ 1, students))
print(summary(lmSport), signif.stars = FALSE)

## ?Cu?l es la desviaci?n est?ndar de las "Horas de deporte semanales"?
## --------------------------------------------------------------------
sd(students$Esport)

## C?lculo del IC del 95% (II).
## ----------------------------
confint(lmSport)


## (b) ?Cu?l es el intervalo de confianza de la diferencia media de
##     "Horas de deporte semanales" entre estudiantes a los que les gusta
##     el f?tbol a los que no?
## =========================================================================
## IC del 95% (asumiendo homocedasticidad).
## ----------------------------------------
t.test(Esport ~ Futbol, students, var.equal = TRUE)
round(t.test(Esport ~ Futbol, students, var.equal = TRUE)$conf.int, 2)

## Uso de la funci?n lm()
## ----------------------
(lmSport2 <- lm(Esport ~ Futbol, students))
print(summary(lmSport2), signif.stars = FALSE)

## C?lculo del IC del 95% (II).
## ----------------------------
confint(lmSport2)


### ==================================================================
### (II) Comprobaci?n de las premisas de un modelo de regresi?n lineal
### ==================================================================
### Los datos de las diferencias salariales
### ---------------------------------------

Recollida_de_dades2$`Temps(ms)` <- log(Recollida_de_dades2$`Temps(ms)`)
Recollida_de_dades2$`Mida(MB)` <- log(Recollida_de_dades2$`Mida(MB)`)

datos <- Recollida_de_dades2[, 2:4]
wifi <- Recollida_de_dades2[, c(2,4)]
ethernet <- Recollida_de_dades2[, c(2,4)]
wifi <- wifi[1:60,]
ethernet <- ethernet[61:120,]

#Para el wifi
Wlmod <- lm(`Temps(ms)` ~ `Mida(MB)`, data = wifi)
print(summary(Wlmod), signif.stars = FALSE)

windows(width = 12)
par(las = 1, font.lab = 2, font.axis = 2, mfrow = 1:2)
plot(Wlmod, 1:2, ask = FALSE, pch = 16)


windows(width = 8)
par(las = 1, font = 2, font.axis = 2, font.lab = 2)
with(wifi, plot(`Temps(ms)` ~ `Mida(MB)`, pch = 16,
                xlab = "Mida(MB)", ylab = "Temps(ms)"))
title("Temps que tarda en carregar una pàgina en funció del seu tamany amb Wi-fi")
abline(6.5, 0.5, lwd = 3)


##Para el ethernet
Elmod <- lm(`Temps(ms)` ~ `Mida(MB)`, data = ethernet)
print(summary(Elmod), signif.stars = FALSE)

windows(width = 12)
par(las = 1, font.lab = 2, font.axis = 2, mfrow = 1:2)
plot(Elmod, 1:2, ask = FALSE, pch = 16)


windows(width = 8)
par(las = 1, font = 2, font.axis = 2, font.lab = 2)
with(ethernet, plot(`Temps(ms)` ~ `Mida(MB)`, pch = 16,
                xlab = "Mida(MB)", ylab = "Temps(ms)"))
title("Temps que tarda en carregar una pàgina en funció del seu tamany amb Ethernet")
abline(6.5, 0.5, lwd = 3)


##Para el wifi + ethernet
datos$`Wifi(1) / Ethernet(0)` <- as.factor(datos$`Wifi(1) / Ethernet(0)`)
WElmod <- lm(`Temps(ms)` ~ `Wifi(1) / Ethernet(0)` + `Mida(MB)`, data = datos)
print(summary(WElmod), signif.stars = FALSE)

windows(width = 12)
par(las = 1, font.lab = 2, font.axis = 2, mfrow = 1:2)
plot(WElmod, 1:2, ask = FALSE, pch = 16)


windows(width = 8)
par(las = 1, font.lab = 4, font.axis = 2, font = 2)
plot(`Temps(ms)` ~ `Mida(MB)`, data = datos, pch = 16, xlab = "Mida(MB)",
     ylab = "", col = as.numeric(`Wifi(1) / Ethernet(0)`) + 1)
title("El temps que es tarda en descarregar una pàgina web amb Wi-fi(1) i Ethernet(0)")
legend("topleft", levels(datos$`Wifi(1) / Ethernet(0)`), col = 2:3, bty = "n", pch = 16)
abline(lm(`Temps(ms)` ~ `Mida(MB)`, data = wifi),
       col = 1, lwd = 2)
abline(lm(`Temps(ms)` ~ `Mida(MB)`, data = ethernet),
       col = 1, lwd = 2)


#interval confiança (paired data)
Twifi <- wifi[[1]]
Tethernet <- ethernet[[1]]
t.test(Tethernet, Twifi, paired = TRUE)

Tdiff <- Tethernet - Twifi
t.test(Tdiff)

WElmod <- lm(`Temps(ms)` ~ `Wifi(1) / Ethernet(0)` + `Mida(MB)`, data = datos)
print(summary(WElmod), signif.stars = FALSE)

windows(width = 12)
par(las = 1, font.lab = 2, font.axis = 2, mfrow = 1:2)
plot(WElmod, 1:2, ask = FALSE, pch = 16)

## Predicci?n basada en el modelo
## ------------------------------
newdat <- data.frame(age = c(50, 40), gender = c("Female", "Male"))
predict(lmod, newdata = newdat)
predict(lmod, newdata = newdat, interval = "prediction")


### Recollida_de_dades2: Pulso versus horas de deporte
### --------------------------------------
lmod2 <- lm(Pols ~ Esport, Recollida_de_dades2)
print(summary(lmod2), signif.stars = FALSE)

windows(width = 12)
par(las = 1, font.lab = 2, font.axis = 2, mfrow = 1:2)
plot(lmod2, 1:2, ask = FALSE, pch = 16)

