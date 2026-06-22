empty :: [a] -> Bool
empty [] = True
empty _  = False

traductor :: Char -> Int
traductor 'I' = 1
traductor 'V' = 5
traductor 'X' = 10
traductor 'L' = 50
traductor 'C' = 100
traductor 'D' = 500
traductor 'M' = 1000

roman2int :: String -> Int
roman2int [] = 0
roman2int (c:str)
    | not (empty str) && traductor c < traductor (head str) = (-traductor c) + roman2int str
    | otherwise                          = traductor c + roman2int str


roman2int' :: String -> Int
roman2int' str =
    let
        decimal = map traductor str
        despla = tail decimal ++ [0]
        negatius = zipWith (\actual segu -> if actual < segu then -actual else actual) decimal despla
    in
        foldl (+) 0 negatius


arrels :: Float -> [Float]
arrels x = x : auxArrels x x

auxArrels :: Float -> Float -> [Float]
auxArrels p x =
    let
        actual = (1/2) * (p + (x/p))
    in
        actual : auxArrels actual x


arrel :: Float -> Float -> Float
arrel x e =
    let
        desp = tail (arrels x)
    in
        untilError (arrels x) desp e

untilError :: [Float] -> [Float] -> Float -> Float
untilError (x:xs) (y:ys) e
    | abs(x-y) <= e = y
    | otherwise     = untilError xs ys e


data LTree a = Leaf a | Node (LTree a) (LTree a)

instance (Show a) => Show (LTree a) where
    show (Leaf a) = "{" ++ show a ++ "}"
    show (Node l r) = "<" ++ show l ++ "," ++ show r ++ ">"

dividirLista :: [a] -> ([a], [a])
dividirLista xs =
    let mitad = (length xs + 1) `div` 2
    in splitAt mitad xs

build :: [a] -> LTree a
build [x] = Leaf x
build xs =
    let mitads = dividirLista xs
    in Node (build (fst mitads)) (build (snd mitads))


zipLTrees :: LTree a -> LTree b -> Maybe (LTree (a,b))
zipLTrees (Leaf l) (Node _ _) = Nothing
zipLTrees (Node _ _) (Leaf l) = Nothing
zipLTrees (Leaf l1) (Leaf l2) = Just (Leaf (l1, l2))
zipLTrees (Node e1 d1) (Node e2 d2) =
    do
        dre <- zipLTrees d1 d2
        esq <- zipLTrees e1 e2
        Just (Node esq dre)

