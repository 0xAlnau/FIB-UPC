myMap :: (a -> b) -> [a] -> [b]
myMap f ll = [f x | x <- ll]


myFilter :: (a -> Bool) -> [a] -> [a]
myFilter cond ll = [x | x <- ll, cond x]


myZipWith :: (a -> b -> c) -> [a] -> [b] -> [c]
myZipWith op l1 l2 = [op x y | (x, y) <- zip l1 l2]


thingify :: [Int] -> [Int] -> [(Int, Int)]
thingify l1 l2 = [(x,y) | x <- l1, y <- l2, mod x y == 0]


factors :: Int -> [Int]
factors x = [d | d <- [1..x], mod x d == 0]
