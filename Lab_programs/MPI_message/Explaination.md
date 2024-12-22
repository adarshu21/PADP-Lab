# MPI Message Passing Example

## Logic Explanation

The program demonstrates basic Message Passing Interface (MPI) communication patterns. Here's a detailed breakdown:

1. Process Structure

   - Master process (rank 0) coordinates tasks
   - Worker processes (ranks 1-3) perform calculations
   - Uses MPI_Send and MPI_Recv for communication

2. Computation Process:
   - Each worker calculates PI \* rank
   - Results are sent back to master process
   - Communication uses fixed buffer size

## Code Explanation

The program implements MPI for distributed processing. Here's a detailed breakdown:

### Key Components

1. **MPI Initialization**

   ```c
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   ```

   - Initializes MPI environment
   - Gets process rank and total size
   - Sets up communication world

2. **Communication Setup**

   ```c
   char buffer[BUFFER_SIZE];
   MPI_Status status;
   ```

   - Fixed-size buffer for messages
   - Status tracking for MPI operations

3. **Task Distribution**
   - Master process sends tasks
   - Workers receive and process tasks
   - Results sent back to master

### MPI Operations

1. **Message Sending**

   ```c
   MPI_Send(buffer, BUFFER_SIZE, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
   ```

   - Sends messages to specific processes
   - Uses tags for message identification
   - Specifies message size and type

2. **Message Receiving**
   ```c
   MPI_Recv(buffer, BUFFER_SIZE, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
   ```
   - Receives messages from processes
   - Matches send/receive pairs
   - Handles incoming data

### Process Flow

- Master Process (Rank 0):

  - Distributes tasks to workers
  - Collects computation results
  - Coordinates overall execution

- Worker Processes (Rank > 0):
  - Receive task assignments
  - Perform calculations
  - Send results back to master

## Compilation Instructions

```bash
mpicc mpi_msg.c -o mpi_msg
```

## Execution Instructions

```bash
mpirun -np 4 ./mpi_msg
```

## Example Output

```
Master process 0 starting coordination...
Process 2 received task: Task assignment for process 2: Calculate PI * 2
Process 3 received task: Task assignment for process 3: Calculate PI * 3
Process 1 received task: Task assignment for process 1: Calculate PI * 1
Master process 0 received: Process 1 completed calculation: Result = 3.1416
Master process 0 received: Process 2 completed calculation: Result = 6.2832
Master process 0 received: Process 3 completed calculation: Result = 9.4248
```
