def fibs():
    a, b = 0, 1
    while True:
        yield a
        a, b = b, a + b

def roots(x):
    a = x
    while True:
        yield a
        a = 1/2 * (a + (x / a))

def primes():
    prim = [2]
    yield 2

    a = 3
    while True:
        div = False
        it = iter(prim)

        while True and not div:
            try:
                d = it.__next__()
                if a % d == 0: div = True
            except StopIteration:
                break

        if not div:
            yield a
            prim.append(a)
        a += 1

def naturals():
    a = 1
    while True:
        yield a
        a += 1

def hammings():
    # El primer número de Hamming es el 1
    h = [1]
    yield 1

    i2 = i3 = i5 = 0

    while True:
        next2 = h[i2] * 2
        next3 = h[i3] * 3
        next5 = h[i5] * 5

        next_h = min(next2, next3, next5)

        h.append(next_h)
        yield next_h

        if next_h == next2:
            i2 += 1
        if next_h == next3:
            i3 += 1
        if next_h == next5:
            i5 += 1
