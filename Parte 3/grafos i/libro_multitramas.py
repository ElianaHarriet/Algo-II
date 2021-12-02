# 15
from collections import deque 

def contar_entrada(grafo, vertice):
    vertices = grafo.obtener_vertices()
    contador = 0
    for v in vertices:
        if grafo.estan_unidos(v, vertice):
            contador += 1
    return contador

def grado_entrada(grafo): # c
    vertices = grafo.obtener_vertices()
    diccionario = {}
    for vertice in vertices:
        diccionario[vertice] = contar_entrada(grafo, vertice)
    return diccionario

def orden_lectura(grafo):
    entrada = grado_entrada(grafo)
    cola = deque()
    for vertice in grafo.obtener_vertices():
        if entrada[vertice] == 0:
            cola.append(vertice)
    orden = []
    while not len(cola) == 0:
        vertice = cola.popleft()
        orden.append(vertice)
        adyacentes = grafo.adyacentes(vertice)
        for v in adyacentes:
            entrada[v] -= 1
            if entrada[v] == 0:
                cola.append(v)
    
    if len(orden) != len(grafo.obtener_vertices()):
        return None
        
    return orden

# Orden -> O(V + E)
# [idk la diferencia según cómo se implementa el grafo]           