# 10
# Escribir una función bool es_bipartito(grafo) que dado un grafo no dirigido devuelva
# true o false de acuerdo a si es bipartito o no. Indicar y justificar el orden del
# algoritmo. ¿Qué tipo de recorrido utiliza?

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

def _es_bipartito(grafo, v, colores): # -> BFS -> O(V + E)
	for w in grafo.adyacentes(v):
		if w in colores:
			if colores[w] == colores[v]:
				return False
		else:
			colores[w] = 1 - colores[v]
			if not _es_bipartito(grafo, w, colores):
				return False
	return True

def es_bipartito(grafo):
	colores = {}
	for v in grafo.obtener_vertices():
		if v not in colores:
			colores[v] = 0
		if not _es_bipartito(grafo, v, colores):
			return False
	return True

# # # # # # # # # # # # # # -> {Orden del algoritmo} <- # # # # # # # # # # # # # # # #
# Obtener los vértices -> O(V)                                                        #
# DFS -> O(V + E)                                                                     #
# (El resto es O(1))                                                                  #
# Total -> O(V) + V * O(V + E) -> O(V + V^2 + V * E) -> O(V^2 + V * E) => O(V(V + E)) #
# [Creo] [idk la diferencia según cómo se implementa el grafo]                        #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #