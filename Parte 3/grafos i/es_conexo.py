# 4
# Implementar un algoritmo que determine si un grafo no dirigido es conexo o
# no. 

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

def _dfs(grafo, v, visitados):
    visitados.add(v)
    for w in grafo.adyacentes(v):
        if w not in visitados:
            _dfs(grafo, w, visitados)

def es_conexo(grafo):
    vertices = grafo.obtener_vertices()
    visitados = set()
    componentes = 0
    for v in vertices:
        if v not in visitados:
            componentes += 1
            _dfs(grafo, v, visitados)
    return componentes <= 1
# # # # # # # # # # # # # # -> {Orden del algoritmo} <- # # # # # # # # # # # # # # # #
# Obtener los vértices -> O(V)                                                        #
# DFS -> O(V + E)                                                                     #
# (El resto es O(1))                                                                  #
# Total -> O(V) + V * O(V + E) -> O(V + V^2 + V * E) -> O(V^2 + V * E) => O(V(V + E)) #
# [Creo] [idk la diferencia según cómo se implementa el grafo]                        #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #