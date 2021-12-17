from collections import deque
from random import shuffle

# - # - # - # - # - # - # Constantes # - # - # - # - # - # - #

ITERACIONES_LABEL = 50
DAMPING_FACTOR = 0.85
K = 0.0000001

# - # - # - # - # - # Funciones auxiliares # - # - # - # - # - #

def max_frecuencia(entradas, labels):
    """
    Función que devuelve la etiqueta que más se repite en un conjunto
    de vértices
    """
    frecuencias = {}
    for v in entradas:
        label_v = labels[v]
        frecuencias[label_v] = frecuencias.get(label_v, 0) + 1
    return max(frecuencias, key= frecuencias.get)


# - # - # - # - # - # - # - # - # - # - # - # - # - # - # - #
#              Biblioteca de funciones genéricas            #
#             para grafos no pesados y dirigidos            #
#      (Algunas funciones funcionan incluso para grafos     #
#       no dirigidos o pesados, pero no es el objetivo)     #
# - # - # - # - # - # - # - # - # - # - # - # - # - # - # - #

def bfs(grafo, origen, destino = None, n = None):
    """
    Busca los caminos minimos dado un vértice de origen
     - En caso de que se especifique un destino, se corta la busqueda
       cuando se encuentra el camino minimo hasta el destino
     - En caso de que se especifique un n, se corta la busqueda cuando
       ya se encontraron todos los caminos de longitud n
    """
    visitados = set()
    padres = {}
    orden = {}
    padres[origen] = None
    orden[origen] = 0

    visitados.add(origen)
    q = deque()
    q.append(origen)

    while len(q) > 0:
        v = q.popleft()
        for w in grafo.adyacentes(v):
            if w not in visitados:
                padres[w] = v
                orden[w] = orden[v] + 1
                visitados.add(w)
                q.append(w)

                if destino != None and w == destino:
                    return padres, orden
                if n != None and orden[w] > int(n):
                    return padres, orden

    return padres, orden


def componentes_fuertemente_conexas(grafo, v, cosas):
    """
    Algoritmo que busca las componentes fuertemente conexas de un grafo
    """
    visitados, apilados, todas_cfc, orden, mb, pila = cosas
    global orden_contador

    visitados.add(v)
    orden[v] = orden_contador
    mb[v] = orden[v]

    orden_contador += 1
    pila.appendleft(v)
    apilados.add(v)

    for w in grafo.adyacentes(v):
        if w not in visitados:
            cosas = [visitados, apilados, todas_cfc, orden, mb, pila]
            componentes_fuertemente_conexas(grafo, w, cosas)
        
        if w in apilados:
            mb[v] = min(mb[v], mb[w])
    
    if orden[v] == mb[v] and len(pila) > 0:
        nueva_cfc = []
        while True:
            w = pila.popleft()
            apilados.remove(w)
            nueva_cfc.append(w)
            if w == v:
                break

        todas_cfc.append(nueva_cfc)

def buscar_cfcs(grafo, vertice):
    """
    Función que devuelve las componentes fuertemente conexas de un grafo
    en una lista
    """
    cosas = [set(), set(), [], {}, {}, deque()]
    global orden_contador
    orden_contador = 0
    componentes_fuertemente_conexas(grafo, vertice, cosas)
    return cosas[2]


def grados_salida(grafo, set_lectura = None): 
    """
    Función que devuelve un diccionario con los grados de salida de cada vértice
     - En caso en que se especifique un set_lectura, se consideran únicamente los
       vértices que pertenecen a ese conjunto
    """
    grados = {}
    for v in set_lectura if set_lectura else grafo.obtener_vertices():
        grados[v] = 0
        for w in grafo.adyacentes(v):
            if not set_lectura or w in set_lectura:
                grados[v]+=1
    return grados


def vertices_entrada(grafo, set_lectura = None):
    """
    Función que devuelve un diccionario de sets con los vertices que apuntan a
    cada vértice
     - En caso en que se especifique un set_lectura, se consideran únicamente los
       vértices que pertenecen a ese conjunto
    """
    entrada = {}
    for v in set_lectura if set_lectura else grafo.obtener_vertices():
        entrada[v] = set()
    for v in set_lectura if set_lectura else grafo.obtener_vertices():
        for w in grafo.adyacentes(v):
            if not set_lectura or w in set_lectura:
                entrada[w].add(v)
    return entrada


def obtener_ciclo(grafo, origen, vertice, lista, visitados, n):
    """
    Busca por backtracking un ciclo en un grafo dado un origen, un vertice de
    origen y una cantidad determinada de vertices que debe tener el ciclo
    """
    if len(lista) == n:
        if vertice == origen:
            lista.append(vertice)
            return lista
        return None

    if vertice == origen and len(lista) != 0:
        return None

    lista.append(vertice)
    visitados.add(vertice)

    for w in grafo.adyacentes(vertice):
        if w not in visitados or w == origen: 
            if obtener_ciclo(grafo, origen, w, lista, visitados, n):
                return lista

    lista.pop()
    visitados.remove(vertice)
    return None


def label_propagation(grafo, vertice, labels, dict_comunidad, entradas):
    """
    Algoritmo de label propagation que propaga los labels de los vértices
    generando conjuntos de vertices
    """
    aleatorio = grafo.obtener_vertices()
    shuffle(aleatorio)
    
    i = 1
    while (i < ITERACIONES_LABEL):
        cambio = False
        for v in aleatorio:
            entradas_v = entradas[v]
            max_frec = max_frecuencia(entradas_v, labels) if len(entradas_v) > 0 else labels[v] # Si no hay entradas, se mantiene el label
            
            if labels[v] != max_frec:
                dict_comunidad[labels[v]].remove(v)
                dict_comunidad[max_frec].add(v)
                if not dict_comunidad[labels[v]]:
                    del dict_comunidad[labels[v]]
                labels[v] = max_frec
                cambio = True
        
        if not cambio:
            break
        i += 1
        
    if cambio:
        label_propagation(grafo, vertice, labels, dict_comunidad, entradas)


def pr(grafo, salidas, n, dict_pr): # -> O(P + L)
    """
    Algoritmo de PageRank, calcula la probabilidad para cada vértice
    del grafo de aparecer entre los adyacentes de otro vértice
    Devuelve True si convergió, False si no
    """
    vertices = grafo.obtener_vertices()

    dentro_sum = {}
    for v in vertices: # O(P)
        pr = dict_pr[v]   
        l = salidas[v]
        dentro_sum[v] = pr / l if l != 0 else 0
    
    sumas = {v: 0 for v in vertices} # O(P)
    for j in vertices:                   # } O(P + L)
        for i in grafo.adyacentes(j):    # }
            sumas[i] += dentro_sum[j]

    boolean = False
    for v in vertices: # O(P)
        pr_v = (1 - DAMPING_FACTOR) / n + DAMPING_FACTOR * sumas[v]
        if abs(pr_v - dict_pr[v]) > K: # Se define si converge o no
            boolean = True
            dict_pr[v] = pr_v

    return boolean