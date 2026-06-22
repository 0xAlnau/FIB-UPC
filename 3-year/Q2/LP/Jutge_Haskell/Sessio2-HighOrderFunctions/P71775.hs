countIf :: (Int -> Bool) -> [Int] -> Int
countIf _ [] = 0
countIf cond (x:xs)
    | cond x    = 1 + countIf cond xs
    | otherwise = countIf cond xs


pam :: [Int] -> [Int -> Int] -> [[Int]]
pam _ [] = []
pam l (f:fs) =
    let
        mapped = map f l
    in
        [mapped] ++ pam l fs


pam2 :: [Int] -> [Int -> Int] -> [[Int]]
pam2 [] _ = []
pam2 (x:xs) fs =
    let
        mapped = aux_pam2 x fs
    in
        [mapped] ++ pam2 xs fs

--aux for pam2
aux_pam2 :: Int -> [Int -> Int] -> [Int]
aux_pam2 _ [] = []
aux_pam2 x (f:fs) = [f x] ++ aux_pam2 x fs


filterFoldl :: (Int -> Bool) -> (Int -> Int -> Int) -> Int -> [Int] -> Int
filterFoldl cond op cb l =
    let
        filtered = filter cond l
    in
        foldl op cb filtered


insert :: (Int -> Int -> Bool) -> [Int] -> Int -> [Int]
insert _ [] num = [num]
insert cond (x:xs) num
    | cond num x = num : x : xs
    | otherwise  = x : insert cond xs num


insertionSort :: (Int -> Int -> Bool) -> [Int] -> [Int]
insertionSort cond l = auxInsertionSort cond l []

--aux for insertionSort
auxInsertionSort :: (Int -> Int -> Bool) -> [Int] -> [Int] -> [Int]
auxInsertionSort _ [] l_ord = l_ord
auxInsertionSort cond (x:xs) l_ord =
    let
        l_ord2 = insert cond l_ord x
    in
        auxInsertionSort cond xs l_ord2
