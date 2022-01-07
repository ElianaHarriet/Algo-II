# 3. En un grafo bipartito, se puede dividir el grafo en dos subgrupos de vértices en los que en ningún grupo hay aristas hacia
# vértices del mismo grupo. Una proyección de un grafo bipartito G es un grafo G2 que tiene sólo los vértices de una de
# las particiones/grupos de G, y las aristas de G2 unen a vértices que en G conectan a mismos vértices. Por ejemplo, en el
# siguiente grafo podemos ver la partición por los nodos del lado izquierdo (vértices 1 a 5).
# (grafos)
# Implementar una función que reciba un grafo no dirigido, bipartito y conexo y un vértice V , y devuelva el grafo de la
# proyección en la que se encuentra V . Los vértices no tienen información sobre la partición en la que se encuentran. Indicar
# y justificar la complejidad del algoritmo implementado.

# BFS (Usado para justificar el orden del algoritmo pedido)
# BFS se "mueve" por todo el grafo yendo de cada vértice a sus adyacentes, como usa un visitados (set) no se repite
# el algoritmo en vértices ya hayan sido visitados. Ya que las operaciones que se realizan son O(1) (usualmente
# ir creando un dicc de distancias y de padres), el algoritmo es O(V + E) [diccionario de diccionarios]

def _bipartito(grafo, v, colores):
	for w in grafo.adyacentes(v):
		if w in colores:
			colores[w] = 1 - colores[v]
			_bipartito(grafo, w, colores)

def bipartito(grafo):
	colores = {}
	for v in grafo.obtener_vertices():
		if v not in colores:
			colores[v] = 0
			_bipartito(grafo, v, colores)
	return colores

# -> Recorre el grafo de la misma forma que BFS (O(V + E)) y las operaciones que realiza son O(1)
# Por lo tanto, bipartito -> O(V + E)


def proyeccion(grafo, vertice):
	particiones = bipartito(grafo) # Obtengo las particiones del grafo -> O(V + E)
	particion = particiones[vertice]

	proyeccion = Grafo(False) # No dirigido
	vertices_particion = set()
	for v in grafo.obtener_vertices(): # V veces O(1) -> O(V)
		if particiones[v] == particion:
			proyeccion.agregar_vertice(v)
			vertices_particion.add(v)
	
	for v in vertices_particion: # Este for (con todo lo que incluye) es O(V + E), ya que opera igual
								 # que BFS (hasta dist = 2 de v) -> O(V + E)
		for w in grafo.obtener_adyacentes(v):
			for x in grafo.obtener_adyacentes(w):
				if particiones[x] == particion:
					proyeccion.agregar_arista(v, x)
	return proyeccion

# Orden del algoritmo (diccionario de diccionarios): O(V + E)
	


             *
            /.\
           /..'\
           /'.'\
          /.''.'\
          /.'.'.\
   "'""""/'.''.'.\""'"'"
         ^^^[_]^^^


# ¡Felices fiestas corrector/a! :)
