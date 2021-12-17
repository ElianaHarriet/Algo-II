# Métodos del grafo:
# •agregar_vertice(self, v)
# •borrar_vertice(self, v)
# •agregar_arista(self, v, w, peso = 1)
#   •el resultado será v <--> w
# •borrar_arista(self, v, w)
# •estan_unidos(self, v, w)
# •peso_arista(self, v, w)
# •obtener_vertices(self)
#   •Devuelve una lista con todos los vértices del grafo
# •vertice_aleatorio(self)
# •adyacentes(self, v)
# •str
import heapq

def camino_minimo(grafo, s, t):
    distancias = {}
    for v in grafo.obtener_vertices():
        distancias[v] = float('inf')
    distancias[s] = 0
    q = []
    heapq.heappush(q, (s, 0))
    while len(q) != 0:
        v = heapq.heappop(q)[0]
        for w in grafo.adyacentes(v):
            if (distancias[v] + grafo.peso_arista(v, w)) < distancias[w]:
                distancias[w] = distancias[v] + grafo.peso_arista(v, w)
                heapq.heappush(q, (w, distancias[w]))
    return distancias[t]

def minimas_inversiones(grafo, s, t):
    pesado = Grafo()
    for v in grafo.obtener_vertices():
        if not v in pesado:
            pesado.agregar_vertice(v)
        for w in grafo.adyacentes(v):
            if not w in pesado:
                pesado.agregar_vertice(w)
            pesado.agregar_arista(v, w, 0)
            if not grafo.estan_unidos(w, v):
                pesado.agregar_arista(w, v, 1)
    return camino_minimo(pesado, s, t)

# En las pruebas de RPL no hay función para crear un grafo, lo hice editando
# el mismo grafo:
def minimas_inversiones(grafo, s, t):
    for v in grafo.obtener_vertices():
        for w in grafo.adyacentes(v):
            if grafo.peso_arista(v, w) != 0:
                grafo.borrar_arista(v, w)
                grafo.agregar_arista(v, w, 0)
            if not grafo.estan_unidos(w, v):
                grafo.agregar_arista(w, v, 1)
    return camino_minimo(grafo, s, t)