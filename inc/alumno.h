#ifndef ALUMNO_H
#define ALUMNO_H

#include <stddef.h>

/**
 * @brief Tipo de dato opaco para representar un alumno.
 */
typedef struct alumno_s alumno_t;

/**
 * @brief Crea un alumno con apellido, nombre y documento.
 *
 * @param[in] apellido Cadena con el apellido del alumno.
 * @param[in] nombre Cadena con el nombre del alumno.
 * @param[in] documento Documento del alumno.
 *
 * @return Puntero al alumno creado, o NULL si no se pudo crear.
 */
alumno_t * AlumnoCrear(char const * apellido, char const * nombre, unsigned int documento);

/**
 * @brief Libera o invalida un alumno creado previamente.
 *
 * @param[in] alumno Puntero al alumno a destruir.
 */
void AlumnoDestruir(alumno_t * alumno);

/**
 * @brief Serializa los datos de un alumno en formato JSON.
 *
 * @param[in] alumno Puntero al alumno a serializar.
 * @param[out] salida Arreglo de caracteres donde se almacena el resultado.
 * @param[in] capacidad Cantidad de bytes disponibles en la salida.
 *
 * @return Longitud de la cadena generada, o -1 si el espacio no es suficiente
 *         o si los parámetros no son válidos.
 */
int AlumnoSerializar(alumno_t const * alumno, char * salida, size_t capacidad);

#endif