#include "alumno.h"

#include <stdio.h>
#include <string.h>

#define JSON_LLAVE_ABRE "{"
#define JSON_LLAVE_CIERRA "}"
#define JSON_CLAVE_NOMBRE "\"nombre\":\""
#define JSON_CLAVE_APELLIDO "\",\"apellido\":\""
#define JSON_CLAVE_DOCUMENTO "\",\"documento\":"
#define JSON_COMILLA_CIERRE "\""

static int SerializarTexto(char * salida, size_t capacidad, char const * texto);
static int SerializarNumero(char * salida, size_t capacidad, unsigned int valor);

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