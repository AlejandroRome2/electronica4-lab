#include "alumno.h"

#include <stdio.h>

int main(void)
{
    alumno_t alumno = {"Enrique Alejandro", "Romero", 43849747};
    char salida[128];
    int longitud;

    longitud = Serializar(&alumno, salida, sizeof(salida));
    if (longitud < 0)
    {
        printf("Error al serializar\n");
        return 1;
    }

    printf("%s\n", salida);

    return 0;
}