#include <stdio.h>
#include <math.h>

#define PI 3.14159265
#define N 8  // number of samples (you can change it)

int main() {
    double x[N] = {1, 2, 3, 4, 2, 1, 0, 0}; // example input sequence
    double real[N], imag[N];
    double amplitude[N], phase[N];

    // Initialize all arrays to 0
    for (int k = 0; k < N; k++) {
        real[k] = 0;
        imag[k] = 0;
    }

    // DFT computation
    for (int k = 0; k < N; k++) { // for each output frequency bin
        for (int n = 0; n < N; n++) { // for each input sample
            double angle = 2 * PI * k * n / N;
            real[k] += x[n] * cos(angle);
            imag[k] -= x[n] * sin(angle);
        }
    }

    // Compute amplitude and phase
    for (int k = 0; k < N; k++) {
        amplitude[k] = sqrt(real[k] * real[k] + imag[k] * imag[k]);
        phase[k] = atan2(imag[k], real[k]); // returns value in radians
    }

    // Display results
    printf("k\tReal\t\tImag\t\tAmplitude\tPhase (rad)\n");
    printf("--------------------------------------------------------------\n");
    for (int k = 0; k < N; k++) {
        printf("%d\t%.4f\t\t%.4f\t\t%.4f\t\t%.4f\n",
               k, real[k], imag[k], amplitude[k], phase[k]);
    }

    return 0;
}
