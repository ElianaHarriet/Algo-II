from random import shuffle

def orden_random(hasta, ignorados = []):
    lista = []
    for i in range(hasta):
        if i + 1 not in ignorados:
            lista.append(i + 1)
    shuffle(lista)
    return lista

def main():
    posponer = [1, 2, 5, 7, 8, 11, 14, 16, 18, 19]
    hechos = [3, 4, 6, 9, 10, 12, 13, 15, 17]
    porcentaje_hechos = round((len(hechos) / len(posponer + hechos)) * 100, 2)
    porcentaje_faltan = 100 - porcentaje_hechos
    print("Hacer -> ", orden_random(19, posponer + hechos))
    print("Porcentaje de ejercicios hechos: ", porcentaje_hechos, "%", sep= "")
    print("Porcentaje de ejercicios que faltan: ", porcentaje_faltan, "%", sep= "")

main()