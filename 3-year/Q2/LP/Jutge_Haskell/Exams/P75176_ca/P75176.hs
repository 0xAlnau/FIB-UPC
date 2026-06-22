import Data.Ratio

to_Real :: String -> Rational
to_Real x = read x

myUntil :: (a -> Bool) -> (a -> a) -> a -> a
myUntil p f x = head (dropWhile (\x -> not (p x)) (iterate f x))

egypt :: Rational -> [Rational]
egypt divi
    | numerator divi == 0 = []
    | otherwise           = reverse (snd (myUntil condicio iteracio (divi, [])))
  where
    -- cas base
    condicio (r, _) = numerator r == 0

    -- guardem resultat i concatenem
    iteracio (fracActual, acumulador) =
        let x = numerator fracActual
            y = denominator fracActual
            unitary = 1 % ceiling (y % x)
            r = mod (-y) x % (y * ceiling (y % x))
        in (r, unitary : acumulador)


main :: IO ()
main = do
    content <- getContents -- [linia1 \n linia2 \n ...]
    let llistaLinies = lines content -- [linia1, linia2, ...]
    let llistaString = map words llistaLinies --cada linia es ["num", "%", "deno"]
    let llistaConcatInt = map concat llistaString
    let llistaAmbPar = map (\x -> "(" ++ x ++ ")") llistaConcatInt
    let llistaReadReals = map (to_Real) llistaAmbPar
    let llistaEgypt = map egypt llistaReadReals
    mapM_ print llistaEgypt
