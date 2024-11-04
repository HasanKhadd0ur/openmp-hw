# openMP-HW

This repository contains two parallel C/C++ programs developed using OpenMP for numerical integration and area approximation tasks.

---

## Overview
This homework includes two C/C++ programs that leverage OpenMP for parallel computation:
1. **Numerical Integration** of $ f(x) = \frac{\ln(x)}{x} $ over the interval $[1, 10]$.
2. **Mandelbrot Set Area Approximation** using the Monte Carlo method.

Both programs contain sequential and parallel implementations to analyze performance and efficiency using OpenMP, along with an automated build and run process via Make.

---
## Solution Structure 

``` 
OPENMP-HW
├── out
│   ├── integral
│   └── mandelbrot
├── profiles
│   ├── integral_profile.txt
│   └── mandelbrot_profile.txt
├── gmon.out
├── integral.c
├── Makefile
├── mandelbrot.c
└── README.md
```

## Question 1: Numerical Integration
**Objective**: Calculate the integral of \( \frac{\ln(x)}{x} \) over \([1, 10]\) using a numerical integration technique that partitions the area under the curve into rectangles with equal width. The sum of these rectangles provides an approximation of the integral.

- **Approach**: Implemented the Riemann sum (rectangle) method, dividing the interval into `num_rectangles` of equal width.
- **Parallelization**: Used OpenMP to distribute rectangle area calculations across multiple threads. 
- **Analysis**: Compared the execution time of the sequential vs. parallel versions to understand the impact of parallelization on performance.

### Question 2: Mandelbrot Set Area Approximation
**Objective**: Approximate the area of the Mandelbrot set using the Monte Carlo method. Points are randomly generated within a defined region in the complex plane, and those that remain bounded after iterative calculations are counted to estimate the area.

- **Approach**: Randomly generated points in the complex plane, checking if each point belongs to the Mandelbrot set by iterating a complex function up to a set number of iterations.
- **Parallelization**: OpenMP was used to parallelize the point-checking process across multiple threads.
- **Analysis**: Compared execution time of sequential vs. parallel implementations and analyzed factors affecting parallel efficiency.

---

## Files 
- **`integral.c`**: Program for parallel numerical integration.
- **`mandelbrot.cpp`**: Program for parallel area approximation of the Mandelbrot set using Monte Carlo.
- **`Makefile`**: Automates building, running, profiling and cleaning both programs.

---

## Compilation and Execution

### Prerequisites
- **GCC with OpenMP support**: Ensure `gcc` and `make` are installed.

### Steps
1. **Build**: To compile both programs, run:
   ```bash
   make all
   ```
2. **Run Numerical Integration Program**:
   ```bash
   make run Pr=integral n=<num_threads> r=<num_rectangles>

   ```
3. **Run Mandelbrot Area Program**:
   ```bash
   make run Pr=mandelbrot   n=<num_threads>
   ```
4. **Profiling the Program Executing**:
   ```bash
   make Profile Pr=<program_name> n=<num_threads> 
   ```

5. **Clean**: To remove compiled binaries, run:
   ```bash
   make clean
   ```

Each program outputs the calculated area and the execution time for both sequential and parallel versions, allowing comparison of their performance.

---

## Results Analysis

- **Integration Program**:
  - **Expected Output**:
  - **Performance**: 

- **Mandelbrot Area Program**:
  - **Expected Output**: 
  - **Performance**:

---

## Conclusion
This homework illustrates the effectiveness of OpenMP in parallelizing computational tasks.
Performance comparisons between sequential and parallel implementations reveal insights into how thread distribution and workload balance influence speed and efficiency.

---

