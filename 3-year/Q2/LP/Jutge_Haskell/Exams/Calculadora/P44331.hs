to_int :: String -> Int
to_int s = read s

suma :: [String] -> [Int] -> (Either String Int)
suma vs (x:y:stack) = case postFixCalc vs ((x+y):stack) of
                           Left  e -> Left e
                           Right s -> Right s


rest :: [String] -> [Int] -> (Either String Int)
rest vs (x:y:stack) = if y - x < 0 then Left "neg" else case postFixCalc vs ((y-x):stack) of
                                                             Left  e -> Left e
                                                             Right s -> Right s


mult :: [String] -> [Int] -> (Either String Int)
mult vs (x:y:stack) = case postFixCalc vs ((x*y):stack) of
                           Left  e -> Left e
                           Right s -> Right s


divi :: [String] -> [Int] -> (Either String Int)
divi vs (x:y:stack) = if x == 0 then Left "div0" else if ((y `mod` x) /= 0) then Left "divE" else case postFixCalc vs ((div y x):stack) of
                           Left  e -> Left e
                           Right s -> Right s


postFixCalc :: [String] -> [Int] -> (Either String Int)
postFixCalc [] [x] = Right x
postFixCalc (v:vs) stack
    | v == "+"  = suma vs stack
    | v == "-"  = rest vs stack
    | v == "*"  = mult vs stack
    | v == "/"  = divi vs stack
    | otherwise = postFixCalc vs ((to_int v) : stack)

calculate :: [String] -> (Either String Int)
calculate sequ = postFixCalc sequ []

main :: IO()
main= do
    content <- getContents
    let linies = lines content
    let paraul = map words linies
    let result = map calculate paraul
    mapM_ print result
