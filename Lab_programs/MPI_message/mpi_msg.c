// This is a simple MPI prohgram that has total of 4 processes.
// The master process sends a task to each of the other processes to calculate PI * i, where i is the rank of the process.
// Each process receives the task, calculates the result and sends it back to the master process.
// The master process receives the results from all the other processes and prints them.

#include <stdio.h>
#include <mpi.h>
#include <string.h>

#define BUFFER_SIZE 100

int main(int argc, char *argv[])
{
    // Here rank and size are used to get the rank of the process and the total number of processes.
    // rank and size are obtained using MPI_Comm_rank and MPI_Comm_size functions.
    // MPI_Comm_rank(MPI_COMM_WORLD, &rank) returns the rank of the calling process in the communicator MPI_COMM_WORLD.
    // MPI_Comm_size(MPI_COMM_WORLD, &size) returns the total number of processes in the communicator MPI_COMM_WORLD.
    int rank, size;
    char buffer[BUFFER_SIZE];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Simulating some computation
    double computation_result = rank * 3.14159;

    if (rank == 0)
    {
        printf("Master process 0 starting coordination...\n");
        for (int i = 1; i < size; i++)
        {
            sprintf(buffer, "Task assignment for process %d: Calculate PI * %d", i, i);
            MPI_Send(buffer, BUFFER_SIZE, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Recv(buffer, BUFFER_SIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        printf("Process %d received task: %s\n", rank, buffer);
        sprintf(buffer, "Process %d completed calculation: Result = %.4f", rank, computation_result);
        MPI_Send(buffer, BUFFER_SIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    if (rank == 0)
    {
        for (int i = 1; i < size; i++)
        {
            MPI_Recv(buffer, BUFFER_SIZE, MPI_CHAR, i, 0, MPI_COMM_WORLD, &status);
            printf("Master process 0 received: %s\n", buffer);
        }
    }

    MPI_Finalize();
    return 0;
}
