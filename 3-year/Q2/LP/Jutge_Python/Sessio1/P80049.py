def count_unique(L):
    s = set({})
    for x in L:
        s.add(x)
    return len(s)

def remove_duplicates(L):
    s = set({})
    for x in L:
        s.add(x)
    return list(s)

def flatten(L):
    result = []
    for x in L:
        result.extend(x)
    return result

def flatten_rec(L):
    result = []
    for x in L:
        if isinstance(x, list): result.extend(flatten_rec(x))
        else: result.append(x)
    return result
