#ifndef ALUMNO_H
#define ALUMNO_H

#include <stddef.h>

/** @brief Cantidad máxima de caracteres para el nombre. */
#define ALUMNO_NOMBRE_MAX 32

/** @brief Cantidad máxima de caracteres para el apellido. */
#define ALUMNO_APELLIDO_MAX 32

/**
 * @brief Estructura con la información de un alumno.
 */
typedef struct
{
    /** @brief Nombre del alumno. */
    char nombre[ALUMNO_NOMBRE_MAX];

    /** @brief Apellido del alumno. */
    char apellido[ALUMNO_APELLIDO_MAX];

    /** @brief Documento del alumno. */
    unsigned int documento;
} alumno_t;

/**
 * @brief Serializa los datos de un alumno en formato JSON.
 *
 * Genera una cadena JSON con el nombre, apellido y documento del alumno.
 *
 * @param[in] alumno Puntero a la estructura con los datos del alumno.
 * @param[out] salida Cadena donde se almacena el resultado.
 * @param[in] capacidad Cantidad de bytes disponibles en la cadena de salida.
 *
 * @return Longitud de la cadena generada, o -1 si el espacio no es suficiente
 *         o si los punteros recibidos no son válidos.
 */
int Serializar(alumno_t const * alumno, char * salida, size_t capacidad);

#endif