## ==========================================
## Probabilitat i Estadística, Grup 22
## 3.10.2024: Análisis descriptivo univariado
## ==========================================

## 1. Importar los datos de DatosPE_2024_limpios.txt con la función read.table().
## ------------------------------------------------------------------------------
read.table("DatosPE_2024_limpios.txt", sep = "\t", na.strings = "",
           encoding = "latin1")
datosPE <- read.table("DatosPE_2024_limpios.txt", header = TRUE, sep = "\t",
                      na.strings = "", dec = ",", stringsAsFactors = TRUE,
                      encoding = "latin1")

## El objeto creado es un data frame:
class(datosPE)

## Exploración de los datos.
## -------------------------
str(datosPE)
head(datosPE)
summary(datosPE)

## Alternativa para la importación de datos.
## -----------------------------------------
# datosPE <- read.delim("DatosPE_2024_limpios.txt", header = TRUE,
#                        na.strings = "", dec = ",")


## 2. Creación del subconjunto grup22:
## -----------------------------------
grup22 <- subset(datosPE, Grup == 22)
summary(grup22)


## 3. ¿Cuáles son las medias, medianas y desviaciones estándar de
##    la edad en todo el conjunto de datos y en el grupo 22, resp.?
## ----------------------------------------------------------------
mean(datosPE$Edat)
median(grup22$Edat)
sd(datosPE$Edat)
range(datosPE$Edat)


## 4. ¿Cuáles son la media, la mediana y la desviación estándar
##    de la altura y las pulsaciones por minuto? ¿Qué observáis?
## -------------------------------------------------------------
mean(datosPE$Altura)
mean(datosPE$Pols, na.rm =TRUE)
median(datosPE$Altura)
median(datosPE$Pols)
sd(datosPE$Altura)
sd(datosPE$Pols)


## 5. Histogramas de las variables Altura y Casa2Fib.
##    ¿Qué observáis?
## ---------------------------------------------------
windows(width = 12)             # Usar quartz() en Mac o x11() en Linux.
par(mfrow = 1:2, las = 1, font.lab = 4, font.axis = 2)
hist(datosPE$Altura, breaks = 10, xlab = "Altura [cm]",
     main = "Histograma de la altura [Grupos 21 y 22]", col = 3)
hist(datosPE$Casa2Fib, breaks = 10, xlab = "Minutos",
     main = "Tiempo desde la casa a la FIB", col = "steelblue")
