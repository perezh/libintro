/*
 * File: test_intro.c
 *
 * Description: Check i/o operations provided by libintro
 *
 * Author:  Intro_SW <>
 * Version: 2020-07-23
 *
*/

#include <stdio.h>
#include "intro.h"

int main (void) {

    int    input1;
    string input2;

    // Clear shell
    clear_terminal();

    // Ask user input data
    printf ("Introduce un número entero: ");
    input1 = get_user_int();

    printf ("Introduce un texto: ");
    input2 = get_user_string();
   
    // Output data to screen
    printf ("Datos introducidos: %d, %s\n", input1, input2);

    // Free resources
    finalize();

    return 0;
}
