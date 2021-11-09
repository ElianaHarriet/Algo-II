#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "hash_struct.h"
#include "testing.h"

void test() {
    hash_t* hash = hash_crear();
    hash_guardar(hash, "Mondi", "miau");
    hash_guardar(hash, "Viena", "miu");
    hash_guardar(hash, "Mruzka", "miauczec");
    hash_borrar(hash, "Mondi");
    print_test("test1", !hash_pertenece(hash, "Mondi"));
    print_test("test2", hash_pertenece(hash, "Viena"));
    print_test("test3", hash_pertenece(hash, "Mruzka"));
    print_test("test4", hash_obtener(hash, "Mondi") == NULL);
    print_test("test5", strcmp(hash_obtener(hash, "Viena"), "miu") == 0);
    print_test("test6", strcmp(hash_obtener(hash, "Mruzka"), "miauczec") == 0);
    print_test("test7", hash_cantidad(hash) == 2);
    hash_borrar(hash, "Viena");
    print_test("test8", !hash_pertenece(hash, "Mondi"));
    print_test("test9", !hash_pertenece(hash, "Viena"));
    print_test("test10", hash_pertenece(hash, "Mruzka"));
    print_test("test11", hash_obtener(hash, "Viena") == NULL);
    print_test("test12", hash_cantidad(hash) == 1);
    hash_destruir(hash);
}

int main() {
    test();
    return 0;
}