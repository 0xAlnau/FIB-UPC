fizzBuzz :: [Either Int String]
fizzBuzz = auxFizz 0

--aux for fizzBuzz
auxFizz :: Int -> [Either Int String]
auxFizz x
    | x `mod` 3 == 0 && x `mod` 5 == 0 = Right "FizzBuzz" : auxFizz (x+1)
    | x `mod` 3 == 0                   = Right "Fizz" : auxFizz (x+1)
    | x `mod` 5 == 0                   = Right "Buzz" : auxFizz (x+1)
    | otherwise                        = Left x : auxFizz (x+1)
