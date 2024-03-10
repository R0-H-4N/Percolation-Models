import matplotlib.pyplot as plt
import random
import time

random.seed(time.time())

class Percolator:
    def __init__(self, o, pr) -> None:
        self.nodes = [0]
        self.sizes = [1]
        self.state = [True]
        self.order = o
        self.per = 0

        for i in range(1, o*o+1):
            self.nodes.append(i)
            self.sizes.append(1)
            j = random.uniform(0.00, 100.00)
            self.state.append((j <= pr))
            if(j <= pr):
                self.per = self.per + 1
        
        self.nodes.append(o*o+1)
        self.sizes.append(1)
        self.state.append(True)

        for i in range(1, o+1):
            if(self.state[i]):
                self.unite(i, 0)
            if(self.state[self.p(o, i)]):
                self.unite(self.p(o, i), o*o+1)
        self.form()
        

    def form(self):
        for i in range(1, self.order+1):
            for j in range(1, self.order+1):
                if(self.state[self.p(i, j)]):
                    self.connect(i, j)

    def p(self, x, y) -> int:
        return (x-1)*self.order + y
    
    def root(self, a) -> int:
        while(self.nodes[a] != a):
            a = self.nodes[a]
        return a
    
    def connected(self, a, b) -> bool:
        return (self.root(a) == self.root(b))
    
    def unite(self, a, b):
        if(self.connected(a, b)):
            return
        root_a = self.root(a)
        root_b = self.root(b)
        if(self.sizes[root_a] > self.sizes[root_b]):
            self.nodes[root_b] = root_a
            self.sizes[root_a] = self.sizes[root_a] + self.sizes[root_b]
        else:
            self.nodes[root_a] = root_b
            self.sizes[root_b] = self.sizes[root_a] + self.sizes[root_b]

    def connect(self, x, y):
        if(x == 1):
            if(self.state[self.p(x+1, y)]): self.unite(self.p(x+1, y), self.p(x, y)) #down
            if(y == 1):
                if(self.state[self.p(x, y+1)]): self.unite(self.p(x, y+1), self.p(x, y)) #right
            elif(y == self.order):
                if(self.state[self.p(x, y-1)]): self.unite(self.p(x, y-1), self.p(x, y)) #left
            else:
                if(self.state[self.p(x, y+1)]): self.unite(self.p(x, y+1), self.p(x, y)) #right
                if(self.state[self.p(x, y-1)]): self.unite(self.p(x, y-1), self.p(x, y)) #left
        elif(x == self.order):
            if(self.state[self.p(x-1, y)]): self.unite(self.p(x-1, y), self.p(x, y)) #up
            if(y == 1):
                if(self.state[self.p(x, y+1)]): self.unite(self.p(x, y+1), self.p(x, y)) #right
            elif(y == self.order):
                if(self.state[self.p(x, y-1)]): self.unite(self.p(x, y-1), self.p(x, y)) #left
            else:
                if(self.state[self.p(x, y+1)]): self.unite(self.p(x, y+1), self.p(x, y)) #right
                if(self.state[self.p(x, y-1)]): self.unite(self.p(x, y-1), self.p(x, y)) #left
        elif(y == 1):
            if(self.state[self.p(x, y+1)]): self.unite(self.p(x, y+1), self.p(x, y)) #right
            if(x == 1):
                if(self.state[self.p(x+1, y)]): self.unite(self.p(x+1, y), self.p(x, y)) #down
            elif(x == self.order):
                if(self.state[self.p(x-1, y)]): self.unite(self.p(x-1, y), self.p(x, y)) #up
            else:
                if(self.state[self.p(x+1, y)]): self.unite(self.p(x+1, y), self.p(x, y)) #down
                if(self.state[self.p(x-1, y)]): self.unite(self.p(x-1, y), self.p(x, y)) #up
        elif(y == self.order):
            if(self.state[self.p(x, y-1)]): self.unite(self.p(x, y-1), self.p(x, y)) #left
            if(x == 1):
                if(self.state[self.p(x+1, y)]): self.unite(self.p(x+1, y), self.p(x, y)) #down
            elif(x == self.order):
                if(self.state[self.p(x-1, y)]): self.unite(self.p(x-1, y), self.p(x, y)) #up
            else:
                if(self.state[self.p(x+1, y)]): self.unite(self.p(x+1, y), self.p(x, y)) #down
                if(self.state[self.p(x-1, y)]): self.unite(self.p(x-1, y), self.p(x, y)) #up
        else:
            if(self.state[self.p(x+1, y)]): self.unite(self.p(x+1, y), self.p(x, y)) #down
            if(self.state[self.p(x-1, y)]): self.unite(self.p(x-1, y), self.p(x, y)) #up
            if(self.state[self.p(x, y+1)]): self.unite(self.p(x, y+1), self.p(x, y)) #right
            if(self.state[self.p(x, y-1)]): self.unite(self.p(x, y-1), self.p(x, y)) #left

    def show(self) -> None:
        for i in range(1, self.order+1):
            for j in range(1, self.order+1):
                if(self.state[self.p(i, j)]):
                    print(1, end = " ")
                else:
                    print(0, end = " ")
            print("\n")
    
    def display(self) -> None:
        for i in range(1, self.order+1):
            for j in range(1, self.order+1):
                print(self.root(self.p(i, j)), end=" ")
            print("\n")

    def perc(self):
        print(self.per)

    def percolating(self) -> bool:
        return self.connected(0, self.order*self.order + 1)
    

x = []
y = []
print("Started\n")
for k in range(0, 1001):
    c = 0
    j = k / 10

    for i in range(1, 101):
        network = Percolator(100, j)
        if(network.percolating()):
            c = c + 1
        
    c = c / 100
    y.append(c)
    x.append(j)

plt.plot(x, y, marker = 'o')
plt.xlabel('x-axis')
plt.ylabel('y-axis')
plt.title('Perculation Graph')
plt.grid(True)
plt.show()




