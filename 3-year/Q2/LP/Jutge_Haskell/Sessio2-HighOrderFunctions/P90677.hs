myFoldl :: (a -> b -> a) -> a -> [b] -> a
myFoldl _ cb [] = cb
myFoldl (op) cb (x:xs) = myFoldl op (op cb x) xs


myFoldr :: (a -> b -> b) -> b -> [a] -> b
myFoldr _ cb [] = cb
myFoldr (op) cb (x:xs) = op x (myFoldr (op) cb xs)


myIterate :: (a -> a) -> a -> [a]
myIterate (op) x = [x] ++ myIterate (op) (op x)


myUntil :: (a -> Bool) -> (a -> a) -> a -> a
myUntil cond op x
    | cond x    = x
    | otherwise = myUntil cond (op) (op x)


myMap :: (a -> b) -> [a] -> [b]
myMap f = myFoldr (\x acc -> f x : acc) []


myFilter :: (a -> Bool) -> [a] -> [a]
myFilter cond = myFoldr (\x acc -> if cond x then x : acc else acc) []


myAll :: (a -> Bool) -> [a] -> Bool
myAll cond = myFoldr (\x acc -> cond x && acc) True


myAny :: (a -> Bool) -> [a] -> Bool
myAny cond = myFoldr (\x acc -> cond x || acc) False


myZip :: [a] -> [b] -> [(a, b)]
myZip _ [] = []
myZip [] _ = []
myZip (x:l1) (y:l2) = [(x,y)] ++ myZip l1 l2


myZipWith :: (a -> b -> c) -> [a] -> [b] -> [c]
myZipWith op l1 l2 =
    let
        zipped = myZip l1 l2
    in
        myMap (\(x,y) -> op x y) zipped
