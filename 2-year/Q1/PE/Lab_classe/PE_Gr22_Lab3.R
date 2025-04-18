## ===========================================
## Probabilitat i Estadística, Grup 22
## 11.10.2024: Análisis descriptivo univariado
## ===========================================

## 1. Importar los datos de DatosPE_2024_limpios.txt con la función read.table().
## ----------------------------------------------------------------------------
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
## Todos los datos
table(datosPE$Edat)
mean(datosPE$Edat)
median(datosPE$Edat)
sd(datosPE$Edat)
range(datosPE$Edat)

## Grupo 22
table(grup22$Edat)
mean(grup22$Edat)
median(grup22$Edat)
sd(grup22$Edat)
range(grup22$Edat)


## 4. ¿Cuáles son la media, la mediana y la desviación estándar
##    de la altura y las pulsaciones por minuto? ¿Qué observáis?
## -------------------------------------------------------------
mean(datosPE$Altura)
median(datosPE$Altura)
sd(datosPE$Altura)
range(datosPE$Altura)

## En caso de la variable Pols faltan algunos datos
mean(datosPE$Pols, na.rm = TRUE)
median(datosPE$Pols, na.rm = TRUE)
sd(datosPE$Pols, na.rm = TRUE)
range(datosPE$Pols, na.rm = TRUE)

## Un valor no parece correcto
max(datosPE$Pols, na.rm = TRUE)
## ==> Lo declaramos valor perdido
datosPE$Pols[datosPE$Pols == 186] <- NA

mean(datosPE$Pols, na.rm = TRUE)
median(datosPE$Pols, na.rm = TRUE)
sd(datosPE$Pols, na.rm = TRUE)
range(datosPE$Pols, na.rm = TRUE)


## 5. Cálculo de algunos cuantiles de las variables Altura y Casa2Fib.
##    ¿Cómo se pueden interpretar estos valores?
## -------------------------------------------------------------------
quantile(datosPE$Altura)
quantile(datosPE$Casa2Fib, 1:9 / 10)



## 6. Histogramas de las variables Altura y Casa2Fib.
##    ¿Qué observáis?
## ---------------------------------------------------
x11s(width = 12)             # Usar quartz() en Mac o x11() en Linux.
par(mfrow = 1:2, las = 1, font.lab = 4, font.axis = 2)
hist(datosPE$Altura, breaks = 10, xlab = "Altura [cm]",
     main = "Histograma de la altura", col = 3)
hist(datosPE$Casa2Fib, breaks = 10, xlab = "Minutos",
     main = "Tiempo desde la casa a la FIB", col = "steelblue")

# Más colores:
colors()


## 7. Boxplots de las variables Altura y Casa2Fib.
## ------------------------------------------------
windows(width = 12)
par(mfrow = 1:2, las = 1, font.lab = 2, font.axis = 2)
boxplot(datosPE$Altura, ylab = "Altura [cm]",
        main = "Boxplot de la altura", col = 3)
boxplot(datosPE$Casa2Fib, ylab = "Minutos",
        main = "Boxplot del Tiempo desde la casa a la FIB", col = "steelblue")


## 7. Diagrama de barras de la variable Número de hermanos.
## --------------------------------------------------------
table(datosPE$Germans)
windows()
par(las = 1, font.lab = 2, font.axis = 2)
...(table(datosPE$Germans), col = 1:6, xlab = "Número de hermanos")

## Dibujad el diagrama de barras de la variable Edad. ¿Es un buen gráfico?
windows()
par(las = 1, font.lab = 2, font.axis = 2)



## 8. ¿Cuál es el porcentaje de seguidores del Barça en los grupos 12, 13 y 22?
## ----------------------------------------------------------------------------
# install.packages("descr")
library(descr)
...(datosPE$Equip, plot = FALSE)


## 9. Tabla de frecuencia de los meses de nacimiento.
## --------------------------------------------------
freq(datosPE$Mes, plot = FALSE)
datosPE$Mes <- ...(datosPE$Mes,
                      levels = c("Gener", "Febrer", "Març", "Abril", "Maig",
                                 "Juny", "Juliol", "Agost", "Setembre",
                                 "Octubre", "Novembre", "Desembre"))

freq(datosPE$Mes)


## 10. Guardar el data frame "datosPE" en un área de trabajo de R.
## ---------------------------------------------------------------
