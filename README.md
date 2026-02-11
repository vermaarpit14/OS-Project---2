# Matrix Multiplication Benchmark (Sequential vs Parallel)

This project benchmarks sequential and process-based parallel matrix
multiplication in C using `fork()` and `wait()` on Linux systems.\
A Bash automation script is included to compile the program, execute
benchmarks, and store results in a log file.

------------------------------------------------------------------------

## Project Structure

-   `matrix_ops.c` --- C source implementing sequential and parallel
    matrix multiplication.
-   `benchmark.sh` --- Shell script to build, run, and log benchmarks.
-   `benchmark_log.txt` --- File where benchmark results are appended.

------------------------------------------------------------------------

## System Requirements

-   Linux or WSL environment\
-   GCC compiler\
-   Bash shell

To install required tools:

``` bash
sudo apt install build-essential
```

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

1.  Compiles `matrix_ops.c` into `matrix_benchmark`
2.  Executes the benchmark with matrix size `2000` and `4` worker
    processes
3.  Appends output to `benchmark_log.txt`
4.  Removes the compiled binary after completion

------------------------------------------------------------------------

### Manual Compilation and Execution

Compile the program:

``` bash
gcc -O2 ai_fast_calculation.c -o matrix_benchmark
```

Run with arguments:

``` bash
./matrix_benchmark <matrix_size> <workers>
```

Example:

``` bash
./matrix_benchmark 2000 4
```

------------------------------------------------------------------------

## Performance Metrics

-   **Sequential Time** --- Execution using a single process.
-   **Parallel Time** --- Computation divided row-wise among multiple
    processes using `fork()`.

Each worker computes a contiguous block of matrix rows while the parent
process waits for all children to complete.

------------------------------------------------------------------------

## Sample Output

    Initializing Matrix: 2000x2000 | Workers: 4
    Running Sequential Mode...
    >> Sequential Time: 21.76 seconds
    Running Parallel Mode...
    >> Parallel Time: 6.14 seconds

------------------------------------------------------------------------

## Authors

PALURI VEERA DURGA VARA PRASAD --- 24CS8031

GOGULAMUDI PREM SANTHOSH --- 24CS8032

PRADIP GORAI --- 24CS8033

GUNTREDDI NEELAPRASANTH --- 24CS8034

DARLA POOJITHA --- 24CS8035

ANJALI SINGH --- 24CS8036

ANIKET HALDAR --- 24CS8037

ARPIT VERMA --- 24CS8038

HIMANSHU GUPTA --- 24CS8039

RAJ GURU --- 24CS8040

------------------------------------------------------------------------

