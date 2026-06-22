myLength :: [Int] -> Int
myLength [] = 0
myLength (x:xs) = 1 + myLength xs


myMaximum :: [Int] -> Int
myMaximum [] = -100000
myMaximum (x:xs) = max x (myMaximum xs)


average :: [Int] -> Float
average l =
    let sumaL = suma l
        mida  = myLength l
    in
        fromIntegral sumaL / fromIntegral mida
--aux for average
suma :: [Int] -> Int
suma [] = 0
suma (x:xs) = x + suma xs


buildPalindrome :: [Int] -> [Int]
buildPalindrome l = reverse l ++ l


remove :: [Int] -> [Int] -> [Int]
remove [] _ = [] --si no tinc elements ja a la llista
remove l [] = l  --si no hi ha elements a eliminar
remove (x:xs) r
    | elem x r  = remove xs r
    | otherwise = x : remove xs r


flatten :: [[Int]] -> [Int]
flatten l = concat l


oddsNevens :: [Int] -> ([Int],[Int])
oddsNevens [] = ([],[])
oddsNevens (x:xs) =
    let tupla = oddsNevens xs
        odds  = fst tupla
        evens = snd tupla
    in
        if (mod x 2 == 0)
        then (odds, x : evens)
        else (x : odds, evens)


primeDivisors :: Int -> [Int]
primeDivisors 1 = []
primeDivisors 2 = [2]
primeDivisors x = primeDivisorsAux 2 x
--aux for primeDivisors
primeDivisorsAux :: Int -> Int -> [Int]
primeDivisorsAux d x
    | mod x d == 0 && isPrime d = d : primeDivisorsAux (d+1) (div x d)
    | d == x                    = []
    | d > x                     = []
    | otherwise                 = primeDivisorsAux (d+1) x
--aux for primeDivisorsAux
isPrime :: Int -> Bool
isPrime 1 = False
isPrime 2 = True --  d x
isPrime x = auxPrime 2 x
--auxiliar function for isPrime
auxPrime :: Int-> Int -> Bool
auxPrime d x
    | d*d <= x = if (mod x d == 0) then False else auxPrime (d+1) x
    | otherwise = True


