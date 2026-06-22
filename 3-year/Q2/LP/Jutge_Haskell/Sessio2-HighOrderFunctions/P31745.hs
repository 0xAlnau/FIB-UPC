flatten :: [[Int]] -> [Int]
flatten ls = concatMap id ls


myLength :: String -> Int
myLength s = length s


myReverse :: [Int] -> [Int]
myReverse l = reverse l


countIn :: [[Int]] -> Int -> [Int]
countIn ls x =
    let
        xs = map (\l -> filter (== x) l) ls
    in
        map (\y -> length y) xs


firstWord :: String -> String
firstWord s =
    let
        treure_pre = dropWhile (\x -> x == ' ') s
    in
        takeWhile (\x -> elem x ['A'..'Z'] || elem x ['a'..'z']) treure_pre
