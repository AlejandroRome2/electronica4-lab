#include "alumno.h"

#include <stdio.h>

/**
 * @brief Función principal del programa.
 *
 * Crea un alumno, serializa sus datos en formato JSON y muestra
 * el resultado por pantalla.
 *
 * @return 0 si finaliza correctamente, o 1 si ocurre un error.
 */

int main(void)
{
    alumno_t * alumno;
    char salida[128];
    int longitud;

    alumno = AlumnoCrear("Romero", "Enrique Alejandro", 43849747U);
    if (alumno == NULL)
    {
        printf("Error al crear alumno\n");
        return 1;
    }

    longitud = AlumnoSerializar(alumno, salida, sizeof(salida));
    if (longitud < 0)
    {
        printf("Error al serializar\n");
        AlumnoDestruir(alumno);
        return 1;
    }

    printf("%s\n", salida);

    AlumnoDestruir(alumno);

    return 0;
}