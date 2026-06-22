eql :: [Int] -> [Int] -> Bool
eql l1 l2 = (l1 == l2)


prod :: [Int] -> Int
prod l = foldl (*) 1 l


prodOfEvens :: [Int] -> Int
prodOfEvens l =
    let evens = filter even l
    in prod evens


powersOf2 :: [Int]
powersOf2 = iterate (*2) 1


scalarProduct :: [Float] -> [Float] -> Float
scalarProduct l1 l2 =
    let mult = zipWith (*) l1 l2
    in sum mult
