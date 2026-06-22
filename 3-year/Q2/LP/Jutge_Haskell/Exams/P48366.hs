data Racional = Racional Integer Integer

instance Show Racional where
    show (Racional n d) = (show $ div n m) ++ "/" ++ (show $ div d m)
        where m = gcd n d

instance Eq Racional where
    (Racional n1 d1) == (Racional n2 d2) = n1 * d2 == n2 * d1


data Tree a = Node a (Tree a) (Tree a)

arbreCalkinWilf :: Racional -> Tree Racional
arbreCalkinWilf (Racional n d) = Node (Racional n d) (arbreCalkinWilf x) (arbreCalkinWilf y)
    where
        x = Racional n (n + d)
        y = Racional (n + d) d

recXnivells :: Tree a -> [a]
recXnivells t = recXnivells' [t]
    where recXnivells' ((Node x fe fd):ts) = x:recXnivells' (ts ++ [fe, fd])

racionals :: [Racional]
racionals = recXnivells tree
    where
        tree = arbreCalkinWilf (Racional 1 1)


racional :: Integer -> Integer -> Racional
racional n d = Racional (div n x) (div d x)
    where x = gcd n d

numerador :: Racional -> Integer
numerador (Racional n d) = n

denominador :: Racional -> Integer
denominador (Racional n d) = d

operator :: String -> (Bool, Int -> Int -> Int)
operator "+" = (True, (+))
operator "-" = (True, (-))
operator "*" = (True, (*))
operator "/" = (True, (div))
operator _   = (False, (*))

stackPost :: [String] -> [Int] -> Int
stackPost [] [x] = x
stackPost (x:xs) [] = stackPost xs [read x]
stackPost (x:xs) (y:ys)
    | oper = stackPost xs ((f (head ys) y):(tail ys))
    | otherwise  = stackPost xs ((read x):(y:ys))
    where (oper, f) = operator x

eval1 :: String -> Int
eval1 expr = stackPost (words expr) []


eval2 :: String -> Int
eval2 expr = head (foldl f [] valors)
    where
        valors = words expr
        f (y:x:ys) "+" = (x + y) : ys
        f (y:x:ys) "-" = (x - y) : ys
        f (y:x:ys) "*" = (x * y) : ys
        f (y:x:ys) "/" = div x y : ys
        f ys n         = read n : ys


fsmap :: a -> [a -> a] -> a
fsmap x [] = x
fsmap x (f:fs) = fsmap (f x) fs


onlyOne :: [a] -> Bool
onlyOne []  = True
onlyOne [x] = True
onlyOne _  =  False

divideNconquer :: (a -> Maybe b) -> (a -> (a, a)) -> (a -> (a, a) -> (b, b) -> b) -> a -> b
divideNconquer base divide conquer x
    | trivial = case casBase of Just (w) -> w
    | otherwise = conquer x (x1,x2) (y1,y2)
    where
        casBase = base x
        trivial = case casBase of Nothing -> False
                                  Just (_) -> True
        (x1,x2) = divide x
        y1 = divideNconquer base divide conquer x1
        y2 = divideNconquer base divide conquer x2


quickSort :: [Int] -> [Int]
quickSort ll = divideNconquer base divide conquer ll
    where
         base   = (\x -> if onlyOne x then Just x else Nothing)
         divide = (\(p:xs) -> ([x | x <- xs, x <  p], [x | x <- xs, x >= p]))
         conquer (x:_) _ (ys1, ys2) = ys1 ++ [x] ++ ys2
