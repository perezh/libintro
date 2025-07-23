/**
 * @file    intro.c
 * @brief   Libreria de apoyo para las primeras semanas de curso IS
 *          Busca evitar el uso de punteros y arrays sin haberse explicado.
 *
 *
 * @author  Intro_SW <perezh@unican.es>
 * @version 2020.1
 *
 */
#define _GNU_SOURCE
#include "intro.h"
#include <stdlib.h>
// Check for errors
#include <limits.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>  // Concept of finite and infinite
#include <float.h> // Limits for floating point
#include <ctype.h> // Character checks

/**
 * @brief Macro 'CHK'. Comprueba los errores de las funciones POSIX que NO modifican la variable "errno".
 * Las funciones devuelven cero si se ejecutan correctamente, en otro caso devuelven un número con el error.
 * @param p Funcion a comprobar
 * @returns termina la ejecucion si existe error
 *
 */
#define CHK(p) { int ret;                                      \
                 if ((ret = p)) {                  \
                   printf ("Error: "#p": %s\n", strerror (ret)); \
                   exit (EXIT_FAILURE);                                  \
                 }                                             \
               }

/**
 * @brief Macro 'ERROR'. Muestra los errores de las funciones POSIX que modifican la variable "errno".
 * @param s String a mostrar
 * @returns termina la ejecucion al existir error
 *
 */
#define ERROR(s) {  perror((s));\
                    exit(EXIT_FAILURE); }

/**
 * @brief Elimina el caracter \n si se encuentra al final de un string
 * @param line String a procesar
 * @param chars la longitud del string
 * @returns el número de caracteres del string resultante
 *
 */
static int remove_trailing_newline (char *line, int size) {
    int index = size;
    if (index > 0 && line[index - 1] == '\n') {
        line[index - 1] = '\0';
        index--;
    }
    return index;
}

/**
 * @brief Comprueba si el string está vacío
 * @param line String a procesar
 * @returns true si el string está vacío, false en caso contrario
 *
 */
static bool is_empty_string (char *line) {
    bool result = true;
    if (*line != '\0') { // If it's not null terminated character, input is incorrect
        result = false;
    }
    return result;
}

/**
 * Array de strings reservados por get_user_string.
 */
static string *strings = NULL;
/**
 * Numero de strings reservados por get_user_string.
 */
static size_t allocations = 0;

/**
 * @brief Pide al usuario que introduzca un entero
 * @returns el entero introducido por el usuario o termina si ha habido algun error
 *
 */
int get_user_int (void) {

    long result = 0;
    char *endptr, *line = NULL;
    size_t len = 0;
    int base = 10; // Decimal

    errno = 0;    /* To distinguish success/failure after call */
    int chars = getline (&line, &len, stdin);
    if (chars < 0) { // if line is null, getline internally allocates memory for the string
        ERROR ("getline");
    }
    chars = remove_trailing_newline (line, chars);

    result = strtol (line, &endptr, base);  // endptr is the remaining string that cannot be converted
    if (!is_empty_string (endptr)) {        // If it's not null terminated character, input is incorrect
        fprintf (stderr, "Input data error\n");
        exit (EXIT_FAILURE);
    }

    if (errno == ERANGE || (errno != 0 && result == 0)) {
        ERROR ("strtol");
    }

    // As strol is for long, we need to check the range after
    if (result > INT_MAX || result < INT_MIN) {
        fprintf (stderr, "Number out of the valid range [%d, %d]\n", INT_MIN, INT_MAX);
        exit (EXIT_FAILURE);
    }

    if (endptr == line) {
        fprintf (stderr, "No digits were found\n");
        exit (EXIT_FAILURE);
    }
    free (line);

    return (int) result;
}

/**
 * @brief Pide al usuario que introduzca un entero largo
 * @returns el entero largo introducido por el usuario o termina si ha habido algun error
 *
 */
long get_user_long (void) {

    long result = 0;
    char *endptr, *line = NULL;
    size_t len = 0;
    int base = 10; // Decimal

    errno = 0;    /* To distinguish success/failure after call */
    int chars = getline (&line, &len, stdin);
    if (chars < 0) { // if line is null, getline internally allocates memory for the string
        ERROR ("getline");
    }
    chars = remove_trailing_newline (line, chars);

    result = strtol (line, &endptr, base);

    if (!is_empty_string (endptr)) {  // If it's not a control character (\0, \n, \r)
        fprintf (stderr, "Input data error\n");
        exit (EXIT_FAILURE);
    }

    if (errno == ERANGE || result > LONG_MAX || result < LONG_MIN || (errno != 0 && result == 0)) {
        ERROR ("strtol");
    }
    if (endptr == line) {
        fprintf (stderr, "No digits were found\n");
        exit (EXIT_FAILURE);
    }
    free (line);

    return result;
}

/**
 * @brief Pide al usuario que introduzca un real
 * @returns el real introducido por el usuario o termina si ha habido algun error
 *
 */
float get_user_float (void) {

    float result = 0.0;

    char *endptr, *line = NULL;
    size_t len = 0;

    errno = 0;    /* To distinguish success/failure after call */
    int chars = getline (&line, &len, stdin);
    if (chars < 0) {
        ERROR ("getline");
    }
    // Remove trailing newline, if exists
    chars = remove_trailing_newline (line, chars);

    result = strtof (line, &endptr);

    if (!is_empty_string (endptr)) {  // If it's not null terminated character, input is incorrect
        fprintf (stderr, "Input data error\n");
        exit (EXIT_FAILURE);
    }

    if (errno == ERANGE || (errno != 0 && result == 0)) {
        ERROR ("strtof");
    }

    // For float types, is not so easy so the strictest check is comparing
    // the digits with the expected decimal digits of precission (FLT_DIG). However, the
    // precision depends on the most significative part (integer)
    if (isfinite (result) == 0 || result > FLT_MAX) {
        fprintf (stderr, "Number out of the valid range\n"); // Precision
        exit (EXIT_FAILURE);
    }

    if (endptr == line) {
        fprintf (stderr, "No digits were found\n");
        exit (EXIT_FAILURE);
    }
    free (line);

    return result;

}

/**
 * @brief Pide al usuario que introduzca un numero real
 * @returns el num. real (doble precision) introducido por el usuario o termina si ha habido algun error
 *
 */
double get_user_double (void) {

    double result = 0.0;

    char *endptr, *line = NULL;
    size_t len = 0;

    errno = 0;    /* To distinguish success/failure after call */
    int chars = getline (&line, &len, stdin);
    if (chars < 0) {
        ERROR ("getline");
    }
    // Remove trailing newline, if exists
    chars = remove_trailing_newline (line, chars);

    result = strtod (line, &endptr);

    if (!is_empty_string (endptr)) {  // If it's not null terminated character, input is incorrect
        fprintf (stderr, "Input data error\n");
        exit (EXIT_FAILURE);
    }

    if (errno == ERANGE || (errno != 0 && result == 0)) {
        ERROR ("strtod");
    }

    // For double types, is not so easy so the strictest check is comparing
    // the len with the expected decimal digits of precission (DBL_DIG). However, the
    // precision depends on the most significative part (integer)
    if (isfinite (result) == 0 || result > DBL_MAX) {
        fprintf (stderr, "Number out of the valid range\n"); // Precision
        exit (EXIT_FAILURE);
    }

    if (endptr == line) {
        fprintf (stderr, "No digits were found\n");
        exit (EXIT_FAILURE);
    }
    free (line);

    return result;

}

/**
 * @brief Pide al usuario que introduzca un string
 * @returns el string introducido por el usuario o termina si ha habido algun error
 *
 */
string get_user_string (void) {

    char *result = NULL;
    size_t len = 0;
    size_t chars = 0;

    errno = 0;    /* To distinguish success/failure after call */
    if ((chars = getline (&result, &len, stdin)) < 0) {
        ERROR ("getline");
    }

    // Remove trailing newline, if exists
    chars = remove_trailing_newline (result, chars);

    // resize strings array to add the new one
    string *tmp = realloc (strings, sizeof (string) * (allocations + 1));
    if (tmp == NULL) {
        ERROR ("realloc");
    }

    // assign new space to the array of strings
    strings = tmp;

    // add new string
    strings[allocations] = result;
    allocations++;

    return result;
}

/**
 * @brief Pide al usuario que introduzca un carácter.
 * Esta función admite los caracteres de la tabla ASCII estándar (códigos desde 1 a 127)
 * @returns el carácter introducido por el usuario o termina si ha habido algun error
 *
 */
char get_user_char (void) {
    char result, end;
    string text = get_user_string ();
    // Return a char only if a single char is provided
    if (sscanf(text, "%c%c", &result, &end) != 1) {
        fprintf (stderr, "Input data error. A single regular ASCII character should be introduced\n");
        exit (EXIT_FAILURE);
    }
    return result;
}

/**
 * @brief libera los recursos de la libreria de apoyo.
 * @returns void
 *
 */
void finalize (void) {
    // free string resources
    if (strings != NULL) {
        for (size_t i = 0; i < allocations; i++) {
            free (strings[i]);
        }
        free (strings);
        // Reset variables
        strings = NULL;
        allocations = 0;
    }
}

/**
 * @brief Borra el contenido del terminal. Esta llamada es dependiente
 * del sistema operativo y puede no ser soportada por tu sistema
 * @returns void
 *
 */
void clear_terminal (void) {
    printf ("\n"); // Output any remaining data in buffer
    int result = system ("clear"); // OS-dependent, use #ifdef __linux__ / __WIN32__ to support Windows
    if (result == -1) {
        fprintf (stderr,
                 "This command is os-dependent and is not supported by your system\n");
        exit (EXIT_FAILURE);
    }
}

/**
 * Variable para inicializar la semilla de números aleatorios.
 */
static bool seed_computed = false;  // Cambiar a variable local estática

/**
 * @brief Retorna un numero real aleatorio entre 0 (incluido) y 1 (excluido).
 * @returns el numero real alteatorio
 *
 */
float random_float (void) {
    // Inicializamos números aleatorios
    if (!seed_computed) {
        srand (time (NULL));
        seed_computed = true;
    }

    int random_integer = rand();
    // Float [0.0, 1.0)
    float result = (float) random_integer / (float) ((long) RAND_MAX + 1);
    return result;
}
