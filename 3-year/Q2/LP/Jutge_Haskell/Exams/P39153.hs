import Data.Ratio

fact :: Integer -> Integer
fact 0 = 1
fact n = n * fact (n-1)

exps2 :: Rational -> Integer -> [Rational]
exps2 x e = num : exps2 x (e+1)
    where
        n = numerator x
        d = denominator x
        num = (n^e) % ((fact e) * (d^e))

exps :: Rational -> [Rational]
exps r = exps2 r 0


exponencial :: Rational -> Rational -> Rational
exponencial r eps = sum llista
    where
        llista = takeWhile (\x -> x >= eps) (exps r)
