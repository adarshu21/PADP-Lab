# Matrix Multiplication using OpenMP

## Logic Explanation

The program implements parallel matrix multiplication using OpenMP. Here's a detailed breakdown:

1. Matrix Structure

   - Two input matrices of size 2000x2000
   - Dynamic memory allocation using malloc
   - Result matrix to store multiplication output

2. Multiplication Process:
   - For each element result[i][j]:
   - Calculate sum of matrix1[i][k] \* matrix2[k][j]
   - Where k varies from 0 to cols

## Code Explanation

The program leverages OpenMP for parallel processing. Here's a detailed breakdown:

### Key Components

1. **Memory Allocation**

   ```c
   int **matrix1 = (int **)malloc(rows * sizeof(int *));
   ```

   - Dynamically allocates memory for matrices
   - Uses double pointers for 2D array representation

2. **Matrix Initialization**

   - Sequential counter fills matrices with values
   - Ensures matrices have valid multiplication dimensions

3. **Parallel Implementation**
   ```c
   #pragma omp parallel for private(i, j, k, sum)
   ```
   - Distributes outer loop iterations among threads
   - Private variables prevent data race conditions

### OpenMP Directives

1. **Thread Management**

   ```c
   omp_set_num_threads(num_threads[t])
   ```

   - Tests with 1, 2, 4, and 8 threads
   - Measures execution time for each configuration

2. **Work Distribution**
   ```c
   #pragma omp parallel for
   ```
   - Parallelizes the outermost loop
   - Each thread processes different rows

### Performance Analysis

- Measures execution time using `omp_get_wtime()`
- Tests different thread configurations
- Demonstrates parallel speedup potential

## Compilation Instructions

```bash
gcc -fopenmp Matrix_mul.c -o mat_mul
```

## Example Output

```bash
./mat_mul
Time taken for 1 threads: 39.575116
Time taken for 2 threads: 18.263602
Time taken for 4 threads: 9.561242
Time taken for 8 threads: 6.606753
```
