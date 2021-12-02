#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    while (1) {
        
        // GETLINE
        // Prueba leer línea con getline -> máx(leidos) = 4096

        char* linea = NULL;
        size_t capacidad = 0;
        ssize_t leidos = getline(&linea, &capacidad, stdin);
        linea[strlen(linea) - 1] = '\0';
        printf("%li\n", leidos);
        printf("%li\n", capacidad);

        //*//*//*//*//*//*//*//*//*//*//*//
        
        // FUNCIONA COMO GETLINE SIN USAR GETLINE
        // Prueba leer hasta linea con caracter == '\n' (funciona como getline) -> máx(leidos) = 4096
        
        // char* linea = NULL;
        // size_t capacidad = 0;
        // ssize_t leidos = getdelim(&linea, &capacidad, '\n', stdin);
        // linea[strlen(linea) - 1] = '\0';
        // printf("%li\n", leidos);
        // printf("%li\n", capacidad);

        //*//*//*//*//*//*//*//*//*//*//*//

        // != GETLINE
        // Prueba leer hasta linea con caracter != '\n' (getdelim) -> no hay máximo
        
        // char* linea = NULL;
        // size_t capacidad = 0;
        // ssize_t leidos = getdelim(&linea, &capacidad, '|', stdin);
        // linea[strlen(linea) - 1] = '\0';
        // printf("%li\n", leidos);
        // printf("%li\n", capacidad);

        //*//*//*//*//*//*//*//*//*//*//*//

        // FUNCIONA COMO GETLINE SIN USAR GETLINE
        // Prueba leer hasta caracter == '\n' (fgetc) -> máx(strlen(txt)) = 4096

        // char c = (char)fgetc(stdin);
        // char txt[120000] = "";
        // while (1) {
        //     txt[strlen(txt)] = c;
        //     txt[strlen(txt) + 1] = '\0';
        //     char c = (char)fgetc(stdin);
        //     if (c == '\n') {
        //         break;
        //     }
        // }
        // txt[strlen(txt)] = c;
        // txt[strlen(txt) + 1] = '\0';
        // printf("%li\n", strlen(txt));

    }
    return 0;
}
