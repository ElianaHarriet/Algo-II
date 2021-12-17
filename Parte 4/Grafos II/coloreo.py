# Implementar un algoritmo que reciba un grafo y un número nn que, utilizando backtracking, indique
# si es posible pintar cada vértice con nn colores de tal forma que no hayan dos vértices adyacentes
# con el mismo color.

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

def valido(grafo, vertice, coloreados):
    for v in grafo.adyacentes(vertice):
        if v in coloreados and coloreados[v] == coloreados[vertice]:
            return False
    return True

def _colorear(grafo, coloreados, n, vertices, ind):
    if len(coloreados) == len(grafo.obtener_vertices()):
        return True
    
    nuevo_vertice = vertices[ind]
    for i in range(n):
        coloreados[nuevo_vertice] = i
        if not valido(grafo, nuevo_vertice, coloreados):
            del coloreados[nuevo_vertice]
            continue
        if _colorear(grafo, coloreados, n, vertices, ind + 1):
            return True
        del coloreados[nuevo_vertice]
    
    return False

def colorear(grafo, n):
    coloreados = {}
    vertices = grafo.obtener_vertices()
    return _colorear(grafo, coloreados, n, vertices, 0)