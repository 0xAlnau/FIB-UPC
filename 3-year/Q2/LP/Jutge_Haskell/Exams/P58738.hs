data STree a = Nil | Node Int a (STree a) (STree a) deriving Show

instance Functor (STree) where
    fmap _ Nil = Nil
    fmap f (Node t n fe fd) = (Node t (f n) (fmap f fe) (fmap f fd))

getT :: STree a -> Int
getT Nil = 0
getT (Node t _ _ _) = t

isOk :: STree a -> Bool
isOk Nil = True
isOk (Node t n l r) = isOk l && isOk r && t == 1 + (getT l) + (getT r)


auxNthElement :: STree a -> Int -> Maybe a
auxNthElement Nil _ = Nothing
auxNthElement (Node t n l r) nth
    | nth <= tEsq     = auxNthElement l nth
    | nth == tEsq + 1 = Just n
    | otherwise       = auxNthElement r (nth - tEsq - 1)
    where
        tEsq = getT l

nthElement :: STree a -> Int -> Maybe a
nthElement tree nth
    | isOk tree = auxNthElement tree nth
    | otherwise           = Nothing


mapToElements :: (a -> b) -> STree a -> [Int] -> [Maybe b]
mapToElements _ _ [] = []
mapToElements f tree (x:xs) =
    case nthElement tree x of
         Nothing -> Nothing : mapToElements f tree xs
         Just v  -> Just (f v) : mapToElements f tree xs
