#include "alumno.h"

#include <stdio.h>
#include <string.h>

#define JSON_LLAVE_ABRE "{"
#define JSON_LLAVE_CIERRA "}"
#define JSON_CLAVE_NOMBRE "\"nombre\":\""
#define JSON_CLAVE_APELLIDO "\",\"apellido\":\""
#define JSON_CLAVE_DOCUMENTO "\",\"documento\":"

/**
 * @brief Serializa una cadena de texto en la salida.
 *
 * Copia el texto recibido dentro de la cadena de salida, siempre que
 * exista espacio suficiente.
 *
 * @param[out] salida Cadena donde se copia el texto.
 * @param[in] capacidad Cantidad de bytes disponibles en la salida.
 * @param[in] texto Cadena de texto a copiar.
 *
 * @return Cantidad de caracteres copiados, o -1 si no hay espacio suficiente.
 */
static int SerializarTexto(char * salida, size_t capacidad, char const * texto);

/**
 * @brief Serializa un valor numérico en la salida.
 *
 * Convierte el número recibido a texto decimal y lo copia en la cadena
 * de salida, siempre que exista espacio suficiente.
 *
 * @param[out] salida Cadena donde se copia el número convertido.
 * @param[in] capacidad Cantidad de bytes disponibles en la salida.
 * @param[in] valor Número a serializar.
 *
 * @return Cantidad de caracteres copiados, o -1 si no hay espacio suficiente.
 */
static int SerializarNumero(char * salida, size_t capacidad, unsigned int valor);

/**
 * @brief Genera una cadena JSON con los datos de un alumno.
 *
 * La función construye una cadena con el formato:
 * {"nombre":"...","apellido":"...","documento":...}
 *
 * @param[in] alumno Puntero a la estructura con los datos del alumno.
 * @param[out] salida Cadena donde se almacena el resultado.
 * @param[in] capacidad Cantidad de bytes disponibles en la cadena de salida.
 *
 * @return Longitud de la cadena generada, o -1 si el espacio no es suficiente
 *         o si los punteros recibidos no son válidos.
 */
int Serializar(alumno_t const * alumno, char * salida, size_t capacidad)
{
    size_t usados;
    int escritos;

    if ((alumno == NULL) || (salida == NULL))
    {
        return -1;
    }

    usados = 0U;

    escritos = SerializarTexto(salida + usados, capacidad - usados, JSON_LLAVE_ABRE);
    if (escritos < 0)
    {
        return -1;
    }
    usados += (size_t)escritos;

    escritos = SerializarTexto(salida + usados, capacidad - usados, JSON_CLAVE_NOMBRE);
    if (escritos < 0)
    {
        return -1;
    }
    usados += (size_t)escritos;

    escritos = SerializarTexto(salida + usados, capacidad - usados, alumno->nombre);
    if (escritos < 0)
    {
        return -1;
    }
    usados += (size_t)escritos;

    escritos = SerializarTexto(salida + usados, capacidad - usados, JSON_CLAVE_APELLIDO);
    if (escritos < 0)
    {
        return -1;
    }
    usados += (size_t)escritos;

    escritos = SerializarTexto(salida + usados, capacidad - usados, alumno->apellido);
    if (escritos < 0)
    {
        return -1;
    }
    usados += (size_t)escritos;

    escritos = SerializarTexto(salida + usados, capacidad - usados, JSON_CLAVE_DOCUMENTO);
    if (escritos < 0)
    {
        return -1;
    }
    usados += (size_t)escritos;

    escritos = SerializarNumero(salida + usados, capacidad - usados, alumno->documento);
    if (escritos < 0)
    {
        return -1;
    }
    usados += (size_t)escritos;

    escritos = SerializarTexto(salida + usados, capacidad - usados, JSON_LLAVE_CIERRA);
    if (escritos < 0)
    {
        return -1;
    }
    usados += (size_t)escritos;

    salida[usados] = '\0';

    return (int)usados;
}

static int SerializarTexto(char * salida, size_t capacidad, char const * texto)
{
    size_t longitud;

    longitud = strlen(texto);

    if (capacidad <= longitud)
    {
        return -1;
    }

    memcpy(salida, texto, longitud);

    return (int)longitud;
}

static int SerializarNumero(char * salida, size_t capacidad, unsigned int valor)
{
    char buffer[16];
    int longitud;

    longitud = sprintf(buffer, "%u", valor);
    if (longitud < 0)
    {
        return -1;
    }

    if (capacidad <= (size_t)longitud)
    {
        return -1;
    }

    memcpy(salida, buffer, (size_t)longitud);

    return longitud;
}