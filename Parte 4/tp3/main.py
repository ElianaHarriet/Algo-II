#!/usr/bin/python3
from netstats import *
import sys

def maquina(grafo):
    for line in sys.stdin:

        comando_parametros = line.rstrip()
        comando = comando_parametros.split(" ")[0]
        parametros = " ".join(comando_parametros.split(" ")[1:]).split(",")

        if comando == "listar_operaciones":
            listar_operaciones()

        elif comando == "camino":
            desde = parametros[0]
            hasta = parametros[1]
            camino = camino_minimo(grafo, desde, hasta)
            if camino:
                print(" -> ".join(camino))
                print("Costo: ", len(camino) - 1)
            else:
                print("No se encontro recorrido")
        
        elif comando == "mas_importantes":
            cantidad = int(parametros[0])
            importantes = mas_importantes(grafo, cantidad)
            print(", ".join(importantes))
        
        elif comando == "conectados":
            pagina = parametros[0]
            conectados_ = conectados(grafo, pagina)
            print(", ".join(conectados_))
        
        elif comando == "ciclo":
            pagina = parametros[0]
            n = int(parametros[1])
            ciclo_ = ciclo(grafo, pagina, n)
            print("No se encontro recorrido" if not ciclo_ else " -> ".join(ciclo_))
        
        elif comando == "lectura":
            paginas = parametros
            lectura_ = lectura(grafo,paginas)
            print(", ".join(lectura_) if lectura_ else "No existe forma de leer las paginas en orden")
        
        elif comando == "diametro":
            diametro_ = diametro(grafo)
            print(" -> ".join(diametro_))
            print("Costo: ", len(diametro_) - 1)

        elif comando == "rango":
            pagina = parametros[0]
            n = parametros[1]
            rango_ = rango(grafo, pagina, n)
            print(rango_)

        elif comando == "comunidad":
            pagina = parametros[0]
            comunidad_ = comunidades(grafo,pagina)
            print(", ".join(comunidad_))
            print(len(comunidad_))

        elif comando == "navegacion":
            pagina = parametros[0]
            navegacion_ = navegacion(grafo, pagina)
            print(" -> ".join(navegacion_))

        elif comando == "clustering":
            pagina = parametros[0] if len(parametros) > 0 else None
            clustering_ = clustering(grafo, pagina) if pagina else clustering_global(grafo)
            print(clustering_)
        
    
if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Cantidad de agrumentos inválida")
    else:
        grafo = Grafo()
        filename = sys.argv[1]
        with open(filename) as tsv:
            for linea in tsv:
                linea = linea.rstrip()
                arr = linea.split("\t")
                vertice = arr[0]
                aristas = arr[1:]
                grafo.agregar_vertice(vertice)
                for arista in aristas:
                    grafo.agregar_arista(vertice, arista)
        maquina(grafo)