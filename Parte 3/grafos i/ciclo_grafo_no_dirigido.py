# Consigna
# Implementar un algoritmo que, dado un grafo no dirigido, nos devuelva un ciclo
# dentro del mismo, si es que los tiene. Indicar el orden del algoritmo.

# Ejemplo
# Para el grafo {A: [B], B: [A, C], C: [B]} el resultado sería lista vacía: []
# Para el grafo {A: [B, C], B: [A, C], C: [B,A]} el resultado podría ser, entre otros,
# [A,B,C] ya que existe un camino que recorra A -> B -> C -> A

# Métodos del grafo no dirigido:
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

def lista_ciclo(padre, inicio, fin):
    v = fin
    camino = []
    while v != inicio:
        camino.append(v)
        v = padre[v]
    camino.append(inicio)
    return camino[::-1]

def _dfs(grafo, v, visitados, padre):
    visitados[v] = True
    for w in grafo.adyacentes(v):
        if w in visitados:
            if w != padre[v]:
                return lista_ciclo(padre, w, v)
    else:
        padre[w] = v
        ciclo = _dfs(grafo, w, visitados, padre)
        if ciclo:
            return ciclo

def obtener_ciclo(grafo):
    visitados = {}
    padre = {}
    for v in grafo.obtener_vertices():
        if v not in visitados:
            ciclo = _dfs(grafo, v, visitados, padre)
            if ciclo:
                return ciclo

# Orden -> O(V + E) [Estando el grafo implementado en una lista de adyacencias] #