// We need to write an OpenMP program to multiply two matrices.
// We need to use dynamic memory allocation for the matrices.

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int rows = 2000, cols = 2000;
    int i, j, k, count = 0, sum = 0;
    // Dynamically allocate memory for the matrices
    int **matrix1 = (int **)malloc(rows * sizeof(int *));
    int **matrix2 = (int **)malloc(rows * sizeof(int *));
    int **result = (int **)malloc(rows * sizeof(int *));

    for (i = 0; i < rows; i++)
    {
        matrix1[i] = (int *)malloc(cols * sizeof(int));
        matrix2[i] = (int *)malloc(cols * sizeof(int));
        result[i] = (int *)malloc(cols * sizeof(int));
    }

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            matrix1[i][j] = count++;
            matrix2[i][j] = count++;
        }
    }

    int num_threads[4] = {1, 2, 4, 8};
    for (int t = 0; t < 4; t++)
    {
        double start_time = omp_get_wtime();
        omp_set_num_threads(num_threads[t]);
#pragma omp parallel for private(i, j, k, sum)
        for (i = 0; i < rows; i++)
        {
            for (j = 0; j < cols; j++)
            {
                sum = 0;
                for (k = 0; k < cols; k++)
                {
                    sum += matrix1[i][k] * matrix2[k][j];
                }
                result[i][j] = sum;
            }
        }

        double end_time = omp_get_wtime();
        printf("Time taken for %d threads: %lf\n", num_threads[t], end_time - start_time);
    }

    return 0;
}