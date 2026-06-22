data Temps = Temps Int Int

data Arbre a = Arbre a [Arbre a]

instance Show Temps where
    show (Temps h m) =
        let
            midaH = if h <= 9 then "0" else ""
            midaM = if m <= 9 then "0" else ""
        in
            midaH ++ show h ++ ":" ++ midaM ++ show m

toInt :: String -> Int
toInt s = read s

toTemps :: [Int] -> Temps
toTemps ([h,m]) = Temps h m

suma :: Temps -> Temps -> Temps
suma (Temps h1 m1) (Temps h2 m2) =
    let
        sumaM = m1 + m2
        h3 = if (sumaM < 60) then h1 + h2 else h1 + h2 + 1
        m3 = if (sumaM < 60) then sumaM else (sumaM - 60)
    in
        Temps h3 m3


sumes :: [Temps] -> Temps
sumes = foldl (\x y -> suma x y) (Temps 0 0)


sumesArbres2 :: [Arbre Temps] -> [Temps]
sumesArbres2 [] = []
sumesArbres2 (x:xs) = sumesArbre x : sumesArbres2 xs

sumesArbre :: Arbre Temps -> Temps
sumesArbre (Arbre n []) = n
sumesArbre (Arbre n fills) =
    let
         llistaSumes = sumesArbres2 fills
    in
        suma n (sumes llistaSumes)


main :: IO ()
main = do
    linia <- getLine
    let linia2 = words linia
    let temps = map (map (\x -> if x == ':' then ' ' else x)) linia2
    let numStrings = map words temps
    let nums = map (map toInt) numStrings
    let tempsFinals = map toTemps nums
    let sumacio = sumes tempsFinals
    print sumacio
