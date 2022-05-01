
import numpy as np
import matplotlib.pyplot as plt
import networkx as nx
import random

class Node():
    def __init__(self):
        self.friend = []
    def degree(self):
        return len(self.friend)

def sumdegree(no):
    res = 0
    for i in no:
        res += len(i.friend)
    return res

nodes = [Node(),Node()]
nodes[0].friend.append(1)
nodes[1].friend.append(2)
edges = [(1,2)]
alldegree = 2

for i in range(0,500):
    newNode = Node()
    L = len(nodes)
    for i in range(0,L):
        p = nodes[i].degree() / alldegree
        if(random.random() < p):
            newNode.friend.append(i+1)
            nodes[i].friend.append( L+1 )
            edges.append( (i+1,L+1) )
            alldegree += 2
    if(len(newNode.friend) == 0):
        continue
    nodes.append(newNode)

plt.figure(figsize=(20,20))
G = nx.Graph()
G.add_nodes_from(  [i+1 for i in range(0,len(nodes))])
G.add_edges_from(edges)
nx.draw(G,with_labels = False,node_size=600,node_color='red',font_size=15,font_color="white")
plt.title("N = " + str(500),fontsize=45)
plt.show()

# k = [ i.degree() for i in nodes ]

# p = [0 for i in range(1,max(k)+1)]
# K_x = [i+1 for i in range(0,len(p))]
# for i in k:
#     p[i-1] += 1

# plt.plot(k,p)
