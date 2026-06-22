import Data.List

degree :: Eq a => [(a, a)] -> a -> Int
degree [] _ = 0
degree ((x,y):g) n
    | x == n    = 1 + degree g n
    | y == n    = 1 + degree g n
    | otherwise = degree g n


degree' :: Eq a => [(a, a)] -> a -> Int
degree' g n = sum $ map (\(x,y) -> if (x == n || y == n) then 1 else 0) g


neighbors :: Ord a => [(a, a)] -> a -> [a]
neighbors g n = filter (\v -> v /= n) $ sort $ map (\(x,y) -> if x == n then y else if y == n then x else n) g
