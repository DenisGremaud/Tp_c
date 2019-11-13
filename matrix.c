/*
Auteur : Denis Gremaud
Version : 1.0
Date : 06.11.2019
Description : tp_03
*/
#include <stdio.h>  // used for printf/scanf
#include <stdint.h>  // used for printf/scanf
#include <stdbool.h>  // used for printf/scanf
#include <stdlib.h> // used for EXIT_SUCCESS
#include <time.h> // used for time(NULL)
#include <math.h>
#include "matrix.h"

matrix matrix_create(int m, int n){
    matrix mat;
    mat.data = (double **)malloc(m * sizeof(double*));
    double* temp = (double *)malloc(n * m * sizeof(double));

    for (int i = 0; i < m; i++)
    {
        mat.data[i] = &temp[i * n];
    }

    mat.m = m;
    mat.n = n;
    return mat;
}

void matrix_destroy(matrix *mat){
    free(mat->data[0]);
    free(mat->data);
    mat->data = NULL;
    mat->m = -1;
    mat->n = -1;
}

matrix matrix_create_from_array(int m, int n, double data[]){
    matrix mat = matrix_create(m, n);
    mat.m = m;
    mat.n = n;

    for (int i = 0; i < m; i++)
    {
        for (int y = 0; y < n; y++)
        {
            mat.data[i][y] = data[i * y];
        }
    }
    return mat;
}

matrix matrix_clone(matrix mat){
  matrix newmat = matrix_create(mat.m,mat.n);
  memcpy(*(newmat.data), *(mat.data), mat.m * mat.n * sizeof(newmat.data));
  return newmat;
}

void matrix_print(matrix mat){
    printf("Taille du tableau : %d, %d \n", mat.m, mat.n);
    for (int i = 0; i < mat.m; i++)
    {
        for (int y = 0; y < mat.n; y++)
        {
            if (y == 0)
            {
                printf("\n");
            }
            printf("%.2f, ", mat.data[i][y]);
        }
    }
    printf("\n");
}

int matrix_resize(matrix *mat, int m, int n){
    double donnee[m * n];

    if (m < 1 && n < 1)
    {
        return 0;
    }

    for (int i = 0; i < m; i++)
    {
        for (int y = 0; y < n; y++)
        {
            donnee[i * y] = 0.00; 
        }
    }
    

    for (int i = 0; i < mat->m; i++)
    {
        for (int y = 0; y < mat->n; y++)
        {
            donnee[i * y] = mat->data[i][y];
        }
    }
    
    mat->m = m;
    mat->n = n;

    *mat = matrix_create_from_array(m, n, donnee);
    
    return 1;
}

bool matrix_is_approx_equal(matrix mat1, matrix mat2, double epsilon){
    if(mat1.m == mat2.m && mat1.n == mat2.n){
        for (int i = 0; i < mat1.m; i++)
        {
            for (int y = 0; y < mat1.n; y++)
            {
                if(fabs(mat1.data[i][y] - mat2.data[i][y]) > epsilon)
                {
                    return 0;
                }
            }
        }
        return 1;
    }
    else{
        return 0;
    }
}

bool matrix_is_equal(matrix mat1, matrix mat2){
   if(mat1.m == mat2.m && mat1.n == mat2.n){
        for (int i = 0; i < mat1.m; i++)
        {
            for (int y = 0; y < mat1.n; y++)
            {
                if(fabs(mat1.data[i][y] - mat2.data[i][y]) == 0)
                {
                    return 0;
                }
            }
        }
        return 1;
    }
    else{
        return 0;
    }
}

int matrix_add_in_place(matrix mat1, matrix mat2){
    if(mat1.m == mat2.m && mat1.n == mat2.n){
        mat1 = matrix_add(mat1, mat2);
        return 1;
    }
    else{
        return 0;
    }
}

int matrix_sub_in_place(matrix mat1, matrix mat2){
    if(mat1.m == mat2.m && mat1.n == mat2.n){
        mat1 = matrix_sub(mat1, mat2);
        return 1;
    }
    else{
        return 0;
    }
}

int matrix_mult_in_place(matrix *mat1, matrix mat2){
    int res = 1;
    matrix tmp_mat;

    if(mat1->n == mat2.m && mat1->m == mat2.n){

        tmp_mat = matrix_create(mat1->m, mat2.n);
        for (int k = 0; k < tmp_mat.n; k++)
        {
            for (int i = 0; i < tmp_mat.n; i++)
            {
                for (int j = 0; j < mat1->n; j++)
                {
                    tmp_mat.data[k][i] += mat1->data[k][i] * mat2.data[j][i];
                }
            }
        }
        matrix_resize(mat1, tmp_mat.m, tmp_mat.n);
        for (int i = 0; i < tmp_mat.m; i++)
        {
            for (int j = 0; j < tmp_mat.n; j++)
            {
                mat1->data[i][j] = tmp_mat.data[i][j];
            }
        }
        matrix_destroy(&tmp_mat);
    }
    else{
        res = 0;
    }
    return res;
}

int matrix_add_scalar_in_place(matrix mat1, double n){
    mat1 = matrix_add_scalar(mat1, n);
    return 1;
}

int matrix_mult_scalar_in_place(matrix mat1, double n){
    mat1 = matrix_mult_scalar(mat1, n);
    return 1;
}

int matrix_transpose_in_place(matrix *mat){
    return 1;
}

int matrix_normalize_in_place(matrix mat){
    return 1;
}

matrix matrix_add(matrix mat1, matrix mat2){
    matrix mat;
    mat = matrix_create(mat1.m, mat1.n);
    for (int i = 0; i < mat1.m; i++)
    {
        for (int y = 0; y < mat1.n; y++)
        {
            mat.data[i][y] = mat1.data[i][y] + mat2.data[i][y];
        }
    }
    return mat;
}

matrix matrix_sub(matrix mat1, matrix mat2){
    matrix mat;
    mat = matrix_create(mat1.m, mat1.n);
    for (int i = 0; i < mat1.m; i++)
    {
        for (int y = 0; y < mat1.n; y++)
        {
            mat.data[i][y] = mat1.data[i][y] - mat2.data[i][y];
        }
    }
    return mat;
}

matrix matrix_mult(matrix mat1, matrix mat2){
    matrix tmp_mat;

    tmp_mat = matrix_create(mat1.m, mat2.n);
    for (int k = 0; k < tmp_mat.n; k++)
    {
        for (int i = 0; i < tmp_mat.n; i++)
        {
            for (int j = 0; j < mat1.n; j++)
            {
                tmp_mat.data[k][i] += mat1.data[k][i] * mat2.data[j][i];
            }
        }
    }
    return tmp_mat;
}

matrix matrix_add_scalar(matrix mat, double n){
    matrix matNew;
    matNew = matrix_create(mat.m, mat.n);
    for (int i = 0; i < mat.m; i++)
    {
        for (int y = 0; y < mat.n; y++)
        {
            matNew.data[i][y] = mat.data[i][y] + n;
        }
    }
    return matNew; 
}

matrix matrix_mult_scalar(matrix mat, double n){
    matrix matNew;
    matNew = matrix_create(mat.m, mat.n);
    for (int i = 0; i < mat.m; i++)
    {
        for (int y = 0; y < mat.n; y++)
        {
            matNew.data[i][y] = mat.data[i][y] * n;
        }
    }
    return matNew;
}

matrix matrix_transpose(matrix mat){
    matrix newmat;
    return newmat;
}

matrix matrix_normalize(matrix mat){
    matrix newmat;
    return newmat;
}
