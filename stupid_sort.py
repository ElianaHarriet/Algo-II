import random

def random_list():
    list = []
    for _ in range(random.randint(1, 7)):
        list.append(random.randint(-1000, 1000))
    return list

def stupid_sort(list):
    ordenada = sorted(list)
    intentos = 0

    while not list == ordenada:
        intentos += 1
        random.shuffle(list)
        print(f"Lista -> {list} | Intentos -> {intentos}")
    return list, intentos

def main():
    list = random_list()
    print(f"܀Lista -> {list}܀\n܀Largo -> {len(list)}܀")
    ordenada, intentos = stupid_sort(list)
    print("¡ORDENADA!")
    print(f"܀Lista original -> {list}܀\n܀Lista ordenada -> {ordenada}܀\n܀Intentos -> {intentos}܀")

main()
