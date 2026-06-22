def myLength(L):
    count = 0
    for x in L:
        count += 1
    return count

def myMaximum(L):
    maximum = L[0]
    for x in L:
        if maximum < x: maximum = x
    return maximum

def average(L):
    aver = 0.0
    for x in L:
        aver += x
    return aver / myLength(L)

def buildPalindrome(L):
    R = reversed(L)
    return list(R) + L #sino es un reversed_list

def remove(L1,L2):
    return [x for x in L1  if x not in L2]

def flatten(L):
    result = []
    for x in L:
        if isinstance(x, list): result.extend(flatten(x))
        else: result.append(x)
    return result

def oddsNevens(L):
    odds = []
    even = []
    for x in L:
        if x % 2 == 0: even.append(x)
        else: odds.append(x)
    return odds, even

def isPrime(x):
    if (x <= 1): return False
    else:
        for i in range(2, x // 2 + 1):
            if x % i == 0:
                return False
        return True

def primeDivisors(n):
    result = []
    for i in range(2, n // 2 +1):
        if n % i == 0 and isPrime(i): result.append(i)

    if isPrime(n): result.append(n)

    return result
