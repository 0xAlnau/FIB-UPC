class Tree:
    def __init__(self, x):
        self.rt = x
        self.child = []

    def __iter__(self):
        c = []
        c.append(self)
        while len(c) > 0:
            tree = c.pop(0)
            yield tree.rt
            for f in tree.child:
                c.append(f)
                
    
    def addChild(self, a):
        self.child.append(a)

    def root(self):
        return self.rt

    def ithChild (self, j):
        fills = self.child
        for i in range(0,len(fills)):
            if i == j: return fills[i]

    def numChildren (self):
        return len(self.child)
        

