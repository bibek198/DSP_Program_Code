#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

// Recursive FFT function (Decimation in Time)
void FFT(float real[], float imag[], int N) {
    if (N <= 1) return;

    // Split even and odd parts
    float even_real[N/2], even_imag[N/2];
    float odd_real[N/2],  odd_imag[N/2];

    for (int i = 0; i < N/2; i++) {
        even_real[i] = real[2*i];
        even_imag[i] = imag[2*i];
        odd_real[i]  = real[2*i + 1];
        odd_imag[i]  = imag[2*i + 1];
    }

    // Recursive calls
    FFT(even_real, even_imag, N/2);
    FFT(odd_real, odd_imag, N/2);

    // Combine results
    for (int k = 0; k < N/2; k++) {
        float angle = -2 * PI * k / N;
        float w_real = cos(angle);
        float w_imag = sin(angle);

        float temp_real = w_real * odd_real[k] - w_imag * odd_imag[k];
        float temp_imag = w_real * odd_imag[k] + w_imag * odd_real[k];

        real[k]       = even_real[k] + temp_real;
        imag[k]       = even_imag[k] + temp_imag;
        real[k + N/2] = even_real[k] - temp_real;
        imag[k + N/2] = even_imag[k] - temp_imag;
    }
}

int main() {
    int N = 8; // Must be power of 2
    float real[] = {1, 2, 3, 4, 0, 0, 0, 0};
    float imag[8] = {0};
    float amp[8], phase[8];

    // Perform FFT
    FFT(real, imag, N);

    // Compute amplitude and phase
    for (int i = 0; i < N; i++) {
        amp[i] = sqrt(real[i]*real[i] + imag[i]*imag[i]);
        phase[i] = atan2(imag[i], real[i]); // in radians
    }

    // Display results
    printf("-----------------------------------------------------\n");
    printf(" k\tReal\t\tImag\t\tAmplitude\tPhase (rad)\n");
    printf("-----------------------------------------------------\n");

    for (int i = 0; i < N; i++) {
        printf(" %d\t%.4f\t%.4f\t%.4f\t\t%.4f\n", i, real[i], imag[i], amp[i], phase[i]);
    }

    printf("-----------------------------------------------------\n");
    return 0;
}
