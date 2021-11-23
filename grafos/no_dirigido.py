# 12
# Implementar una función que permita determinar si un grafo puede ser no dirigido.

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

def no_dirigido(grafo): # -> O(V + E)
    vertices = grafo.obtener_vertices()
    for v in vertices:
        for w in grafo.adyacentes(v):
            if not v in grafo.adyacentes(w):
                return False
    return True