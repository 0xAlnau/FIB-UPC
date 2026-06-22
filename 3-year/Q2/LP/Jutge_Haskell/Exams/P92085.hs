
data Nat = Z | S Nat
    deriving Show


rec :: a -> (Nat -> a -> a) -> Nat -> a
rec base step Z = base 
rec base step (S n) = step n (rec base step n)


-- indica si un natural e ́s parell o no
isEven :: Nat -> Bool 
isEven = rec base step
    where 
        base = True
        step = (\_ y -> not y)


-- retorna la suma de dos naturals
add :: Nat -> (Nat -> Nat)
add = rec base step 
    where
        base = (\y -> y) -- base :: Nat -> Nat
        step = (\_ rec_m -> (\y -> S (rec_m y))) -- step :: Nat -> (Nat -> Nat) -> (Nat -> Nat)


-- retorna el producte de dos naturals
mul :: Nat -> (Nat -> Nat)
mul = rec base step
    where
        base = const Z
        step = \_ rec_m y -> add y (rec_m y)


-- retorna el factorial d’un natural
fact :: Nat -> Nat
fact = rec base step
    where
        base = S Z
        step = mul . S


