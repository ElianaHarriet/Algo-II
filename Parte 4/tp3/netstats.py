import sys
import heapq
from grafo import *
from biblioteca import *

# - # - # - # - # - # - # Constantes # - # - # - # - # - # - #

MAX_ITERACIONES =  21
RECURSION_LIMIT = 50000
LIMITE_ADYACENTES = 2

# - # - # - # - # - # Funciones auxiliares # - # - # - # - # - #

def armar_camino(padre, origen, destino):
    camino = []
    v = destino
    while v != origen:
        camino.append(v)
        v = padre[v]
    camino.append(origen)
    return camino[::-1]

def lista_a_set(lista):
    s = set()
    for v in lista:
        s.add(v)
    return s

# - # - # - # - # Funciones principales de Netstats # - # - # - # - #

############# - || Comando: listar_operaciones || - #############

def listar_operaciones():
    print("camino") 
    print("mas_importantes") 
    print("conectados") 
    print("ciclo") 
    print("lectura") 
    print("diametro")  
    print("rango") 
    print("comunidad")
    print("navegacion") 
    print("clustering") 

################### - || Comando: camino || - ###################

def camino_minimo(grafo, origen, destino):
    padre, distancia = bfs(grafo, origen, destino)
    if not destino in distancia:
        return None
    return armar_camino(padre, origen, destino)

################## - || Comando: diametro || - ##################

def diametro(grafo):
    max_min_dist = 0
    inicio = None
    destino = None
    padres = None

    for v in grafo.obtener_vertices():
        padre, distancias = bfs(grafo, v)
        for w in distancias:
            if distancias[w] != None and distancias[w] > max_min_dist:
                max_min_dist = distancias[w]
                inicio = v
                destino = w
                padres = padre

    return armar_camino(padres, inicio, destino)

#################### - || Comando: rango || - ####################

def rango(grafo, p, n):
    _, distancias = bfs(grafo, p, None, n)
    return len([v for v in distancias if distancias[v] == int(n)])

################## - || Comando: navegacion || - ##################

def navegacion(grafo, origen):
    actual = origen
    navegacion = []
    navegacion.append(actual)

    while len(grafo.adyacentes(actual)) > 0:
        actual = grafo.adyacentes(actual)[0]
        navegacion.append(actual)
        if len(navegacion) == MAX_ITERACIONES:
            break

    return navegacion

################## - || Comando: conectados || - ##################

def conectados(grafo, vertice):
    sys.setrecursionlimit(RECURSION_LIMIT)
    todas_cfc = buscar_cfcs(grafo, vertice)
    for cfc in todas_cfc:
        if vertice in cfc:
            return cfc
    return []

################### - || Comando: lectura || - ###################

def lectura(grafo, lista):
    set_lectura = lista_a_set(lista)
    salida= grados_salida(grafo, set_lectura)
    entradas = vertices_entrada(grafo, set_lectura)
    cola = deque()

    for vertice in lista:
        if salida[vertice] == 0:
            cola.append(vertice)

    orden = []
    while not len(cola) == 0:
        vertice = cola.popleft()
        orden.append(vertice)
        entradas_v = entradas[vertice]
        for v in entradas_v:
            if v in set_lectura:
                salida[v] -= 1
                if salida[v] == 0:
                    cola.append(v)

    if len(orden) != len(lista): # Hay ciclo o no no hay suficientes
        return None
    
    return orden
    
################## - || Comando: comunidad || - ##################

def comunidades(grafo, vertice):
    i = 0
    labels = {}
    dict_comunidad  = {} 

    for v in grafo.obtener_vertices():
        dict_comunidad[i] = set()
        dict_comunidad[i].add(v)
        labels[v] = i
        i += 1
        
    entradas = vertices_entrada(grafo)
    label_propagation(grafo, vertice, labels, dict_comunidad, entradas)

    for comunidad in dict_comunidad.values():
        if vertice in comunidad:
            return comunidad

################ - || Comando: mas_importantes || - ################

def mas_importantes(grafo, cantidad):
    salidas = grados_salida(grafo) # O(P + L)
    n = len(grafo.obtener_vertices())
    pr_vertices = {vertice: 1/n for vertice in grafo.obtener_vertices()} # O(P)
    
    boolean = True
    while boolean:
        boolean = pr(grafo, salidas, n, pr_vertices)   # O(P + L)
        
    heap = []    #USAMOS HEAP PARA SATIFACER LA COMPLEJIDAD DE O(P LOG(N))
    i = 0
    for vertice in pr_vertices:           # O(P LOG(N)) 
        if i < cantidad:
            heapq.heappush(heap, (pr_vertices[vertice], vertice)) 
            i += 1
        else:
            if pr_vertices[vertice] > heap[0][0]:
                heapq.heappop(heap)
                heapq.heappush(heap, (pr_vertices[vertice], vertice))

    importantes = []
    while not len(heap) == 0:     # O(N LOG(N))
        importantes.append(heapq.heappop(heap)[1])
    return importantes[::-1]
        
#################### - || Comando: ciclo || - ####################

def ciclo(grafo, vertice, n):
    visitados = set()
    return obtener_ciclo(grafo, vertice, vertice, [], visitados, n)

################ - || Comando: clustering || - ################

def clustering(grafo, vertice):
    adyacentes = grafo.adyacentes(vertice)
    if len(adyacentes) < LIMITE_ADYACENTES:
        return 0
    suma = 0
    for v in adyacentes:
        for w in adyacentes:
            if w != v  and v != vertice and grafo.estan_unidos(v, w):
                suma += 1
    return float(format(suma / (len(adyacentes) * (len(adyacentes) - 1)), '.3f'))

def clustering_global(grafo):
    vertices = grafo.obtener_vertices()
    suma = 0
    for v in vertices:
        suma += clustering(grafo, v)
    return float(format(suma / len(vertices), '.3f'))