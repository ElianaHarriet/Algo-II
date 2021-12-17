# Problema del viajante (TSP): Dada una lista de ciudades y la distancia entre cada par de ellas, ¿Cuál es el peso de la
# ruta más corta posible que visita cada ciudad exactamente una vez y al finalizar regresa a la ciudad de origen?

# Métodos del grafo
# agregar_vertice(self, v)
# borrar_vertice(self, v)
# agregar_arista(self, v, w, peso = 1)
# el resultado será v <--> w
# borrar_arista(self, v, w)
# estan_unidos(self, v, w)
# peso_arista(self, v, w)
# obtener_vertices(self)
# Devuelve una lista con todos los vértices del grafo
# vertice_aleatorio(self)
# adyacentes(self, v)
# str

def _ciclo(grafo, origen, anterior, vertice, peso, visitados, n):
    if len(visitados) == n:
        if vertice == origen:
            peso += grafo.peso_arista(anterior, vertice)
            return peso
        return None
    if vertice == origen and anterior: # Si es el origen, el ciclo es menor a n
        return None

    peso += grafo.peso_arista(anterior, vertice) if anterior else 0
    visitados.add(vertice)

    pesos = []
    for w in grafo.adyacentes(vertice):
        if w not in visitados or w == origen: # Si el vértice no está en visitados se lo puede agregar,
                                                # si es el origen también porque debe cerrar el ciclo
            # nuevo = _ciclo(grafo, origen, vertice, w, peso, visitados.copy(), n) # .copy() empeora la complejidad
            nuevo = _ciclo(grafo, origen, vertice, w, peso, visitados.copy(), n)
            if nuevo:
                pesos.append(nuevo)
    
    visitados.remove(vertice) # No va abajo, así no se usa el .copy()
    
    if len(pesos) != 0:
        return min(pesos)

    # visitados.remove(vertice)
    return None

def viajante(grafo):
    visitados = set()
    vertice = grafo.vertice_aleatorio()
    n = len(grafo.obtener_vertices())
    return _ciclo(grafo, vertice, None, vertice, 0, visitados, n)
