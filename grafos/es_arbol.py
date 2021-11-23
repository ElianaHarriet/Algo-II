# 6
def lista_ciclo(padre, inicio, fin):
    v = fin
    camino = []
    while v != inicio:
        camino.append(v)
        v = padre[v]
    camino.append(inicio)
    return camino[::-1]

def _dfs_ciclo(grafo, v, visitados, padre):
    visitados[v] = True
    for w in grafo.adyacentes(v):
        if w in visitados:
            if w != padre[v]:
                return lista_ciclo(padre, w, v)
    else:
        padre[w] = v
        ciclo = _dfs_ciclo()(grafo, w, visitados, padre)
        if ciclo:
            return ciclo

def obtener_ciclo(grafo):
    visitados = {}
    padre = {}
    for v in grafo.obtener_vertices():
        if v not in visitados:
            ciclo = _dfs_ciclo(grafo, v, visitados, padre)
            if ciclo:
                return 
                
def es_aciclico(grafo):
    ciclo = obtener_ciclo(grafo)
    return len(ciclo) == 0


def cant_aristas(grafo): #(grafo no dirigido)
    aristas = 0
    for v in grafo.obtener_vertices():
        aristas += len(grafo.adyacentes(v))
    return aristas / 2

def cant_vertices(grafo):
    return len(grafo.obtener_vertices())

def es_arbol(grafo):
    return es_aciclico(grafo) and cant_aristas(grafo) == cant_vertices(grafo) - 1

# # # # # # # # # -> {Orden del algoritmo} <- # # # # # # # # #
# Ver si es aciclico -> O(V + E)                              #
# Contar las aristas -> O(V + E)                              #
# Contar los vertices -> O(V)                                 #
# Total -> 2 * O(V + E) + O(V) => O(V + E)                    #
# [Estando el grafo implementado en una lista de adyacencias] #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #