# Implementar por backtracking un algoritmo que reciba un Grafo no dirigido y no pesado, un vértice origen A, un vértice
# destino B y un número K y devuelva una lista con todos los caminos existentes de A hacia B que estén a distancia menor
# que K.
from grafo import *

def _caminos(grafo, a, b, k, todos, sub_caminos):
	if len(sub_caminos) > k - 2:
		return
	sub_caminos.append(a)
	if a == b:
		todos.append(sub_caminos.copy())
		sub_caminos.pop()
		return
	
	for v in grafo.adyacentes(a):
		_caminos(grafo, v, b, k, todos, sub_caminos)
	sub_caminos.pop()

def caminos(grafo, a, b, k):
	todos = []
	sub_caminos = []
	_caminos(grafo, a, b, k, todos, sub_caminos)
	return todos
