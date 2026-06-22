class Tree:
    def __init__(self, x):
        self.rt = x
        self.child = []

    def add_child(self, a):
        self.child.append(a)

    def root(self):
        return self.rt

    def ith_child (self, j):
        fills = self.child
        for i in range(0,len(fills)):
            if i == j: return fills[i]

    def num_children (self):
        return len(self.child)


class Pre(Tree):
    def preorder(self):
        res = [self.rt]
        fills = self.child
        
        for f in fills:
            res.extend(f.getPreorder())
            
        return res

    def getPreorder(self):
        res = [self.rt]
        fills = self.child

        for f in fills:
            res.extend(f.getPreorder())
            
        return res

        
