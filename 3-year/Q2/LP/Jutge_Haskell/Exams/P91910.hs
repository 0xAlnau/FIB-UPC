multEq2 :: Int -> Int -> Int -> [Int]
multEq2 x y prev = z : multEq2 x y z
    where z = x * y * prev


multEq :: Int -> Int -> [Int]
multEq x y = 1 : multEq2 x y 1


pos :: Int -> [Int] -> Int -> Int
pos _ [] _ =  (-1)
pos x (y:ys) p
    | x == y    = p
    | otherwise = pos x ys (p+1)


isOk :: Int -> [Int] -> [Int] -> Bool
isOk x y z = if ((p1 /= (-1) && p2 /= (-1) && p1 < p2) || (elem x y && not (elem x z))) then True else False
    where
        p1 = pos x y 0
        p2 = pos x z 0


selectFirst :: [Int] -> [Int] -> [Int] -> [Int]
selectFirst [] _ _ = []
selectFirst (x:xs) y z
    | isOk x y z = x : selectFirst xs y z
    | otherwise  = selectFirst xs y z


myIterate :: (a -> a) -> a -> [a]
myIterate f x = scanl (\y _ -> f y) (x) (repeat x)


type SymTab a = String -> Maybe a

empty :: SymTab a
empty = \_ -> Nothing

get :: SymTab a -> String -> Maybe a
get sT s = case sT s of
                Nothing -> Nothing
                Just x  -> Just x

set :: SymTab a -> String -> a -> SymTab a
set sT s v = \x -> (if x == s then Just v else sT x)


data Expr a
    = Val a
        | Var String
        | Sum (Expr a) (Expr a)
        | Sub (Expr a) (Expr a)
        | Mul (Expr a) (Expr a)
          deriving Show

eval :: (Num a) => SymTab a -> Expr a -> Maybe a

eval _ (Val x) = Just x

eval sT (Var s) = sT s

eval sT (Sum e1 e2) = case res1 of
                           Nothing -> Nothing
                           Just  x -> case res2 of
                                           Nothing -> Nothing
                                           Just  y -> Just (x + y)
    where res1 = eval sT e1
          res2 = eval sT e2

eval sT (Sub e1 e2) = case res1 of
                           Nothing -> Nothing
                           Just  x -> case res2 of
                                           Nothing -> Nothing
                                           Just  y -> Just (x - y)
    where res1 = eval sT e1
          res2 = eval sT e2

eval sT (Mul e1 e2) = case res1 of
                           Nothing -> Nothing
                           Just  x -> case res2 of
                                           Nothing -> Nothing
                                           Just  y -> Just (x * y)
    where res1 = eval sT e1
          res2 = eval sT e2
