# 11
# Implementar un algoritmo que reciba un grafo dirigido, un vértice
# V y un número N, y devuelva una lista con todos los vértices que
# e encuentren a exactamente N aristas de distancia del vértice V. 
from collections import deque 

def bfs(grafo, origen): # -> O(V + E)
    visitados = set()
    orden = {}
    orden[origen] = 0
    visitados.add(origen)
    cola = deque()
    cola.append(origen)
    while len(cola) > 0:
        vertice = cola.popleft()
        for w in grafo.obtener_adyacentes(vertice):
            if w not in visitados:
                visitados.add(w)
                orden[w] = orden[vertice] + 1
                cola.append(w)
    return orden

def n_vertices(grafo, origen, n): # -> O(V + E)
    orden = bfs(grafo, origen)
    return [vertice for vertice in orden if orden[vertice] == n]