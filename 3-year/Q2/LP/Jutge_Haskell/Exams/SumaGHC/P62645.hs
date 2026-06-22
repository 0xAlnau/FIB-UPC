to_Int :: String -> Int
to_Int s = read s

sumaString :: [String] -> Int
sumaString [] = 0
sumaString (x:xs) = (to_Int x) + sumaString xs

main :: IO()
main = do
    content <- getContents
    let linies = lines content
    let separats = map words linies
    let tot = concat separats
    let suma = sumaString tot
    print suma
