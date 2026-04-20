#include "alumno.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALUMNO_NOMBRE_MAX 32
#define ALUMNO_APELLIDO_MAX 32

#define ALUMNO_MEMORIA_DINAMICA 1
#define ALUMNO_MAXIMO_ESTATICO 4

#define JSON_LLAVE_ABRE "{"
#define JSON_LLAVE_CIERRA "}"
#define JSON_CLAVE_NOMBRE "\"nombre\":\""
#define JSON_CLAVE_APELLIDO "\",\"apellido\":\""
#define JSON_CLAVE_DOCUMENTO "\",\"documento\":"

/**
 * @brief Serializa un campo de texto en la salida.
 *
 * @param[out] salida Cadena donde se copia el texto.
 * @param[in] capacidad Cantidad de bytes disponibles en la salida.
 * @param[in] texto Texto a copiar.
 *
 * @return Cantidad de caracteres copiados, o -1 si no hay espacio suficiente.
 */
static int SerializarTexto(char * salida, size_t capacidad, char const * texto);

/**
 * @brief Serializa un campo numérico en la salida.
 *
 * @param[out] salida Cadena donde se copia el número convertido.
 * @param[in] capacidad Cantidad de bytes disponibles en la salida.
 * @param[in] valor Número a serializar.
 *
 * @return Cantidad de caracteres copiados, o -1 si no hay espacio suficiente.
 */
static int SerializarNumero(char * salida, size_t capacidad, unsigned int valor);

/**
 * @brief Estructura privada que almacena el estado de un alumno.
 */
struct alumno_s
{
    /** @brief Nombre del alumno. */
    char nombre[ALUMNO_NOMBRE_MAX];

    /** @brief Apellido del alumno. */
    char apellido[ALUMNO_APELLIDO_MAX];

    /** @brief Documento del alumno. */
    unsigned int documento;
};

#if !ALUMNO_MEMORIA_DINAMICA
static alumno_t alumnos_estaticos[ALUMNO_MAXIMO_ESTATICO];
static int alumnos_en_uso[ALUMNO_MAXIMO_ESTATICO];
#endif

static int SerializarTexto(char * salida, size_t capacidad, char const * texto);
static int SerializarNumero(char * salida, size_t capacidad, unsigned int valor);

/**
 * @brief Crea un alumno.
 *
 * La creación puede realizarse usando memoria dinámica o memoria estática
 * interna del módulo, según la configuración de compilación.
 *
 * @param[in] apellido Cadena con el apellido del alumno.
 * @param[in] nombre Cadena con el nombre del alumno.
 * @param[in] documento Documento del alumno.
 *
 * @return Puntero al alumno creado, o NULL si no se pudo crear.
 */


alumno_t * AlumnoCrear(char const * apellido, char const * nombre, unsigned int documento)
{
    alumno_t * alumno;

#if !ALUMNO_MEMORIA_DINAMICA
    int i;
#endif

    if ((apellido == NULL) || (nombre == NULL))
    {
        return NULL;
    }

#if ALUMNO_MEMORIA_DINAMICA
    alumno = malloc(sizeof(alumno_t));
    if (alumno == NULL)
    {
        return NULL;
    }
#else
    alumno = NULL;

    for (i = 0; i < ALUMNO_MAXIMO_ESTATICO; i++)
    {
        if (alumnos_en_uso[i] == 0)
        {
            alumnos_en_uso[i] = 1;
            alumno = &alumnos_estaticos[i];
            break;
        }
    }

    if (alumno == NULL)
    {
        return NULL;
    }
#endif

    strncpy(alumno->apellido, apellido, ALUMNO_APELLIDO_MAX - 1U);
    alumno->apellido[ALUMNO_APELLIDO_MAX - 1U] = '\0';

    strncpy(alumno->nombre, nombre, ALUMNO_NOMBRE_MAX - 1U);
    alumno->nombre[ALUMNO_NOMBRE_MAX - 1U] = '\0';

    alumno->documento = documento;

    return alumno;
}

/**
 * @brief Destruye un alumno creado previamente.
 *
 * En modo dinámico libera la memoria reservada. En modo estático marca
 * nuevamente el registro como disponible.
 *
 * @param[in] alumno Puntero al alumno a destruir.
 */

void AlumnoDestruir(alumno_t * alumno)
{
#if ALUMNO_MEMORIA_DINAMICA
    if (alumno != NULL)
    {
        free(alumno);
    }
#else
    int i;

    if (alumno == NULL)
    {
        return;
    }

    for (i = 0; i < ALUMNO_MAXIMO_ESTATICO; i++)
    {
        if (alumno == &alumnos_estaticos[i])
        {
            alumnos_en_uso[i] = 0;
            alumnos_estaticos[i].nombre[0] = '\0';
            alumnos_estaticos[i].apellido[0] = '\0';
            alumnos_estaticos[i].documento = 0U;
            break;
        }
    }
#endif
}

/**
 * @brief Genera una cadena JSON con los datos de un alumno.
 *
 * @param[in] alumno Puntero al alumno a serializar.
 * @param[out] salida Arreglo de caracteres donde se almacena el resultado.
 * @param[in] capacidad Cantidad de bytes disponibles en la salida.
 *
 * @return Longitud de la cadena generada, o -1 si el espacio no es suficiente
 *         o si los parámetros no son válidos.
 */

int AlumnoSerializar(alumno_t const * alumno, char * salida, size_t capacidad)
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