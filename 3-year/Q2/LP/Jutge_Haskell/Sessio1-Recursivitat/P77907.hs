absValue :: Int -> Int
absValue n
    | n >= 0    = n
    | otherwise = -n


power :: Int -> Int -> Int
power _ 0 = 1
power x p =
    let p_halved = div p 2
        y = power x p_halved
    in
        if even p
        then y * y
        else y * y * x


isPrime :: Int -> Bool
isPrime 0 = False
isPrime 1 = False
isPrime 2 = True --  d x
isPrime x = auxPrime 2 x
--auxiliar function for isPrime
auxPrime :: Int-> Int -> Bool
auxPrime d x
    | d*d <= x = if (mod x d == 0) then False else auxPrime (d+1) x
    | otherwise = True

slowFib :: Int -> Int
slowFib 0 = 0
slowFib 1 = 1
slowFib x = slowFib (x-1) + slowFib (x-2)


quickFib :: Int -> Int
quickFib 0 = 0
quickFib 1 = 1
quickFib x = auxFib 0 1 x 2
--auxiliar function for quickFib
auxFib :: Int -> Int -> Int -> Int -> Int
auxFib n2 n1 x i
    | x == i    = n2 + n1
    | otherwise = auxFib n1 (n1+n2) x (i+1)
