import Data.List (sort, group)

print2 :: (String, Int) -> IO()
print2 (s,n) = putStrLn(s ++ " " ++ show n)

main :: IO()
main = do
    content <- getContents
    let linies = lines content
    let paraul = map words linies
    let conca  = concat paraul
    let sorted = sort conca
    let grou   = group sorted
    let orga   = map (\x -> (head x, length x)) grou
    mapM_ print2 orga
