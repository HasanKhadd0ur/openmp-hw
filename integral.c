#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

// Define the function f(x) = ln(x) / x
double lnFunction(double x) {
    return log(x) / x; 
}

// this is the first approach 
double calculateIntegral(int numRectangles, int start, int end) {
    
    // the width of  aa single rectangle
    double width = (end - start ) /( numRectangles * 1.0 );
    
    // total area
    double totalArea = 0.0;

    #pragma omp parallel for reduction(+:totalArea)
    for (int i = 0; i < numRectangles; i++) {

        // Midpoint for rectangle
        double xMid = start + (i + 0.5) * width;  
        // calcute F (x)
        double area = lnFunction(xMid) * width;

        totalArea += area;
    }

    return totalArea;
}
// anpother appraoch to calc the itegral using openmp 
// by using an atomic operation for the (+=)
double calculateIntegralSecondApproach(int numRectangles, int start, int end) {
    double width = (end - start) / (numRectangles * 1.0);
    double totalArea = 0.0;

    // Calculate the area using the in parallel
    #pragma omp parallel
    {
        double localSum = 0.0;

        #pragma omp for
        for (int i = 0; i < numRectangles; i++) {
            // Midpoint for rectangle
            double xMid = start + (i + 0.5) * width;  
            // calcute F (x)
            double area = lnFunction(xMid) * width;
            localSum += area;
        }

        // Reduce local sums into total area
        #pragma omp atomic
        totalArea += localSum;
    }

    return totalArea;
}


int main(int argc, char *argv[]) {

    // * note => ( 
    //          the two parameter nume of threads and num of rectangle 
    //          we read them from the argument of the program    
    // )

    // Adjust for higher precision
    int numRectangles = 1000000;  
    // number of threads 
    int numThreads = 2;

    // integration interval
    int  start = 1, end = 10;
    
    // read the number of threads and rectangles from argument if it passed  
    if (argc < 3) {
        printf("+ Usage: %s <num_threads> <num_rectangles>\n", argv[0]);
        printf("+ Using default values: %d threads, %d rectangles.\n", numThreads, numRectangles);
      
    } else {
        // Convert command line argument to integer for threads
        numThreads = atoi(argv[1]); 
        // Convert command line argument to integer for rectangles
        numRectangles = atoi(argv[2]);
    }
    
    // Set the number o threads
    omp_set_num_threads(numThreads);

    // start the timer 
    double startTime = omp_get_wtime();
    double result = calculateIntegral(numRectangles, start, end);
    // stop the timer 
    double endTime = omp_get_wtime();

    // Print results in a good way
    printf("\n+----------------------------------------+\n");
    printf("+\tResult\t\t\n");
    printf("+------------------------------------------+\n");
    printf("[+] Calculated integral:    %.10f\n", result);
    printf("[+] Execution time:         %.4f seconds\n", endTime - startTime);
    printf("[+] Number of threads:      %d\n", numThreads);
    printf("[+] Number of rectangles:   %d\n", numRectangles);
    printf("+------------------------------------------+\n");

 // this is an old code for the main 
/*
    int ad ;

    int numThreads;    //number of threads

    printf("Enter the number of threads: ");
    ad =scanf("%d", &numThreads);

    // Set the number of threads for OpenMP
    omp_set_num_threads(numThreads);

    // Start timing the execution
    double startTime = omp_get_wtime();
    
    // Calculate the integral
    double result = calculateIntegral(numRectangles , start , end );

    // End timing the execution
    double endTime = omp_get_wtime();

    // Output the results
    printf("Calculated integral: %.10f\n", result);
    printf("Execution time: %.4f seconds with %d threads\n", endTime - startTime, numThreads);
 */

    return 0;
}
