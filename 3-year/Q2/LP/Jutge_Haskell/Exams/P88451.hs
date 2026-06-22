data Tree a = Empty | Node a (Tree a) (Tree a)

instance Show a => Show (Tree a) where
    show Empty = "()"
    show (Node n fe fd) = "(" ++ show fe ++ "," ++ show n ++ "," ++ show fd ++ ")"

instance Functor Tree where
    fmap _ Empty = Empty
    fmap f (Node n fe fd) = (Node (f n) (fmap f fe) (fmap f fd))


data Forest a = Forest [Tree a] deriving (Show)

instance Functor Forest where
    fmap f (Forest trees) = (Forest (map (fmap f) trees))

doubleT :: Num a => Tree a -> Tree a
doubleT tree = (*2) <$> tree

doubleF :: Num a => Forest a -> Forest a
doubleF fore = (*2) <$> fore
