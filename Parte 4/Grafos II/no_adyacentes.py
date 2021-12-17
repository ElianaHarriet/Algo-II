# Implementar por backtracking un algoritmo que, dado un grafo no dirigido y un numero n
# menor a #V, devuelva si es posible obtener un subconjunto de n vertices tal que ningun
# par de vertices sea adyacente entre si.

# Se puede suponer que los vértices están identificados con números de 0 a V - 1.

# Métodos del grafo
# agregar_vertice(self, v)
# borrar_vertice(self, v)
# agregar_arista(self, v, w, peso = 1)
#   el resultado será v <--> w
# borrar_arista(self, v, w)
# estan_unidos(self, v, w)
# peso_arista(self, v, w)
# obtener_vertices(self)
#   Devuelve una lista con todos los vértices del grafo
# vertice_aleatorio(self)
# adyacentes(self, v)
# str

def no_hay_adyacentes(grafo, puestos):
    for v in puestos:
        for w in puestos:
            if v != w and grafo.estan_unidos(v, w):
                return False
    return True    

def llego_a_n(vertices, v_actual, puestos, n):
    return len(puestos) + (len(vertices) - v_actual) >= n

def _poner_v_no_adyacentes(grafo, vertices, v_actual, puestos, n):
    if v_actual == len(vertices):
        return False
    if len(puestos) == n:
        return no_hay_adyacentes(grafo, puestos)
    
    if not no_hay_adyacentes(grafo, puestos) or not llego_a_n(vertices, v_actual, puestos, n):
        return False
    
    puestos.add(vertices[v_actual])
    if _poner_v_no_adyacentes(grafo, vertices, v_actual + 1, puestos, n):
        return True
    puestos.remove(vertices[v_actual])
    return _poner_v_no_adyacentes(grafo, vertices, v_actual + 1, puestos, n)

def no_adyacentes(grafo, n):
    vertices = grafo.obtener_vertices()
    return _poner_v_no_adyacentes(grafo, vertices, 0, set(), n)