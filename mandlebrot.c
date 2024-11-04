#include <stdio.h>
#include <stdlib.h>
#include <complex>
#include <omp.h>

using namespace std ;
// global varibles 

// define the interval for the complex plane region 
const double REAL_MIN = -2.5;
const double REAL_MAX = 1.0;
const double IMAG_MIN = -1.0;
const double IMAG_MAX = 1.0;


// define the max iteration for check the mandlebrot set 
const int MAXITERATION = 3000;

// function to check if a point is in the Mandelbrot set
bool isInMandelbrotSet(double real, double imag) {
    complex<double> c(real, imag);
    complex<double> z = 0;
    
    // iterate to check if the point diverges
    for (int i = 0; i < MAXITERATION; ++i) {
        z = z * z + c;
        
        // if the magnitude of z exceeds 2, it escapes the set
        if (abs(z) > 2.0) return false;
    }
    
    // if max_iterations reached without escaping, it s not  in the set
    return true;
}

// function to estimate the area of the Mandelbrot set
//  using Monte Carlo method
double calculateMandelbrotArea(int numIteration) {
    int inSetCount = 0;
    double real, imag;

    // Parallelize the loop
    #pragma omp parallel for reduction(+:inSetCount) private(real, imag) 
    for (int i = 0; i < numIteration; ++i) {
        
        // generate a random point within the specified complex plane region

        // Real part in range [REAL_MIN, REAL_MAX]
        real = (rand() / (double)RAND_MAX) * (REAL_MAX - REAL_MIN) + REAL_MIN;

        // Imagina part in range [IMAG_MIN, IMAG_MAX]
        imag = (rand() / (double)RAND_MAX) * (IMAG_MAX - IMAG_MIN) + IMAG_MIN;  

        // check if the point is within the mandelbrot set
        if (isInMandelbrotSet(real, imag)) {
            inSetCount++;  
        }
    }

    // calculate the estimated area based on the fraction of points in the set

    double area = ((REAL_MAX - REAL_MIN) * (IMAG_MAX - IMAG_MIN)) * (inSetCount / (double)numIteration);
    
    return area;
}

int main(int argc, char *argv[]) {
    // 
    double startTime, endTime ;
    
    // number of iteration  for Monte Carlo method
    int numIteration = 1000000;     
    // default number of threads
    int numThreads = 4;            

    // check if the number of threads is provided as a command line argument
    if (argc > 1) {
        // Convert argument to integer
        numThreads = atoi(argv[1]);  
    }

    // set the number of threads for OpenMP
    omp_set_num_threads(numThreads);

    // execution
    
    // Start timer
    startTime = omp_get_wtime();                   
    // Calculate area
    double area_par = calculateMandelbrotArea(numIteration);   
    // End timer
    endTime = omp_get_wtime();                
    
    printf("[+] Mandelbrot area: %.10f\n", area_par);
    printf("[+] time: %.4f seconds with %d threads\n", endTime - startTime, numThreads);

    return 0;
}
