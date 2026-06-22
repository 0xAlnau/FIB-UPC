main :: IO ()
main = do
    linia <- getLine
    let dades = words linia
    let n = read (head dades) :: Int
    let origen = dades !! 1
    let desti = dades !! 2
    let aux = dades !! 3

    resolHanoi n origen desti aux

-- Función recursiva en la mónada IO
resolHanoi :: Int -> String -> String -> String -> IO ()
resolHanoi 0 _ _ _ = return () -- Caso base: 0 discos, no hacemos nada
resolHanoi n origen desti aux = do
    -- 1. Movemos n-1 discos al poste auxiliar
    resolHanoi (n - 1) origen aux desti

    -- 2. Movemos el disco actual al destino (e imprimimos)
    putStrLn (origen ++ " -> " ++ desti)

    -- 3. Movemos los n-1 discos del auxiliar al destino final
    resolHanoi (n - 1) aux desti origen
