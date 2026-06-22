data Expr = Val Int | Add Expr Expr | Sub Expr Expr | Mul Expr Expr | Div Expr Expr


eval1 :: Expr -> Int
eval1 (Val v) = v
eval1 (Add e1 e2) = eval1 e1 + eval1 e2
eval1 (Sub e1 e2) = eval1 e1 - eval1 e2
eval1 (Mul e1 e2) = eval1 e1 * eval1 e2
eval1 (Div e1 e2) = div (eval1 e1) (eval1 e2)


eval2 :: Expr -> Maybe Int
eval2 (Val v) = Just v

eval2 (Add e1 e2) = do
    e1_ev <- eval2 e1
    e2_ev <- eval2 e2
    Just (e1_ev + e2_ev)

eval2 (Sub e1 e2) = do
    e1_ev <- eval2 e1
    e2_ev <- eval2 e2
    Just (e1_ev - e2_ev)

eval2 (Mul e1 e2) = do
    e1_ev <- eval2 e1
    e2_ev <- eval2 e2
    Just (e1_ev * e2_ev)

eval2 (Div e1 e2) = do
    e1_ev <- eval2 e1
    e2_ev <- eval2 e2
    if (e2_ev == 0) then Nothing
    else Just (div e1_ev e2_ev)


eval3 :: Expr -> Either String Int
eval3 (Val v) = Right v

eval3 (Add e1 e2) = do
    e1_ev <- eval3 e1
    e2_ev <- eval3 e2
    Right (e1_ev + e2_ev)

eval3 (Sub e1 e2) = do
    e1_ev <- eval3 e1
    e2_ev <- eval3 e2
    Right (e1_ev - e2_ev)

eval3 (Mul e1 e2) = do
    e1_ev <- eval3 e1
    e2_ev <- eval3 e2
    Right (e1_ev * e2_ev)

eval3 (Div e1 e2) = do
    e1_ev <- eval3 e1
    e2_ev <- eval3 e2
    if (e2_ev == 0) then Left "div0"
    else Right (div e1_ev e2_ev)
