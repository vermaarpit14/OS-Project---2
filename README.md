# OS Project 2(b) fast_solve - Determinant & Cramer's Rule Benchmark

This project benchmarks sequential and process-based parallel
computation of matrix determinants and solving systems of linear
equations using **Cramer's Rule** in C.\
The implementation utilizes `fork()` for parallelism and compares
performance against a sequential approach on Linux systems.

A Bash automation script is included to compile the program, execute
benchmarks, and store results in a log file.

------------------------------------------------------------------------

## Project Structure

-   `fast_solve.c` --- C source implementing sequential and parallel
    determinant computation and Cramer's Rule solver.
-   `benchmark.sh` --- Shell script to build, run, and log benchmarks.
-   `benchmark_log.txt` --- File where benchmark results are appended.

------------------------------------------------------------------------

## System Requirements

-   Linux or WSL environment
-   GCC compiler
-   Bash shell

To install required tools:

``` bash
sudo apt install build-essential
```

------------------------------------------------------------------------

## Problem Description

Write a program that:

1.  Computes the **determinant of a matrix**.
2.  Solves a system of linear equations using **Cramer's Rule**.
3.  Works efficiently for large systems where the number of equations
    **n \> 1000**.
4.  Demonstrates performance improvement using multiple processes.

------------------------------------------------------------------------

## Prerequisites Used

-   `srand()` and `random()` --- to generate matrix coefficients.
-   `malloc()` and `free()` --- for dynamic allocation of 1D and 2D
    arrays.
-   `fork()` --- to create multiple child processes for parallel
    computation.

### Implementation Notes

-   Dynamic memory allocation is used to create matrices of size **n ×
    n** and vectors of size **n**.
-   Matrix values are populated using pseudo-random numbers.
-   Determinant calculations are distributed across multiple child
    processes.
-   Each child process computes part of the workload while the parent
    waits using process synchronization.
-   Performance speedup is measured by comparing sequential and parallel
    execution times.

------------------------------------------------------------------------

## How to Run

### Automated Benchmarking

Make the script executable:

``` bash
chmod +x benchmark.sh
```

Run:

``` bash
./benchmark.sh
```

This performs the following steps:

1.  Compiles `fast_solve.c` into `fast_solve_benchmark`
2.  Executes the benchmark with matrix size `1000+` and multiple worker
    processes
3.  Appends output to `benchmark_log.txt`
4.  Removes the compiled binary after completion

------------------------------------------------------------------------

### Manual Compilation and Execution

Compile the program:

``` bash
gcc -O2 fast_solve.c -o fast_solve_benchmark
```

Run with arguments:

``` bash
./fast_solve_benchmark <matrix_size> <workers>
```

Example:

``` bash
./fast_solve_benchmark 1200 4
```

------------------------------------------------------------------------

## Performance Metrics

-   **Sequential Time** --- Determinant and equation solving using a
    single process.
-   **Parallel Time** --- Computation divided among multiple processes
    using `fork()`.
-   **Speedup Achieved** --- Comparison between sequential and parallel
    execution.

Each worker process computes a portion of determinant-related
calculations while the parent process waits for all children to
complete.

------------------------------------------------------------------------

## Sample Output

    Initializing Matrix: 1200x1200 | Workers: 4
    Running Sequential Mode...
    >> Sequential Time: 35.42 seconds

    Running Parallel Mode...
    >> Parallel Time: 9.87 seconds

    >> Speedup Achieved: 3.58x

------------------------------------------------------------------------

## Authors

PALURI VEERA DURGA VARA PRASAD --- 24CS8031\
GOGULAMUDI PREM SANTHOSH --- 24CS8032\
PRADIP GORAI --- 24CS8033\
GUNTREDDI NEELAPRASANTH --- 24CS8034\
DARLA POOJITHA --- 24CS8035\
ANJALI SINGH --- 24CS8036\
ANIKET HALDAR --- 24CS8037\
ARPIT VERMA --- 24CS8038\
HIMANSHU GUPTA --- 24CS8039\
RAJ GURU --- 24CS8040

------------------------------------------------------------------------
