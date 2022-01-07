# 1. Implementar por backtracking un algoritmo que reciba un Grafo y un número n y devuelva una lista con todos los
# caminos de largo n dentro del Grafo (no necesariamente simples).

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