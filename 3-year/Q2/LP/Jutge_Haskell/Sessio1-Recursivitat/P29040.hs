insert :: [Int] -> Int -> [Int]
insert [] x = [x]
insert (x:xs) e
    | e <= x    = e : x : xs
    | otherwise = x : insert xs e


isort :: [Int] -> [Int]
isort l = auxIsort l []
--aux for isort
auxIsort :: [Int] -> [Int] -> [Int]
auxIsort [] _ = []
auxIsort (x:xs) l_ord =
    let l_ord2 = insert l_ord x
        result = auxIsort xs l_ord2
    in
        if (result == []) then l_ord2
        else result


remove :: [Int] -> Int -> [Int]
remove [] _ = []
remove (x:xs) e
    | x == e    = xs
    | otherwise = x : remove xs e


ssort :: [Int] -> [Int]
ssort [] = []
ssort l =
    let minim       = minimum l
        l_nou       = remove l minim
        l_nou_ord   = ssort l_nou
    in
        minim : l_nou_ord


merge :: [Int] -> [Int] -> [Int]
merge [] l2 = l2
merge l1 [] = l1
merge (x1:xs1) (x2:xs2)
    | x1 <= x2  = x1 : merge (xs1) (x2:xs2)
    | otherwise = x2 : merge (x1:xs1) (xs2)


msort :: [Int] -> [Int]
msort [] = []
msort [x] = [x]
msort xs =
    let meitat  = div (length xs) 2
        (m1,m2) = splitAt meitat xs
    in
        merge (msort m1) (msort m2)

qsort :: [Int] -> [Int]
qsort [] = []
qsort (p:xs) = (qsort menors) ++ [p] ++ (qsort majors)
    where
        menors = [x | x <- xs, x <  p]
        majors = [x | x <- xs, x >= p]


genQsort :: Ord a => [a] -> [a]
genQsort [] = []
genQsort (p:xs) = (genQsort menors) ++ [p] ++ (genQsort majors)
    where
        menors = [x | x <- xs, x <  p]
        majors = [x | x <- xs, x >= p]
