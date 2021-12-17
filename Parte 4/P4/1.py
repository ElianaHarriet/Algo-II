# Dado un grafo G no dirigido, se desea implementar un algoritmo usando backtracking que permita numerar los V vértices
# con los números del 1 a |V|, de forma tal que no haya dos vértices adyacentes numerados con números consecutivos (por
# ejemplo, el vertice "a" no puede numerarse con 2, si existe un vértice adyacente que haya sido numerado previamente con 1
# o 3) y que no haya vertices numerados con el mismo número. De ser posible resolver el problema, el algoritmo debe devolver
# un diccionario que tenga por clave el vértice y por valor el número asignado.

def valido(grafo, v, asignados):
    for w in grafo.obtener_adyacentes(v):
        if w in asignados and abs(asignados[w] - asignados[v]) == 1:
            return False
    return True

def _numerar(grafo, numero, asignados, vertices):
    if len(asignados) == len(grafo):
        return asignados
    
    numero += 1
    for v in vertices:
        asignados[v] = numero
        vertices.remove(v)
        if not valido(grafo, v, asignados):
            asignados.remove(v)
            vertices.append(v)
            continue
        dicc = _numerar(grafo, numero, asignados, vertices)
        if dicc:
            return dicc
    
    asignados.remove(v)
    vertices.append(v)
    return None

def numerar(grafo):
    asignados = {}
    vertices = grafo.obtener_vertices()
    return _numerar(grafo, 0, asignados, vertices)
