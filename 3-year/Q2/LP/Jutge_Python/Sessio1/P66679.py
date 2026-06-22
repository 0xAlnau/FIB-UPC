from math import sqrt

def my_map(f, L):
    return [ f(x) for x in L ]

def my_filter(f, L):
    return [ x for x in L if f(x) ]

def factors(n):
    return [ x for x in range(1, n+1) if n % x == 0 ]

def triplets(n):
    return [ (x, y, int(sqrt(x**2 + y**2)) ) for x in range(1,n+1) for y in range(1,n+1) if sqrt(x**2 + y**2).is_integer() and sqrt(x**2 + y**2) <= n ]
