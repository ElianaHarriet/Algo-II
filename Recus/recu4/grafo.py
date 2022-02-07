import random

class Grafo:
    
    def __init__(self, esdirigido = True):
        self.vertices = []
        self.adyacencias = {}
        self.esdirigido = esdirigido
    
    def agregar_vertice(self, v):
        self.vertices.append(v)
        self.adyacencias[v] = {}
    
    def borrar_vertice(self,v):
        self.vertices.remove(v)
        del self.adyacencias[v]
        for w in self.vertices:
            if v in self.adyacencias[w]:
                del self.adyacencias[w][v]
        
    def obtener_vertices(self):
        return self.vertices
    
    def borrar_arista(self, v, w):
        if (self.estan_unidos(v, w)):
            del self.adyacencias[v][w]
            if not self.esdirigido:
                    del self.adyacencias[w][v]           
        
    def agregar_arista(self, v, w, peso = 1):
        self.adyacencias[v][w] = peso
        if not self.esdirigido:
            self.adyacencias[w][v] = peso
    
    def estan_unidos(self, v, w):
        return w in self.adyacencias[v]

    def peso_arista(self, v, w):
        if self.estan_unidos(v, w):
            return self.adyacencias[v][w]
    
    def adyacentes(self, v):
        return list(self.adyacencias[v])
    
    def vertice_aleatorio(self):
        return random.choice(self.vertices)
    
    def __str__(self):
        return str(self.adyacencias)