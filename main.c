/*
Auteur : Denis Gremaud
Version : 1.0.1
Date : 01.10.2019
Description : tp_03
*/
#include <stdio.h>  // used for printf/scanf
#include <stdint.h>  // used for printf/scanf
#include <stdbool.h>  // used for printf/scanf
#include <stdlib.h> // used for EXIT_SUCCESS
#include <time.h> // used for time(NULL)
#include "matrix.h"

int main() {
    int first_m = 5; 
    int second_n = 5;
    double donnee[first_m * second_n]; 
    srand(time(NULL));

    for (int i = 0; i < first_m * second_n; i++)
    {
        donnee[i] = rand() % 100;
    }

    matrix matr;
    matr = matrix_create_from_array(first_m, second_n, donnee);
    system("clear");
    matrix_print(matr);
    printf("%p\n", &matr);
    matrix matr2 = matrix_clone(matr);
    matrix_print(matr2);
    printf("%p\n", &matr2);
    matrix_resize(&matr2, 4, 4);
    matrix_print(matr2);
    printf("%p\n", &matr2);
    matrix matr3 = matrix_mult_scalar(matr2, 4);
    matrix_print(matr3);
    printf("%p\n", &matr3);
    exit(EXIT_SUCCESS);
}
