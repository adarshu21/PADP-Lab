# Matrix Multiplication Using OpenACC

## Program Overview

This program implements matrix multiplication using OpenACC for parallel processing. It multiplies two 100x100 matrices and verifies the results by comparing with a sequential implementation.

## Key Components

1. **Data Structures**

   - Four 100x100 matrices:
     - A: First input matrix
     - B: Second input matrix
     - C: Result matrix (OpenACC)
     - D: Result matrix (Sequential verification)

2. **Core Directives**
   ```c
   #pragma acc data copyin(A, B) copy(C)
   #pragma acc kernels
   #pragma acc loop tile(32, 32)
   #pragma acc loop reduction(+ : temp)
   ```

## Code Explanation

1. **Matrix Initialization**

   - Matrices A and B are initialized with values based on indices
   - C and D are initialized to zero

2. **OpenACC Implementation**

   - Uses data directives for memory management
   - Implements loop tiling (32x32) for optimization
   - Employs reduction for parallel sum computation

3. **Verification Process**
   - Sequential matrix multiplication stored in matrix D
   - Results compared between C and D matrices
   - Reports any mismatches found

## What does each core directive do?

1. `#pragma acc data copyin(A, B) copy(C)`: Copies data to the device and back. This copies the input matrices A and B to the device and the result matrix C back to the host. Here it is assumed that the device is a GPU.

2. `#pragma acc kernels`: Indicates that the following block should be parallelized.

3. `#pragma acc loop tile(32, 32)`: Divides the loop into tiles of size 32x32. This is done to optimize memory access patterns and cache utilization.

4. `#pragma acc loop reduction(+ : temp)`: Performs a reduction operation on the variable `temp`. This is used to compute the sum of products in the matrix multiplication.

## Performance Results

```
Time: 0.003040 seconds taken by OpenACC
Matrix multiplication successful
```

## Compilation Instructions

```bash
gcc -fopenacc -o dma_mat_mul dma_mat_mul.c
```

```bash
# For NVIDIA GPUs
nvc -acc -Minfo=accel -o dma_mat_mul dma_mat_mul.c
```

## Execution

```bash
./dma_mat_mul
```
