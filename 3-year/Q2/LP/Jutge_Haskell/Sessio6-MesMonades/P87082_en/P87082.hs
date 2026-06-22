getBMI :: Float -> String
getBMI n
    | n < 18            = "magror"
    | 18 <= n && n < 25 = "corpulencia normal"
    | 25 <= n && n < 30 = "sobrepes"
    | 30 <= n && n < 40 = "obesitat"
    | otherwise         = "obesitat morbida"

processBMI :: [String] -> (String, String)
processBMI linia = (nom, bmi)
    where
        nom = head linia
        w = read (linia !! 1)
        h = read (linia !! 2)
        bmi = getBMI (w / (h*h))

main :: IO ()
main = do
    info <- getLine
    if info /= "*" then do
        let llista = words info
        let (name, bmi) = processBMI llista
        putStrLn $ name ++ ": " ++ bmi
        main
    else
        return ()
