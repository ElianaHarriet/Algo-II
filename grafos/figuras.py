# En un monitor de dos colores(blanco y negro) la pantalla se puede entender como una matriz
# donde un 0 representa un bit en blanco y un 1 un bit en negro. Se entiende como una figura,
# a un grupo de bits en blanco proximos, esto es, que son vecinos horizontal o verticalmente.
# Para no sobrepasar a los usuarios de informacion, hay un maximo de figuras que un programador
# puede mostrar en una pantalla. Por lo que se quiere tener una forma de obtener la cantidad de
# figuras blancas que hay en una pantalla.

# a) Modelar el problema utilizando grafos. Explicar detalladamente cuales serian los vertices
# y aristas de la representacion del grafo.
# b) Asumiendo que se cuenta con un grafo detallado en el punto b) implementar una funcion que
# reciba el grafo y resultva el problema detallado anteriormente. Especificar y justificar la
# complejidad de la funcion.

def cant_figuras(grafo, cant_figuras, visitados):
    for vertice in grafo.obtener_vertices(): 
        if grafo.obtener_color(vertice) == "blanco":
            if vertice not in visitados:
                cant_figuras += 1
                visitados.append(vertice)
                marcar_figura(grafo, vertice, visitados) 
    return cant_figuras

def marcar_figura(grafo, vertice, visitados): 
    for vecino in grafo.obtener_adyacentes(vertice): 
        if grafo.obtener_color(vecino) == "blanco":
            if vecino not in visitados:
                visitados.append(vecino)
                marcar_figura(grafo, vecino, visitados)

# -> {Complejidad de la función} -> O(V + E) (Creo)
# (Para un grafo implementado como diccionario de diccionarios)
