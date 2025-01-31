# Parallel Word Search Implementation using OpenMP

## Program Overview

This program implements a parallel word search algorithm using OpenMP to count the frequency of specific words in a text file. The program is optimized for performance by utilizing multiple threads.

## Key Components

1. **Data Structures**

   - Array of search words (20 words)
   - Array to store word counts
   - Thread count configurations: 1, 2, 4, and 8 threads

2. **Core Functions**

   - `is_alpha`: Checks if a character is alphabetic
   - `is_equal`: Case-insensitive string comparison
   - `read_word`: Reads a word from file, handling non-alphabetic characters
   - `determine_count`: Counts occurrences of a specific word in the file

3. **Parallel Implementation**
   ```c
   #pragma omp parallel for
   for (int i = 0; i < COUNT; i++)
   {
        counts[i] = determine_count(FILE_NAME, search_words[i], 1);
   }
   ```

## Code Explanation

1. **String Processing Functions**

   - `is_alpha`: Validates alphabetic characters
   - `is_equal`: Implements case-insensitive comparison
   - String manipulations use standard C string functions

2. **File Processing**

   - `read_word`:
     - Skips non-alphabetic characters
     - Reads words character by character
     - Handles EOF conditions

3. **Word Counting**

   - `determine_count`:
     - Opens file for each word search
     - Counts word occurrences
     - Case-insensitive matching

4. **Main Program Flow**
   - Initializes arrays and variables
   - Tests different thread configurations
   - Measures execution time using `omp_get_wtime()`
   - Displays timing analysis and word counts

## Performance Analysis

### Timing Results

```
Thread Count |  Time (sec)
-------------+------------
        1      |   3.865801
        2      |   3.838966
        4      |   2.586286
        8      |   2.062383
```

### Observations

- Significant speedup with increased thread count
- Best performance with 8 threads
- ~47% reduction in execution time from 1 to 8 threads

## Word Frequency Results

The program found consistent counts for most words:

- Common words (apple, banana): 564,480 occurrences
- Other words: 544,320 occurrences
- Exception: "elderberryfig" (0 occurrences - likely due to concatenation)

## Compilation Instructions

```bash
gcc -fopenmp wordsearch.c -o wordsearch
```

## Program Execution

```bash
./wordsearch
```
