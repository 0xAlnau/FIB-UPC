divisors :: Int -> [Int]
divisors v = [x | x <- [1..v], v `mod` x == 0]


nbDivisors :: Int -> Int
nbDivisors = length . divisors


moltCompost :: Int -> Bool
moltCompost v = res
    where
        llista = [nbDivisors x < nbDivisors v | x <- [1..(v-1)]]
        res = not (elem False llista)
