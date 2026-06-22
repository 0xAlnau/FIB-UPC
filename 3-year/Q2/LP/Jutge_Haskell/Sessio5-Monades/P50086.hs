data Queue a = Queue [a] [a]
    deriving (Show)

instance Eq a => Eq (Queue a) where
    (Queue [] []) == (Queue [] []) = True
    (Queue f1 s1) == (Queue f2 s2) =
        let
            q1 = f1 ++ (reverse s1)
            q2 = f2 ++ (reverse s2)
        in q1 == q2

instance Functor Queue where
    fmap f (Queue [] []) = Queue ([]) ([])
    fmap f (Queue f1 []) = Queue (fmap f f1) ([])
    fmap f (Queue [] s1) = Queue ([]) (fmap f s1)
    fmap f (Queue f1 s1) = Queue (fmap f f1) (fmap f s1)


--BUSQUEM LLISTES PLANES ALS APL I MONADS

-- pure :: a -> f a                  (on f es Queue en aquest cas)
-- (<*>) :: f (a -> b) -> f a -> f b (on f es Queue)
-- funcions <*> valors
instance Applicative Queue where
    pure x = Queue [] [x]
    (Queue f1 s1) <*> (Queue f2 s2) =
        let
            funcs  = f1 ++ reverse s1
            valors = f2 ++ reverse s2
        in
            Queue (funcs <*> valors) []

-- return :: a -> m a     el mateix que pure, es fa return = pure
-- (>>=) :: m a -> (a -> m b) -> m b    agafa una cua i una funcio, retorna mes cues
instance Monad Queue where
    return x = pure x
    (Queue f1 s1) >>= g =
        let
            valors = f1 ++ reverse s1
            toList (Queue f2 s2) = f2 ++ reverse s2 --func aux
            nousElements = concatMap (\x -> toList (g x)) valors
        in
            Queue nousElements []



create :: Queue a
create = Queue [] []

push :: a -> Queue a -> Queue a
push x (Queue frt sec) = Queue frt (x:sec)

pop :: Queue a -> Queue a
pop (Queue [] sec) = pop (Queue (reverse sec) [])
pop (Queue (x:frt) sec) = Queue frt sec

top :: Queue a -> a
top (Queue [] sec) = top (Queue (reverse sec) [])
top (Queue (x:frt) sec) = x

empty :: Queue a -> Bool
empty (Queue [] []) = True
empty _ = False


translation :: Num b => b -> Queue b -> Queue b
translation n q = fmap (+n) q


kfilter :: (p -> Bool) -> Queue p -> Queue p
kfilter cond queue = do
    x <- queue              --treiem cada elment de la cua
    if cond x               --condicio
       then return x        --si es True dintre
       else Queue [] []     --cua buida
