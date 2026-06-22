data Bst a = Empty | Node a (Bst a) (Bst a)

instance Show a => Show (Bst a) where
    show Empty = "."
    show (Node n fe fd) = "(" ++ show n ++ " " ++ show fe ++ " " ++ show fd ++ ")"

myUnfoldr :: (b -> Maybe (a, b)) -> b -> [a]
myUnfoldr f x =
    case f x of
         Nothing    -> []
         Just (m,n) -> m : myUnfoldr f n


myReplicate :: a -> Int -> [a]
myReplicate v n = myUnfoldr (\x -> if x == 0 then Nothing else Just (v, x-1)) n


myIterate :: (a -> a) -> a -> [a]
myIterate f v = myUnfoldr (\x -> Just (x, f x)) v


myMap :: (a -> b) -> [a] -> [b]
myMap f ll = myUnfoldr (\x -> case x of
                                   [] -> Nothing
                                   (y:ys) -> Just (f y, ys)) ll


add :: Ord a => a -> (Bst a) -> (Bst a)
add x Empty = Node x Empty Empty
add x (Node y l r)
    | x < y          = Node y (add x l) r
    | x > y          = Node y l (add x r)
    | otherwise = Node y l r


adder :: Ord a => (Bst a, [a]) -> Maybe (Bst a, (Bst a, [a]))
adder (_, []) = Nothing
adder (t, x:xs) = Just (newTree, (newTree, xs))
    where newTree = add x t
