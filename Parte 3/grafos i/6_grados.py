# 8
# La teoría de los 6 grados de separación dice que cualquiera en la Tierra
# puede estar conectado a cualquier otra persona del planeta a través de una
# cadena de conocidos que no tiene más de cinco intermediarios (conectando a
# ambas personas con solo seis enlaces). Suponiendo que se tiene un grafo G
# en el que cada vértice es una persona y cada arista conecta gente que se
# conoce (el grafo es no dirigido):

# a. Implementar un algoritmo para comprobar si se cumple tal teoría para todo
# el conjunto de personas representadas en el grafo G.
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

def grados(grafo): # -> O(V) + V * O(V + E) + O(V + E) -> O(V(V + E)) (creo)
    vertices = grafo.obtener_vertices()
    for v in vertices:
        grados_v = bfs(grafo, v)
        for w in vertices:
            if grados_v[w] > 5:
                return False
    return True