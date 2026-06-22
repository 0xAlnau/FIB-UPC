data Queue a = Queue [a] [a]
    deriving (Show)

instance Eq a => Eq (Queue a) where
    (Queue [] []) == (Queue [] []) = True
    (Queue f1 s1) == (Queue f2 s2) =
        let
            q1 = f1 ++ (reverse s1)
            q2 = f2 ++ (reverse s2)
        in q1 == q2

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
