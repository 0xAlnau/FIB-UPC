data Tree a = Node a (Tree a) (Tree a) | Empty deriving (Show)

pri (x, _, _) = x
seg (_, x, _) = x
ter (_, _, x) = x

size :: Tree a -> Int
size Empty = 0
size (Node _ fe fd) = 1 + size fe + size fd


height :: Tree a -> Int
height Empty = 0
height (Node _ fe fd) = 1 + max (height fe) (height fd)


equal :: Eq a => Tree a -> Tree a -> Bool
equal Empty Empty = True
equal (Node _ _ _) Empty = False
equal Empty (Node _ _ _) = False
equal (Node n1 fe1 fd1) (Node n2 fe2 fd2)
    | n1 == n2 = True && equal fe1 fe2 && equal fd1 fd2
    | otherwise = False


isomorphic :: Eq a => Tree a -> Tree a -> Bool
isomorphic Empty Empty = True
isomorphic (Node _ _ _) Empty = False
isomorphic Empty (Node _ _ _) = False
isomorphic (Node n1 fe1 fd1) (Node n2 fe2 fd2)
    | n1 == n2                                  = (isomorphic fe1 fe2 && isomorphic fd1 fd2) || (isomorphic fe1 fd2 && isomorphic fe2 fd1)
    | otherwise                                 = False


preOrder :: Tree a -> [a] -- arrel + esq + dret
preOrder Empty = []
preOrder (Node n fe fd) = n : preOrder fe ++ preOrder fd


postOrder :: Tree a -> [a] -- esq + dret + arrel
postOrder Empty = []
postOrder (Node n fe fd) = postOrder fe ++ postOrder fd ++ [n]


inOrder :: Tree a -> [a] -- esq + arrel + dret
inOrder Empty = []
inOrder (Node n fe fd) = inOrder fe ++ [n] ++ inOrder fd


breadthFirst :: Tree a -> [a]
breadthFirst Empty = []
breadthFirst (Node n fe fd) = n : auxBFS [fe,fd]

--aux for breadthFirst, volem fer una cua!
auxBFS :: [Tree a] -> [a]
auxBFS [] = []
auxBFS ((Empty):ts) = [] ++ auxBFS ts
auxBFS ((Node n fe fd):ts) = n : auxBFS (ts ++ [fe] ++ [fd])


build :: Eq a => [a] -> [a] -> Tree a
build [] [] = Empty
build (p:ps) inOrderList = Node p leftTree rightTree
    where
        -- Encontramos la raíz 'p' en el inorden y separamos izquierda y derecha
        (leftInOrder, _:rightInOrder) = break (== p) inOrderList

        -- Calculamos cuántos elementos tiene el subárbol izquierdo
        leftLen = length leftInOrder

        -- Separamos el preorden restante (ps) en preorden izquierdo y derecho
        (leftPreOrder, rightPreOrder) = splitAt leftLen ps

        -- Llamadas recursivas para construir cada lado
        leftTree = build leftPreOrder leftInOrder
        rightTree = build rightPreOrder rightInOrder



overlap :: (a -> a -> a) -> Tree a -> Tree a -> Tree a
overlap _ Empty (Node n fe fd) = Node n fe fd
overlap _ (Node n fe fd) Empty = Node n fe fd
overlap _ Empty Empty = Empty
overlap f (Node n1 fe1 fd1) (Node n2 fe2 fd2) = Node (f n1 n2) (overlap f fe1 fe2) (overlap f fd1 fd2)

