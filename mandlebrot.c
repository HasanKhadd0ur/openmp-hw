#include "iostream"
#include <complex>
#include <omp.h>
#include <cstdlib>

bool isInMandelbrotSet(double real, double imag, int max_iterations) {
    std::complex<double> c(real, imag);
    std::complex<double> z = 0;
    for (int i = 0; i < max_iterations; ++i) {
        z = z * z + c;
        if (std::abs(z) > 2.0) return false;
    }
    return true;
}

double calculateMandelbrotArea(int num_points, int max_iterations, bool parallel) {
    int in_set_count = 0;
    double real, imag;

    #pragma omp parallel for reduction(+:in_set_count) private(real, imag) if (parallel)
    for (int i = 0; i < num_points; ++i) {
        real = (rand() / (double)RAND_MAX) * 3.5 - 2.5;  // Real part in range [-2.5, 1]
        imag = (rand() / (double)RAND_MAX) * 2.0 - 1.0;  // Imaginary part in range [-1, 1]
        if (isInMandelbrotSet(real, imag, max_iterations)) {
            in_set_count++;
        }
    }

    double area = (3.5 * 2.0) * (in_set_count / (double)num_points);
    return area;
}

int main() {
    int num_points = 1000000;         // Number of random points for Monte Carlo
    int max_iterations = 5000;        // Maximum iterations for Mandelbrot check

    // Sequential run
    double start_time = omp_get_wtime();
    double area_seq = calculateMandelbrotArea(num_points, max_iterations, false);
    double end_time = omp_get_wtime();
    std::cout << "Sequential Mandelbrot area: " << area_seq << std::endl;
    std::cout << "Sequential time: " << end_time - start_time << " seconds\n";

    // Parallel run
    start_time = omp_get_wtime();
    double area_par = calculateMandelbrotArea(num_points, max_iterations, true);
    end_time = omp_get_wtime();
    std::cout << "Parallel Mandelbrot area: " << area_par << std::endl;
    std::cout << "Parallel time: " << end_time - start_time << " seconds\n";

    return 0;
}
