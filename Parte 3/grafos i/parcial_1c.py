#4
def dfs(grafo, origen, visitados, max, max_camino): # -> O(V + E)
    for v in grafo.adyacentes(origen):
        if v not in visitados:
            visitados.add(v)
            dfs = dfs(grafo, v, visitados, max, max_camino)
            max[v] = dfs if dfs > v else v
            max_camino = max[v] if max[v] > max_camino else max_camino
    return max_camino

def max_etiqueta(grafo): # => O(V + E) (Para diccionario de diccionarios)
    visitados = set()
    max = {}
    for v in grafo.vertices():
        if v not in visitados:
            max[v] = v
            visitados.add(v)
            max[v] = dfs(grafo, v, visitados, max, max[v])
    return max

#6
def grado_vertices(grafo): # -> O(V + E)
    vertices = grafo.obtener_vertices()
    diccionario = {}
    for vertice in vertices:
        diccionario[vertice] = len(grafo.adyacentes(vertice))
    return diccionario

def grado_total(grafo): # -> O(V + E) + O(V) => O(V + E) (Para diccionario de diccionarios)
    grados = grado_vertices(grafo)
    total = 0
    for grado in grados.values():
        total += grado
    return total

# # # # # # # -> {Orden del algoritmo} <- # # # # # # #
#           (para una matriz de adyacencias)          #
# ::grado_vertices::                                  #
#   Obtener vértices -> O(V)                          #
#   Obtener grado de cada vértice -> V * O(V)         #
#   Total -> O(V + V^2) -> O(V^2)                     #
# ::grado_total::                                     #
#   Obtener el grado de todos los vértices -> O(V^2)  #
#   Sumar todos los grados -> O(V)                    #
#   Total -> O(V^2 + V) => O(V^2)                     #
# # # # # # # # # # # # # # # # # # # # # # # # # # # #