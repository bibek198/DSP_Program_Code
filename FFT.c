#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

//--------------------------------------------------
// Utility Functions
//--------------------------------------------------

// Swap function for bit reversal
void bit_reverse(float *real, float *imag, int N) {
    int i, j, k;
    for (i = 1, j = 0; i < N; i++) {
        for (k = N >> 1; (j ^= k) < k; k >>= 1);
        if (i < j) {
            float temp = real[i];
            real[i] = real[j];
            real[j] = temp;

            temp = imag[i];
            imag[i] = imag[j];
            imag[j] = temp;
        }
    }
}

//--------------------------------------------------
// DIT FFT (Decimation in Time) - Recursive Version
//--------------------------------------------------
void DIT_FFT(float real[], float imag[], int N) {
    if (N <= 1) return;

    // Split into even and odd parts
    float even_real[N/2], even_imag[N/2];
    float odd_real[N/2], odd_imag[N/2];

    for (int i = 0; i < N/2; i++) {
        even_real[i] = real[2*i];
        even_imag[i] = imag[2*i];
        odd_real[i]  = real[2*i + 1];
        odd_imag[i]  = imag[2*i + 1];
    }

    // Recursive calls
    DIT_FFT(even_real, even_imag, N/2);
    DIT_FFT(odd_real, odd_imag, N/2);

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

//--------------------------------------------------
// DIF FFT (Decimation in Frequency) - Iterative Version
//--------------------------------------------------
void DIF_FFT(float real[], float imag[], int N) {
    for (int step = N; step > 1; step >>= 1) { // Step sizes: N → N/2 → ...
        int half = step / 2;
        float theta = -2 * PI / step;

        for (int group = 0; group < N; group += step) {
            for (int k = 0; k < half; k++) {
                float w_real = cos(theta * k);
                float w_imag = sin(theta * k);

                int i = group + k;
                int j = i + half;

                float temp_real = real[i] - real[j];
                float temp_imag = imag[i] - imag[j];

                real[i] = real[i] + real[j];
                imag[i] = imag[i] + imag[j];

                real[j] = w_real * temp_real - w_imag * temp_imag;
                imag[j] = w_real * temp_imag + w_imag * temp_real;
            }
        }
    }

    // Bit-reverse at the end for DIF
    bit_reverse(real, imag, N);
}

//--------------------------------------------------
// Helper function to print FFT results
//--------------------------------------------------
void print_fft(float real[], float imag[], int N, char *title) {
    float amp[N], phase[N];
    printf("\n==================== %s ====================\n", title);
    printf(" k\tReal\t\tImag\t\tAmplitude\tPhase (rad)\n");
    printf("-----------------------------------------------------\n");
    for (int i = 0; i < N; i++) {
        amp[i] = sqrt(real[i]*real[i] + imag[i]*imag[i]);
        phase[i] = atan2(imag[i], real[i]);
        printf(" %d\t%.4f\t%.4f\t%.4f\t\t%.4f\n", i, real[i], imag[i], amp[i], phase[i]);
    }
    printf("-----------------------------------------------------\n");
}

//--------------------------------------------------
// Main
//--------------------------------------------------
int main() {
    int N = 8;

    // Input sequence
    float real1[8] = {1, 1, 2, 0, 1, 2, 0, 1};
    float imag1[8] = {0};
    float real2[8] = {1, 1, 2, 0, 1, 2, 0, 1};
    float imag2[8] = {0};

    // Perform DIT FFT
    bit_reverse(real1, imag1, N); // DIT requires bit-reversed input
    DIT_FFT(real1, imag1, N);

    // Perform DIF FFT
    DIF_FFT(real2, imag2, N);

    // Print results
    print_fft(real1, imag1, N, "DIT FFT Output");
    print_fft(real2, imag2, N, "DIF FFT Output");

    return 0;
}
