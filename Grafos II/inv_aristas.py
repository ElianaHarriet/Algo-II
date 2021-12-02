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

def minimas_inversiones(grafo, s, t):
    pesado = Grafo()
    for v in grafo.obtener_vertices():
        if not v in pesado:
            pesado.agregar_vertice(v)
        for w in grafo.adyacentes(v):
            if not w in pesado:
                pesado.agregar_vertice(w)
            pesado.agregar_arista(v, w, 0)
            if not grafo