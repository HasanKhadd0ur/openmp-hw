#include <stdio.h>
#include <math.h>
#include <omp.h>

// Define the function f(x) = ln(x) / x
double lnFunction(double x) {
    return log(x) / x; 
}

double calculate_integral(int num_rectangles, double start, double end) {
    double width = (end - start) / num_rectangles;
    double total_area = 0.0;

    #pragma omp parallel for reduction(+:total_area)
    for (int i = 0; i < num_rectangles; i++) {
        // Midpoint for rectangle
        double x = start + (i + 0.5) * width;  
        double area = lnFunction(x) * width;
        total_area += area;
    }

    return total_area;
}

int main(int argc, char *argv[]) {
    // Adjust for higher precision
    int num_rectangles = 1000000;  

    // integration interval
    double start = 1.0, end = 10.0;

    // Start time for performance measurement
    double start_time = omp_get_wtime(); 
    double total_area = calculate_integral(num_rectangles, start, end);
    
    // End time for performance measurement
    double end_time = omp_get_wtime(); 

    printf("Calculated integral: %.10f\n", total_area);
    printf("Execution time: %.4f seconds\n", end_time - start_time);

    return 0;
}
