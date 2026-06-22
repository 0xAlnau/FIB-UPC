cmpl :: String-> String
cmpl [] = []
cmpl (c:xs)
    | c == '0'  = '1' : cmpl xs
    | otherwise = '0' : cmpl xs

seqtm2 :: String -> [String]
seqtm2 ant = [ant] ++ seqtm2 (ant ++ cmpl ant)

seqtm :: [String]
seqtm = seqtm2 "0"
