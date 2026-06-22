ones :: [Integer]
ones = 1 : ones


nats :: [Integer]
nats = 0 : map (+1) nats


ints :: [Integer]
ints = 0 : concatMap (\(a,b) -> [a,b]) (zip (iterate (+1) 1) (iterate (\x -> x - 1) (-1)))

triangulars :: [Integer]
triangulars = map (\x -> div (x*(x + 1)) 2) [0..]


factorials :: [Integer]
factorials = 1 : 1 : 2 : zipWith (*) (tail $ tail factorials) [3..]

fibs :: [Integer]
fibs = 0 : 1 : 1 : zipWith (+) (tail fibs) (tail $ tail fibs)


primes :: [Integer]
primes = garbell [2..]
    where garbell (p: xs) = p : garbell [x | x <- xs, x `mod` p /= 0]


merge :: [Integer] -> [Integer] -> [Integer]
merge (x:xs) (y:ys)
    | x < y     = x : merge xs (y:ys)
    | x > y     = y : merge (x:xs) ys
    | otherwise = x : merge xs ys  -- Si x == y, posem x

hammings :: [Integer]
hammings = 1 : merge (map (*2) hammings) (merge (map (*3) hammings) (map (*5) hammings))


nextStr :: String -> String
nextStr [] = []
nextStr (c:cs) = show (length iguales) ++ [c] ++ nextStr resto
  where
    (iguales, resto) = span (== c) (c:cs)

nextLook :: Integer -> Integer
nextLook n = read (nextStr (show n))

lookNsay :: [Integer]
lookNsay = iterate nextLook 1


sumTart :: [Integer] -> [Integer]
sumTart (x:y:xs) = [x + y] ++ sumTart (y:xs)
sumTart _ = []

tartaglia2 :: [Integer] -> [Integer]
tartaglia2 l = [1] ++ sumTart l ++ [1]

tartaglia :: [[Integer]]
tartaglia = iterate tartaglia2 [1]
