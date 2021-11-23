# 3
# Implementar una función que determine el:
# a. El grado de todos los vértices de un grafo no dirigido.
# b. El grado de salida de todos los vértices de un grafo dirigido.
# c. El grado de entrada de todos los vértices de un grafo dirigido.

# Nota: Las funciones deberan devolver un diccionario con clave vertice y valor grado.

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

def grado_vertices(grafo): # a -> O(V + E)
    vertices = grafo.obtener_vertices()
    diccionario = {}
    for vertice in vertices:
        diccionario[vertice] = len(grafo.adyacentes(vertice))
    return diccionario

def grado_salida(grafo): # b -> O(V + E)
    vertices = grafo.obtener_vertices()
    diccionario = {}
    for vertice in vertices:
        diccionario[vertice] = len(grafo.adyacentes(vertice))
    return diccionario

def contar_entrada(grafo, vertice): # -> O(V) + V * O(V) -> O(V^2)
    vertices = grafo.obtener_vertices()
    contador = 0
    for v in vertices:
        if grafo.estan_unidos(v, vertice):
            contador += 1
    return contador

def grado_entrada(grafo): # c -> O(V + E) [me da duda ._.]
    vertices = grafo.obtener_vertices()
    diccionario = {}
    for vertice in vertices:
        diccionario[vertice] = contar_entrada(grafo, vertice)
    return diccionario

# Ordenes para un grafo implementado con listas de adyacencia (idk que tan bien estén)