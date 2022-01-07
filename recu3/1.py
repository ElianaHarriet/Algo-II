# 1. Un grafo no dirigido es completo cuando todos los vértices están unidos entre sí, por los que tiene todas las aristas que
# puede tener (es decir: (...)). Se dice que un grafo es altamente conectado cuando todos los vértices tienen al
# menos un 40 % de aristas respecto del máximo posible. Escribir una función que reciba un grafo y devuelva true o false
# de acuerdo a si está altamente conectado. Justificar brevemente el orden del algoritmo para una implementación con matriz
# de adyacencias.

def alt_conectado(grafo):
	vertices = grafo.obtener_vertices() 				# O(V)
	max_aristas = (len(vertices) - 1) * len(vertices) / 2 	# O(1)
	minimo = 0.4 * max_aristas 								# O(1)

	aristas = 0
	for v in vertices: 									# V veces O(V) -> O(V^2)
		adyacentes = grafo.adyacentes(v) 				# O(V)
		aristas += len(adyacentes) 						# O(1)
	aristas /= 2 # ya que es no dirigido				# O(1)

	return aristas >= minimo 							# O(1)

# Orden del algoritmo (matriz de adyacencias): O(V^2) 
