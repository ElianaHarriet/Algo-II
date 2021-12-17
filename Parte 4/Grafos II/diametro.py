from collections import deque

def caminos_minimos(grafo, origen): #BFS porque el grafo es no pesado
    q = deque()
    visitados = set()
    distancia = {}
    distancia[origen] = 0
    visitados.add(origen)
    q.append(origen)

    while len(q) > 0:
        v = q.popleft()
        for w in grafo.adyacentes(v):
            if w not in visitados:
                distancia[w] = distancia[v] + 1
                q.append(w)
                visitados.add(w)
    return distancia

def diametro(grafo):
    max_min_dist = 0
    for v in grafo:
        distancias = caminos_minimos(grafo, v)
        for w in distancias:
            if distancias[w] != None and distancias[w] > max_min_dist: # verificar != None para grafos dirigidos
                max_min_dist = distancias[w]
    return max_min_dist