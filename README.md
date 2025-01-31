# Parallel and Distributed Processing (PADP) Lab (21CS72)

---

### Overview

This repository contains lab programs for the Parallel and Distributed Processing (PADP) course. Each program demonstrates core parallel programming concepts using OpenMP or MPI.

### Table of Contents

| Program                               | Description                                         | Link to Explanation                                                            |
| ------------------------------------- | --------------------------------------------------- | ------------------------------------------------------------------------------ |
| Matrix Multiplication (OpenMP)        | Parallel matrix multiplication using OpenMP         | [Explanation](./Lab_programs/Matrix_mul/Explaination.md)                       |
| Sieve of Eratosthenes (OpenMP)        | Finding prime numbers using different approaches    | [Explanation](./Lab_programs/Sieve_code/Explaination.md)                       |
| Monte Carlo Method for PI Calculation | Parallel random sampling for PI approximation       | [Explanation](./Lab_programs/PI_Calculation_using_Monto-Carlo/Explaination.md) |
| MPI Message Passing                   | Demonstrates MPI-based inter-process communication  | [Explanation](./Lab_programs/MPI_message/Explaination.md)                      |
| Image Processing (OpenMP)             | RGB to modified grayscale conversion in parallel    | [Explanation](./Lab_programs/Image_omp/Explaination.md)                        |
| Word Search (OpenMP)                  | Parallel word search in a mixture of sentences      | [Explanation](./Lab_programs/Wordsearch/Explaination.md)                       |
| Dynamic Memory Allocation (OpenMP)    | Parallel matrix multiplication using dynamic memory | [Explanation](./Lab_programs/DynamicMemAlloc_MatMul/Explaination.md)           |

### Prerequisites

- GCC or Clang compiler with OpenMP support
- MPI compiler (e.g., mpicc) for MPI programs
- GD library (libgd) if running the Image Processing example

### Compilation & Execution

Below is a quick reference for running each program:

1. **Matrix Multiplication (OpenMP)**

```bash
gcc -fopenmp matrix_mul.c -o matrix_mul
./matrix_mul
```

2. **Sieve of Eratosthenes (OpenMP)**

```bash
gcc -fopenmp sieve_euro.c -o sieve -lm
./sieve
```

3. **Monte Carlo Method for PI Calculation**

```bash
gcc pi_monte_carlo.c -o pi_monte_carlo
./pi_monte_carlo 1000000
```

4. **MPI Message Passing**

```bash
mpicc mpi_message.c -o mpi_message
mpirun -np 4 ./mpi_message
```

5. **Image Processing (OpenMP)**

```bash
gcc -fopenmp image_omp.c -o image_omp -lgd
./image_omp input.png output.png
```

### Usage Instructions

- For matrix multiplication, adjust row/column values directly in the code if needed.
- For sieve, specify input size (1M, 10M, 100M, etc.) within the code/CLI prompt.
- For Monte Carlo PI, pass the number of random points as a command line argument or enter interactively.
- For MPI message passing, ensure mpirun -np <num_procs> is used, with <num_procs> matching your setup.
- For image processing, provide input/output filenames and optionally tweak scheduling parameters.

### References

- [OpenMP Documentation](https://www.openmp.org/resources/)
- [MPI Official Site](https://www.mpi-forum.org/)

### Contributors

- [Krishnatejaswi S](https://github.com/KTS-o7)
