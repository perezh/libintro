/**
 * @file    intro.h
 * @brief   Libreria de apoyo para las primeras semanas de curso IS
 *          Busca evitar el uso de punteros y arrays sin haberse explicado.
 *
 * @author  Intro_SW
 * @version 2022.1
 *
 */


#ifndef _IS_H
#define _IS_H

/**
 * Tipo de dato: string
 */
typedef char *string;

/**
 * @brief Pide al usuario que introduzca un num. entero.
 * @returns el entero introducido por el usuario, finaliza en caso de error
 *
 */
int get_user_int (void);

/**
 * @brief Pide al usuario que introduzca un num. entero largo
 * @returns el entero largo introducido por el usuario o termina si ha habido algún error
 *
 */
long get_user_long (void);

/**
 * @brief Pide al usuario que introduzca un num. real.
 * @returns el real introducido por el usuario, finaliza en caso de error
 *
 */
float get_user_float (void);


/**
 * @brief Pide al usuario que introduzca un num. real
 * @returns el num. real (doble precision) introducido por el usuario o termina si ha habido algún error
 *
 */
double get_user_double (void);

/**
 * @brief Pide al usuario que introduzca un string.
 * @returns el string introducido por el usuario, finaliza en caso de error
 *
 */
string get_user_string (void);

/**
 * @brief Pide al usuario que introduzca un carácter.
 * Esta función admite los caracteres de la tabla ASCII estándar (códigos desde 1 a 127)
 * @returns el carácter introducido por el usuario o termina si ha habido algún error
 *
 */
char get_user_char (void);

/**
 * @brief Libera los recursos utilizados por la libreria.
 * @returns void
 *
 */
void finalize (void);

/**
 * @brief Borra el contenido del terminal. Esta llamada es dependiente
 * del sistema operativo y puede no ser soportada por tu sistema
 * @returns void
 *
 */
void clear_terminal (void);

/**
 * @brief Retorna un numero real aleatorio entre 0 (incluido) y 1 (excluido).
 *        No es necesario inicializar la semilla del generador de números.
 * @returns el numero real aleatorio
 *
 *
 */
float random_float (void);

#endif
