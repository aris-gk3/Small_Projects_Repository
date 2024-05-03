# Parallel Processing with OpenMP

Simple code to showcase use of OpenMP to run code on multiple threads.

**Instructions**

hello_opm.c

```
g++ hello_opm.c -o hello_opm -fopenmp
./hello_opm <number_of_threads>
```

Algorithms implemented are:
1. Quick Sort
2. Odd-Even Transposition Sort
3. Merge Sort (with Arrays or Double Linked Lists)

| Algorithm   | 1 thread | 2 threads | length |
| ----------- | ----------- |--- | --- |
| QuickSort    | 917 ms       | 489 ms | 524288|
| Odd-Even Transposition Sort    | 605 ms       | 304 ms| 16384|
| MergeSort with Linked Lists   | 21.5 ms        | 13.6 ms | 65536|
| MergeSort with Arrays   | 82.7 ms | 42.7 ms| 524288 |
| Nested (Parallelism) MergeSort with Arrays   | 89.4 ms        | 46.8 ms| 524288|

<u> Comment </u>: Values depend on the state of the computer.