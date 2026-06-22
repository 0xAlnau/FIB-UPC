import Data.Ratio

fact :: Integer -> Integer
fact 0 = 1
fact n = n * fact (n-1)

termes_cosinus2 :: Rational -> Integer -> [Rational]
termes_cosinus2 angle n = act : termes_cosinus2 angle (n+1)
    where
        num = ((-1)^n * angle^(2*n)) / (toRational (fact (2*n)))
        act = toRational num

termes_cosinus :: Rational -> [Rational]
termes_cosinus angle = termes_cosinus2 angle 0


cosinus :: Rational -> Rational -> Rational
cosinus angle epsi = suma
    where
        cond = takeWhile (\x -> abs(x) >= epsi) (termes_cosinus angle)
        suma = sum cond
