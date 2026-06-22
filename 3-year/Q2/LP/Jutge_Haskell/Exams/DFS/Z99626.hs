data Node a = Node a [a]
data Graf a = Graf [Node a]

mostraVeins :: Show a => [a] -> String
mostraVeins [] = []
mostraVeins (v:vs) = ", " ++ show v ++ mostraVeins vs

instance Show a => Show (Node a) where
    show (Node x []) = show x
    show (Node x (v:vs)) = show x ++ " : " ++ show v ++ mostraVeins vs

instance Show a => Show (Graf a) where
    show (Graf []) = []
    show (Graf (n:[])) = show n
    show (Graf (n:ns)) = show n ++ "\n" ++ show (Graf ns)


afegeix :: [a] -> [a] -> [a]
afegeix [] ll = ll
afegeix (x:xs) ll = afegeix xs ll2
    where ll2 = x : ll


getNode :: Eq a => Graf a -> a -> Node a
getNode (Graf ((Node n v):ns)) nom
    | n == nom  = Node n v
    | otherwise = getNode (Graf ns) nom


cami :: Eq a => Graf a -> (a, a) -> Bool
cami g (ori, des) = dfs g (getNode g ori) des []

dfs :: Eq a => Graf a -> Node a -> a -> [a] -> Bool
dfs g (Node n v) des visit
    | n == des       = True    -- ¡Hemos llegado al destino!
    | n `elem` visit = False   -- Ya hemos estado aquí, evitamos el ciclo
    | otherwise      = any (\vei -> dfs g (getNode g vei) des (n:visit)) v

to_node :: [a] -> Node a
to_node (n:[]) = Node n []
to_node (n:ns) = Node n ns


main :: IO ()
main = do
    contents <- getContents
    let linies = lines contents
    let senseEsp = map words linies
    let oriDes = head senseEsp
    let graf = tail senseEsp
    let (ori,des) = (head oriDes, head $ tail oriDes)
    let nodes = map to_node graf
    let grafFinal = Graf nodes
    let bool = cami grafFinal (ori,des)
    print bool
