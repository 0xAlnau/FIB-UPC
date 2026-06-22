def absValue(x):
    if (x < 0): return -x
    else: return x;

def power(x,p):
    if (p == 0): return 1
    else: return x * power(x, p-1)

def isPrime(x):
    if (x <= 1): return False
    else:
        for i in range(2,x // 2 + 1):
            if x % i == 0:
                return False
        return True

def slowFib(n):
    if   n == 0: return 0
    elif n == 1: return 1
    else:
        return slowFib(n-2) + slowFib(n-1)

def quickFib(n):
    fib0 = 0
    fib1 = 1
    for i in range(0, n):
        aux = fib0
        fib0 = fib1
        fib1 = aux + fib1
    return fib0
