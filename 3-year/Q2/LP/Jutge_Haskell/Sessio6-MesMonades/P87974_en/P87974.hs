isDona :: String -> Bool
isDona str
    | head (reverse str) == 'a' || head (reverse str) == 'A' = True
    | otherwise       = False


main :: IO ()
main = do
    nom <- getLine
    let dona = isDona nom
    if (dona) then putStrLn "Hola maca!"
    else putStrLn "Hola maco!"

