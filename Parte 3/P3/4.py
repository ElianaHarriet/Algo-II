# Implementar una función que reciba un grafo dirigido y no pesado (implementado
# con listas de adyacencia (diccionario de diccionarios)) y devuelva una matriz
# que sea equivalente a la representación de matriz de incidencia del mismo grafo.
# Indicar y justificar el orden del algoritmo implementado.

def cant_aristas(grafo): # -> O(V + E)
    cant_ar = 0
    for v in grafo.obtener_vertices():
        cant_ar += len(grafo.obtener_adyacentes(v))
    return cant_ar

def matriz_incidencia(grafo):
    matriz = []
    vertices = grafo.obtener_vertices() # -> O(V)
    len_v = len(vertices) # -> Asumo que es O(V)
    # Creo la fila de los vertices
    arr_ver = [""]
    for v in vertices: # -> O(V)
        arr_ver.append(v)
    matriz.append(arr_ver)
    # Creo la cantidad de filas donde estaran las aristas
    cant_ar = cant_aristas(grafo) # -> O(V + E)
    for i in range(cant_ar): # -> O(E)
        matriz.append(["A" + str(i + 1)] + [0] * (len_v))
    # Creo un diccionario para acceder facilmente a las posisiones de la tabla
    dic_pos = {}
    for i in range(len_v): # -> O(V)
        dic_pos[vertices[i]] = i + 1
    # Agrego los valores a la matriz
    cont_arista = 1
    for v in vertices: # -> O(V^2)
        for w in vertices:
            if v != w and grafo.estan_unidos(v, w): # (estan_unidos (List. ady. DD) -> O(1))
                matriz[cont_arista][dic_pos[v]] = 1
                matriz[cont_arista][dic_pos[w]] = 1
                cont_arista += 1
    return matriz

# -> {Orden del algoritmo} <- #
# (Para una lista de adyacencia DD) #
# O(V) + O(V) + O(V) + O(V + E) + O(E) + O(V) + O(V^2) -> O(V + E + V^2) => O(V^2 + E)