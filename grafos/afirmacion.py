# 17
# Implementar una función que reciba un grafo no dirigido, y que
# compruebe la siguiente afirmación: “La cantidad de vértices de
# grado IMPAR es PAR”. 

def afirmación(grafo):
    vertices = grafo.obtener_vertices()
    g_impar = 0
    for vertice in vertices:
        if len(grafo.adyacentes(vertice)) % 2 != 0:
            g_impar += 1
    return g_impar % 2 == 0

# # # # # # # # # # # # # # -> {Orden del algoritmo} <- # # # # # # # # # # # # # # # #
# Obtener los vértices -> O(V)                                                        #
# Obtener los adyacentes de cada vértice -> O(V)                                      #
# (Asumo que calcular el len de una lista es O(N), siendo N la cantidad de elementos) #
# (El resto es O(1))                                                                  #
# Total -> O(V) + V * O(V) -> O(V^2) => O(V^2)                                        #
# [Creo] [idk la diferencia según cómo se implementa el grafo]                        #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #