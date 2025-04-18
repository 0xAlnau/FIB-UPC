## ====================================
## Probabilitat i Estadística
## Grupo 22, Bloque D, 5.12.2024
## Gráficos e IC para datos emparejados
## ====================================
## Notas:
## * Si usáis Mac, sustituir windows() por quartz()
## * Si usáis Linux, sustituir windows() por x11()

## Un conjunto de datos emparejados
## =================================
ls()
summary(Recollida_de_dades)
wifi <- Recollida_de_dades$`Wifi (ms)`
ethernet <- Recollida_de_dades$`Ethernet (ms)`
Tdiff <- ethernet - wifi

## Análisis descriptivo
## ====================
summary(wifi)
sd(wifi)

summary(ethernet)
sd(ethernet)

summary(Tdiff)
sd(Tdiff)

## Intervalo de confianza del 95% de mu2 - mu1
## ===========================================

t.test(Tdiff)
t.test(Tdiff-1)
t.test(ethernet, wifi, paired = TRUE)
## Gráficos para representar datos emparejados
## ============================================
## (i) Boxplots
windows(width = 12)
par(mfrow = 1:2, las = 1, font.lab = 2, font.axis = 2)
boxplot(Recollida_de_dades[2:3], ylab = "Segundos", col = c("steelblue", "tomato"),
        main = "Boxplots de los tiempos wifi y ethernet")
boxplot(Tdiff, ylab = "Segundos", xlab = "ethernet-wifi",
        main = "Diferencia de tiempos (ethernet - wifi)", col = 3)
abline(h = 0, lty = 2, lwd = 2)

## (ii) Gráfico de dispersión de ethernet vs wifi
## ======================================
windows()
par(las = 1, font.lab = 4, font.axis = 2)
plot(ethernet ~ wifi, Recollida_de_dades, pch = 19, xlim = c(0, max(wifi, ethernet)),
     ylim = c(0, max(wifi, ethernet)))
abline(0, 1, lwd = 2) #constante i pendiente
text(800, 7000, "ethernet > wifi", font = 2)
text(6500, 400, "wifi > ethernet", font = 2)

## (iii) Bland-Altman plot
## =======================
library(BlandAltmanLeh)
windows()
par(las = 1, font.lab = 4, font.axis = 2)
bland.altman.plot(Recollida_de_dades$'Ethernet (ms)', Recollida_de_dades$'Wifi (ms)', pch = 19,
                  xlab = "Mean", ylab = "ethernet - wifi")
bland.altman.plot(Recollida_de_dades$'Ethernet (ms)', Recollida_de_dades$'Wifi (ms)', donf.int = 0.95, pch = 19,
                  xlab = "Mean", ylab = "ethernet - wifi")
