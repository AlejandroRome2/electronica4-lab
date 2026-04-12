#include "alumno.h"

#include <stdio.h>

/**
 * @brief Función principal del programa.
 *
 * Crea una estructura con los datos del alumno, la serializa en formato
 * JSON y muestra el resultado por pantalla.
 *
 * @return 0 si la ejecución finaliza correctamente, o 1 si ocurre un error.
 */
int main(void)
{
    alumno_t alumno = {"Enrique Alejandro", "Romero", 43849747U};
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