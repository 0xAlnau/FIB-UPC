data LogicExpression
    = Or  LogicExpression LogicExpression
    | And LogicExpression LogicExpression
    | Not LogicExpression
    | Var String
    | Val Bool

instance Show LogicExpression where
    show (Val False) = "0"
    show (Val True)  = "1"
    show (Var x) = x
    show (Or e1 e2) = "(" ++ show e1 ++ " or " ++ show e2 ++ ")"
    show (And e1 e2) = "(" ++ show e1 ++ " and " ++ show e2 ++ ")"
    show (Not e) = "(not " ++ show e ++ ")"


neg :: LogicExpression -> LogicExpression
neg (Val True) = Val False
neg (Val False) = Val True
neg (Var x) = Not (Var x)
neg (And e1 e2) = Or (neg e1) (neg e2)
neg (Or e1 e2) = And (neg e1) (neg e2)
neg (Not e) = e

pushNegations :: LogicExpression -> LogicExpression
pushNegations (Val True) = Val True
pushNegations (Val False) = Val False
pushNegations (Var x) = Var x
pushNegations (And e1 e2) = And (pushNegations e1) (pushNegations e2)
pushNegations (Or e1 e2) = Or (pushNegations e1) (pushNegations e2)
pushNegations (Not e) = neg e


bits :: [[[Int]]]
bits = iterate ([(0:),(1:)] <*>) ([[]])

