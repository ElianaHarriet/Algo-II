# 1. Implementar por backtracking un algoritmo que reciba un Grafo y un número n y devuelva una lista con todos los
# caminos de largo n dentro del Grafo (no necesariamente simples).
from grafo import *

def _caminos(grafo, vertice, n, sub_caminos, todos):
	if len(sub_caminos) == n:
		todos.append(sub_caminos)
		return
	
	sub_caminos.append(vertice)
	for w in grafo.adyacentes(vertice):
		_caminos(grafo, w, n, sub_caminos, todos)
	sub_caminos.pop() # Paso para atrás


def caminos(grafo, n):
	todos = []
	for v in grafo.obtener_vertices():
		sub_caminos = []
		_caminos(grafo, v, n, sub_caminos, todos)
	return todos

g = Grafo(False)

g.agregar_vertice(1)
g.agregar_vertice(2)
g.agregar_vertice(3)
g.agregar_vertice(4)
g.agregar_vertice(5)
g.agregar_vertice(6)

g.agregar_arista(2, 6)
g.agregar_arista(2, 5)
g.agregar_arista(6, 1)
g.agregar_arista(1, 3)
g.agregar_arista(1, 5)
g.agregar_arista(1, 6)
g.agregar_arista(3, 4)
g.agregar_arista(3, 5)
g.agregar_arista(5, 6)

print(caminos(g, 2))